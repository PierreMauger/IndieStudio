/*
** EPITECH PROJECT, 2022
** GameScene.cpp
** File description:
** GameScene
*/

#include "GameScene.hpp"

using namespace neo;

GameScene::GameScene(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_incrementor = 0;
}

GameScene::~GameScene()
{
    for (auto &[player_key, player] : this->_players)
        player.reset();
    for (auto &[wall_key, wall] : this->_map)
        wall.reset();
    for (auto &[bomb_key, bomb] : this->_bombs)
        bomb.reset();
    this->_players.clear();
    this->_map.clear();
    this->_bombs.clear();
}

void GameScene::updatePlayers(void)
{
    for (auto &[player_key, player] : this->_players) {
        if (player->getDirection(RIGHT))
            player->getSpeed().x += 0.1f;
        if (player->getDirection(LEFT))
            player->getSpeed().x += -0.1f;
        if (player->getDirection(UP))
            player->getSpeed().y += 0.1f;
        if (player->getDirection(DOWN))
            player->getSpeed().y += -0.1f;
        for (auto &[wall_key, wall] : this->_map) {
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, wall->getPos().x - 0.5f, wall->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, wall->getPos().x - 0.5f, wall->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
            if (player->getSpeed().x && player->getSpeed().y && CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, wall->getPos().x - 0.5f, wall->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
        }
        if (player->getSpeed() != glm::vec3(0.0f)) {
            player->move(player->getSpeed());
            Packet packet;
            packet << player_key << player->getPos().x << player->getPos().y << player->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
            player->setSpeed(glm::vec3(0.0f));
        }
    }
}

void GameScene::updateBombs()
{
    for (auto &[bomb_key, bomb] : this->_bombs) {
        if (GetTime() - bomb->getTimer() > 3) {
            Packet packet;
            packet << bomb_key;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::DELETE, Module::GRAPHICS));
            this->_bombs.erase(bomb_key);
        }
    }
}

void GameScene::update()
{
    updatePlayers();
    updateBombs();
}

void GameScene::loadScene()
{
    const std::vector<std::string> tmpMap = generateProceduralMap(3, 20, 20);
    Packet packet;

    for (int i = 0; i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            glm::vec3 pos(i - ((float)tmpMap[i].size() - 1) / 2, -j + ((float)tmpMap.size() - 1) / 2, 0.f);
            if (tmpMap[i][j] == 'P') {
                this->_players[_incrementor] = std::make_unique<Player>("RoboCat", pos, glm::vec3(0.4f));
                packet << this->_players[_incrementor]->getType() << _incrementor << *this->_players[_incrementor];
                _incrementor++;
            }
        }
    }
    for (int i = 0; i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            glm::vec3 pos(i - ((float)tmpMap[i].size() - 1) / 2, -j + ((float)tmpMap.size() - 1) / 2, 0.f);
            if (tmpMap[i][j] == '#' || tmpMap[i][j] == 'W') {
                if (tmpMap[i][j] == '#')
                    this->_map[_incrementor] = std::make_unique<Wall>("Block", pos, false, glm::vec3(0.5f));
                if (tmpMap[i][j] == 'W')
                    this->_map[_incrementor] = std::make_unique<Wall>("Wall", pos, true, glm::vec3(0.5f));
                packet << this->_map[_incrementor]->getType() << _incrementor << *this->_map[_incrementor];
                _incrementor++;
            }
        }
    }
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, 0.0f, 50.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
}

bool GameScene::canPlaceBomb(int playerNb)
{
    size_t bombsCount = 0;

    for (auto &[bomb_key, bomb] : this->_bombs)
        if (bomb->getPlayerId() == playerNb)
            bombsCount++;
    if (1 + this->_players[playerNb]->getBombUp() > bombsCount)
        return true;
    return false;
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (this->_players.find(playerNb) == this->_players.end())
        return;
    if (action == "MoveRight")
        this->_players[playerNb]->setDirection(RIGHT, true);
    else if (action == "MoveLeft")
        this->_players[playerNb]->setDirection(LEFT, true);
    else if (action == "MoveUp")
        this->_players[playerNb]->setDirection(UP, true);
    else if (action == "MoveDown")
        this->_players[playerNb]->setDirection(DOWN, true);
    else if (action == "Main" && canPlaceBomb(playerNb)) {
        this->_bombs[_incrementor] = std::make_unique<Bomb>("Bomb", this->_players[playerNb]->getPos(), 0, playerNb, glm::vec3(0.4f));
        Packet packet;
        packet << this->_bombs[_incrementor]->getType() << _incrementor << *this->_bombs[_incrementor];
        _incrementor++;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
    }
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (this->_players.find(playerNb) == this->_players.end())
        return;
    if (action == "MoveRight")
        this->_players[playerNb]->setDirection(RIGHT, false);
    else if (action == "MoveLeft")
        this->_players[playerNb]->setDirection(LEFT, false);
    else if (action == "MoveUp")
        this->_players[playerNb]->setDirection(UP, false);
    else if (action == "MoveDown")
        this->_players[playerNb]->setDirection(DOWN, false);
}

std::string GameScene::multiplier_str(std::string chr, std::size_t size)
{
    std::string str = chr;

    for (size_t i = 1; i != size; i++)
        str += chr;
    return str;
}

std::vector<std::string> GameScene::copySymmetrical(std::size_t nb_player, std::vector<std::string> map)
{
    std::size_t max_y = map.size();

    for (auto &m : map)
        m += std::string(m.rbegin(), m.rend());
    for (std::size_t i = max_y - 1; i != -1; i--)
        map.push_back(map[i]);
    return map;
}

bool GameScene::findPathX(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x)
{
    if (curr.first == x - 1 && map[curr.second][curr.first] == 'W')
        return true;
    if (map[curr.second][curr.first] == '#' || map[curr.second][curr.first] == 't')
        return false;
    map[curr.second][curr.first] = 't';
    if (curr.first != x - 1)
        if (findPathX(map, {curr.first + 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != y - 1)
        if (findPathX(map, {curr.first, curr.second + 1}, y, x) == 1)
            return true;
    if (curr.first != 0)
        if (findPathX(map, {curr.first - 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != 0)
        if (findPathX(map, {curr.first, curr.second - 1}, y, x) == 1)
            return true;
    return false;
}

bool GameScene::findPathY(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x)
{
    if (curr.second == y - 1 && map[curr.second][curr.first] == 'W')
        return true;
    if (map[curr.second][curr.first] == '#' || map[curr.second][curr.first] == 't')
        return false;
    map[curr.second][curr.first] = 't';
    if (curr.first != x - 1)
        if (findPathY(map, {curr.first + 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != y - 1)
        if (findPathY(map, {curr.first, curr.second + 1}, y, x) == 1)
            return true;
    if (curr.first != 0)
        if (findPathY(map, {curr.first - 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != 0)
        if (findPathY(map, {curr.first, curr.second - 1}, y, x) == 1)
            return true;
    return false;
}

std::vector<std::string> GameScene::generateCornerMap(std::size_t x, std::size_t y)
{
    std::vector<std::string> new_map;
    float random = 0;

    new_map.resize(x);
    for (size_t i = 0; i != x; i++) {
        new_map[i].resize(y);
        for (size_t n = 0; n != y; n++) {
            random = std::rand() % 10;
            if (random <= 6)
                new_map[i][n] = 'W';
            else
                new_map[i][n] = '#';
        }
        new_map[i][y] = '\0';
    }
    new_map[0][0] = 'W';
    new_map[0][1] = 'W';
    new_map[1][0] = 'W';
    if (!findPathY(new_map, {0, 0}, y, x))
        return (generateCornerMap(x, y));
    if (!findPathX(new_map, {0, 0}, y, x))
        return (generateCornerMap(x, y));
    new_map[0][0] = ' ';
    new_map[0][1] = ' ';
    new_map[1][0] = ' ';
    return new_map;
}

std::vector<std::string> GameScene::generateProceduralMap(std::size_t nb_player, std::size_t x, std::size_t y)
{
    std::vector<std::string> map = generateCornerMap(x / 2 - 1, y / 2 - 1);

    map = copySymmetrical(nb_player, map);
    for (auto &m : map) {
        m.insert(m.begin(), '#');
        m.push_back('#');
    }
    map.insert(map.begin(), multiplier_str(std::string("#"), x));
    map.push_back(multiplier_str(std::string("#"), x));
    map[1][1] = 'P';
    map[x - 2][y - 2] = 'P';
    if (nb_player > 2)
        map[1][y - 2] = 'P';
    if (nb_player > 3)
        map[x - 2][1] = 'P';
    return map;
}
