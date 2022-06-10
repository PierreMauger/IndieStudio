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
}

GameScene::~GameScene()
{
    for (auto& player : this->_players)
        player.second.reset();
    for (auto& wall : this->_map)
        wall.second.reset();
}

void GameScene::update()
{
    for (int i = 0; i < this->_players.size(); i++) {
        if (this->_players[i]->getDirection(RIGHT))
            this->_players[i]->getSpeed().x += 0.3f;
        if (this->_players[i]->getDirection(LEFT))
            this->_players[i]->getSpeed().x += -0.3f;
        if (this->_players[i]->getDirection(UP))
            this->_players[i]->getSpeed().y += 0.3f;
        if (this->_players[i]->getDirection(DOWN))
            this->_players[i]->getSpeed().y += -0.3f;
        for (size_t j = 0; j < _map.size(); j++) {
            if (CheckCollisionRecs(
                CAST(Rectangle, _players[i]->getPos().x - 0.5f + (_players[i]->getDirection(RIGHT) ? 0.3f : _players[i]->getDirection(LEFT) ? -0.3f : 0.f),
                    _players[i]->getPos().y - 0.5f, 1.0f, 1.0f),
                CAST(Rectangle, _map[j]->getPos().x - 0.5f, _map[j]->getPos().y - 0.5f, 1.0f, 1.0f))) {
                _players[i]->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, _players[i]->getPos().x - 0.5f,
                    _players[i]->getPos().y - 0.5f + (_players[i]->getDirection(UP) ? 0.3f : _players[i]->getDirection(DOWN) ? -0.3f : 0.f), 1.0f, 1.0f),
                CAST(Rectangle, _map[j]->getPos().x - 0.5f, _map[j]->getPos().y - 0.5f, 1.0f, 1.0f))) {
                _players[i]->getSpeed().y = 0.0f;
            }
        }
        if (this->_players[i]->getSpeed() != glm::vec3(0.0f)) {
            this->_players[i]->move(this->_players[i]->getSpeed());
            Packet packet;
            packet << i << this->_players[i]->getPos().x << this->_players[i]->getPos().y << this->_players[i]->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
            this->_players[i]->setSpeed(glm::vec3(0.0f));
        }
    }
}

void GameScene::loadScene()
{
    const std::vector<std::string> tmpMap = generateProceduralMap(3, 20, 20);
    Packet packet;
    int incrementor = 0;

    for (int i = 0, mapId = 0; i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            glm::vec3 pos(i - ((float)tmpMap[i].size() - 1) / 2, -j + ((float)tmpMap.size() - 1) / 2, 0.f);
            if (tmpMap[i][j] == '#')
                this->_map[mapId++] = std::make_unique<Wall>("Block", pos, false, glm::vec3(0.5f));
            if (tmpMap[i][j] == 'W')
                this->_map[mapId++] = std::make_unique<Wall>("Wall", pos, true, glm::vec3(0.5f));
            if (tmpMap[i][j] >= '0' && tmpMap[i][j] <= '9')
                this->_players[tmpMap[i][j] - '0'] = std::make_unique<Player>("RoboCat", pos, glm::vec3(0.5f));
        }
    }
    for (auto& player : this->_players)
        packet << player.second->getType() << incrementor++ << *player.second;
    for (auto& wall : this->_map)
        packet << wall.second->getType() << incrementor++ << *wall.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, 0.0f, 50.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
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
    map[1][1] = 0 + '0';
    map[x - 2][y - 2] = 1 + '0';
    if (nb_player > 2)
        map[1][y - 2] = 2 + '0';
    if (nb_player > 3)
        map[x - 2][1] = 3 + '0';
    return map;
}
