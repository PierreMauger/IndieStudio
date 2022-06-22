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

    const std::vector<std::string> map = _mapGenerator.generateProceduralMap(2, 20, 20);
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)map[i].size() - 1) / 2, -j + ((float)map.size() - 1) / 2, 0.0f};
            if (map[i][j] == 'P')
                this->_players[this->_incrementor++] = std::make_unique<Player>("RoboCat", pos, false, glm::vec3(0.4f));
            else if (map[i][j] == 'B')
                this->_players[this->_incrementor++] = std::make_unique<Player>("RoboCat", pos, true, glm::vec3(0.4f));
        }
    }
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)map[i].size() - 1) / 2, -j + ((float)map.size() - 1) / 2, 0.0f};
            if (map[i][j] == '#')
                this->_walls[this->_incrementor++] = std::make_unique<Wall>("Block", pos, glm::vec3(0.5f));
            else if (map[i][j] == 'W')
                this->_walls[this->_incrementor++] = std::make_unique<Wall>("Wall", pos, glm::vec3(0.5f));
        }
    }
    this->_botEngine = std::make_unique<BotEngine>();
}

GameScene::~GameScene()
{
    for (auto &[player_key, player] : this->_players)
        player.reset();
    for (auto &[wall_key, wall] : this->_walls)
        wall.reset();
    for (auto &[bomb_key, bomb] : this->_bombs)
        bomb.reset();
    for (auto &[powerUp_key, powerUp] : this->_powerUps)
        powerUp.reset();
    this->_players.clear();
    this->_walls.clear();
    this->_bombs.clear();
    this->_powerUps.clear();
    this->_botEngine.reset();
}

void GameScene::loadScene()
{
    Packet packet;

    for (auto &[player_key, player] : this->_players)
        packet << player->getType() << player_key << *player;
    for (auto &[wall_key, wall] : this->_walls)
        packet << wall->getType() << wall_key << *wall;
    for (auto &[bomb_key, bomb] : this->_bombs)
        packet << bomb->getType() << bomb_key << *bomb;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, 0.0f, 50.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
}

void GameScene::updatePlayers(void)
{
    Packet data;

    for (auto &[player_key, player] : this->_players) {
        if (player->getDirection(RIGHT))
            player->getSpeed().x += 0.1f + player->getSpeedUp() * 0.05f;
        if (player->getDirection(LEFT))
            player->getSpeed().x += -0.1f - player->getSpeedUp() * 0.05f;
        if (player->getDirection(UP))
            player->getSpeed().y += 0.1f + player->getSpeedUp() * 0.05f;
        if (player->getDirection(DOWN))
            player->getSpeed().y += -0.1f - player->getSpeedUp() * 0.05f;
        for (auto it = this->_walls.begin(); it != this->_walls.end();) {
            if (it->second->getName() == "Wall" && player->getWallPass()) {
                it++;
                continue;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
            if (player->getSpeed().x && player->getSpeed().y && CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            } else {
                it++;
            }
        }
        for (auto &[bomb_key, bomb] : this->_bombs) {
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f)))
                continue;
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().x = 0.0f;
            }
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
            if (player->getSpeed().x && player->getSpeed().y && CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, bomb->getPos().x - 0.5f, bomb->getPos().y - 0.5f, 1.0f, 1.0f))) {
                player->getSpeed().y = 0.0f;
            }
        }
        for (auto it = this->_powerUps.begin(); it != this->_powerUps.end();) {
            if (CheckCollisionRecs(
                CAST(Rectangle, player->getPos().x - 0.3f + player->getSpeed().x, player->getPos().y - 0.3f + player->getSpeed().y, 0.6f, 0.6f),
                CAST(Rectangle, it->second->getPos().x - 0.5f, it->second->getPos().y - 0.5f, 1.0f, 1.0f))) {
                if (it->second->getName() == "BombUp")
                    player->getBombUp() += 1;
                if (it->second->getName() == "SpeedUp")
                    player->getSpeedUp() += 1;
                if (it->second->getName() == "FireUp")
                    player->getFireUp() += 1;
                if (it->second->getName() == "WallPass")
                    player->getWallPass() = true;
                data << it->second->getType() << it->first;
                this->_powerUps.erase(it++);
            } else {
                it++;
            }
        }
        if (player->getSpeed() != glm::vec3(0.0f)) {
            player->move(player->getSpeed());
            Packet packet;
            packet << player_key << player->getPos().x << player->getPos().y << player->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            player->getSpeed() = glm::vec3(0.0f);
        }
    }
    if (data.checkSize(1))
        this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::explode(std::unique_ptr<Bomb> &bomb)
{
    Packet addData;
    Packet deleteData;

    for (auto it = this->_walls.begin(); it != this->_walls.end(); it++) {
        if (it->second->getPos().x == bomb->getPos().x && it->second->getPos().y == bomb->getPos().y) {
            deleteData << it->second->getType() << it->first;
            this->_walls.erase(it++);
            break;
        }
    }
    for (size_t i = RIGHT; i <= DOWN; i++) {
        for (int j = 0; j <= 2 + bomb->getFireUp(); j++) {
            for (auto it = this->_players.begin(); it != this->_players.end();) {
                if (std::floor(it->second->getPos().x) + 0.5f == bomb->getPos().x + (i == RIGHT ? j : i == LEFT ? -j : 0) &&
                    std::floor(it->second->getPos().y) + 0.5f == bomb->getPos().y + (i == UP ? j : i == DOWN ? -j : 0)) {
                    deleteData << it->second->getType() << it->first;
                    this->_players.erase(it++);
                } else {
                    it++;
                }
            }

            for (auto &[bomb_key, other_bomb] : this->_bombs) {
                if (other_bomb->getPos() == bomb->getPos())
                    continue;
                if (other_bomb->getPos().x == bomb->getPos().x + (i == RIGHT ? j : i == LEFT ? -j : 0) &&
                    other_bomb->getPos().y == bomb->getPos().y + (i == UP ? j : i == DOWN ? -j : 0))
                    other_bomb->getTimer() = 0.0f;
            }
            
            for (auto it = this->_powerUps.begin(); it != this->_powerUps.end();) {
                if (it->second->getPos().x == bomb->getPos().x + (i == RIGHT ? j : i == LEFT ? -j : 0) &&
                    it->second->getPos().y == bomb->getPos().y + (i == UP ? j : i == DOWN ? -j : 0)) {
                    deleteData << it->second->getType() << it->first;
                    this->_powerUps.erase(it++);
                } else {
                    it++;
                }
            }

            for (auto it = this->_walls.begin(); it != this->_walls.end(); it++) {
                if (it->second->getPos().x == bomb->getPos().x + (i == RIGHT ? j : i == LEFT ? -j : 0) &&
                    it->second->getPos().y == bomb->getPos().y + (i == UP ? j : i == DOWN ? -j : 0)) {
                    j = 2 + bomb->getFireUp();
                    if (it->second->getName() == "Block")
                        break;
                    deleteData << it->second->getType() << it->first;
                    if (std::rand() % 1 == 0) {
                        int tmp = std::rand() % 4;
                        this->_powerUps[this->_incrementor] = std::make_unique<PowerUp>(powerUps[tmp], it->second->getPos(), glm::vec3(0.5f));
                        addData << this->_powerUps[this->_incrementor]->getType() << this->_incrementor << *this->_powerUps[this->_incrementor];
                        this->_incrementor++;
                    }
                    this->_walls.erase(it++);
                    break;
                }
            }
        }
    }
    if (addData.checkSize(1))
        this->_messageBus->sendMessage(Message(addData, GraphicsCommand::ADD, Module::GRAPHICS));
    if (deleteData.checkSize(1))
        this->_messageBus->sendMessage(Message(deleteData, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::updateBombs(void)
{
    Packet data;

    for (auto it = this->_bombs.begin(); it != this->_bombs.end();) {
        if (GetTime() - it->second->getTimer() > 3) {
            this->explode(it->second);
            data << it->second->getType() << it->first;
            this->_bombs.erase(it++);
        } else {
            it++;
        }
    }
    if (data.checkSize(1))
        this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
}

void GameScene::update(void)
{
    this->_botEngine->updateBot(this);
    this->updatePlayers();
    this->updateBombs();
}

bool GameScene::canPlaceBomb(int playerNb)
{
    size_t bombsCount = 0;

    for (auto it = this->_bombs.begin(); it != this->_bombs.end(); it++)
        if (it->second->getPlayerId() == playerNb)
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
        this->_players[playerNb]->getDirection(RIGHT) = true;
    else if (action == "MoveLeft")
        this->_players[playerNb]->getDirection(LEFT) = true;
    else if (action == "MoveUp")
        this->_players[playerNb]->getDirection(UP) = true;
    else if (action == "MoveDown")
        this->_players[playerNb]->getDirection(DOWN) = true;
    else if (action == "Main" && canPlaceBomb(playerNb)) {
        glm::vec3 pos(floor(this->_players[playerNb]->getPos().x) + 0.5f, floor(this->_players[playerNb]->getPos().y) + 0.5f, this->_players[playerNb]->getPos().z);
        this->_bombs[this->_incrementor] = std::make_unique<Bomb>("Bomb", pos, this->_players[playerNb]->getFireUp(), playerNb, glm::vec3(0.5f));
        Packet packet;
        packet << this->_bombs[this->_incrementor]->getType() << this->_incrementor << *this->_bombs[this->_incrementor];
        this->_incrementor++;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
    }
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (this->_players.find(playerNb) == this->_players.end())
        return;
    if (action == "MoveRight")
        this->_players[playerNb]->getDirection(RIGHT) = false;
    else if (action == "MoveLeft")
        this->_players[playerNb]->getDirection(LEFT) = false;
    else if (action == "MoveUp")
        this->_players[playerNb]->getDirection(UP) = false;
    else if (action == "MoveDown")
        this->_players[playerNb]->getDirection(DOWN) = false;
}


void GameScene::handleButtonClicked(int button)
{
}

void GameScene::handleConfig(std::vector<std::string> config)
{
}

void GameScene::handleStartGame(Packet data)
{
}

std::shared_ptr<MessageBus> GameScene::getMessageBus()
{
    return this->_messageBus;
}

std::map<int, std::unique_ptr<Player>> &GameScene::getPlayers()
{
    return this->_players;
}

std::map<int, std::unique_ptr<Bomb>> &GameScene::getBombs()
{
    return this->_bombs;
}

std::map<int, std::unique_ptr<Wall>> &GameScene::getWalls()
{
    return this->_walls;
}

std::map<int, std::unique_ptr<PowerUp>> &GameScene::getPowerUps()
{
    return this->_powerUps;
}

neo::MapGenerator &GameScene::getMapGenerator()
{
    return this->_mapGenerator;
}
