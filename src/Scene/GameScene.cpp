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
        if (this->_players[i]->getSpeed() != glm::vec3(0.0f)) {
            this->_players[i]->move(this->_players[i]->getSpeed());
            Packet packet;
            packet << i << this->_players[i]->getPos().x << this->_players[i]->getPos().y << this->_players[i]->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
        }
    }
}

void GameScene::loadScene()
{
    const std::vector<std::string> tmpMap = {
                {"###########"},
                {"#0 WWWWW  #"},
                {"# W#W#W#W #"},
                {"#WWWWWWWWW#"},
                {"##W#W#W#W##"},
                {"#WWWWWWWWW#"},
                {"##W#W#W#W##"},
                {"#WWWWWWWWW#"},
                {"# W#W#W#W #"},
                {"#  WWWWW 1#"},
                {"###########"}
    };
    Packet packet;
    int incrementor = 0;

    for (int i = 0, mapId = 0; i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            glm::vec3 pos(i - ((float)tmpMap[i].size() - 1) / 2, -j + ((float)tmpMap.size() - 1) / 2, 0.f);
            if (tmpMap[i][j] == '#')
                _map[mapId++] = std::make_unique<Wall>("Block", pos, false, glm::vec3(0.5f));
            if (tmpMap[i][j] == 'W')
                _map[mapId++] = std::make_unique<Wall>("Wall", pos, true, glm::vec3(0.5f));
            if (tmpMap[i][j] >= '0' && tmpMap[i][j] <= '9')
                _players[tmpMap[i][j] - '0'] = std::make_unique<Player>("RoboCat", pos, glm::vec3(0.5f));
        }
    }
    for (auto& player : this->_players)
        packet << player.second->getType() << incrementor++ << *player.second;
    for (auto& wall : this->_map)
        packet << wall.second->getType() << incrementor++ << *wall.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.f, 0.f, 20.f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
}
//printf("%f %f %f %f\n", _map[i]->getPos().x, _map[i]->getPos().y, _players[playerNb]->getPos().x, _players[playerNb]->getPos().y);
bool GameScene::checkCollision(int playerNb, std::string direction, float ammount)
{
    if (direction == "MoveRight") {
        for (size_t i = 0; i < _map.size(); i++) {
            printf("%f %f %f %f\n", _map[i]->getPos().x, _map[i]->getPos().y, _players[playerNb]->getPos().x, _players[playerNb]->getPos().y);
            if (_players[playerNb]->getPos().x + ammount > _map[i]->getPos().x - 1.f &&
                _players[playerNb]->getPos().x + ammount < _map[i]->getPos().x &&
                _players[playerNb]->getPos().y > _map[i]->getPos().y - 1.f &&
                _players[playerNb]->getPos().y < _map[i]->getPos().y + 1.f) {
                return true;
            }
        }
    }
    else if (direction == "MoveLeft") {
        for (size_t i = 0; i < _map.size(); i++) {
        if (_players[playerNb]->getPos().x - ammount < _map[i]->getPos().x + 1.f &&
            _players[playerNb]->getPos().x - ammount > _map[i]->getPos().x &&
            _players[playerNb]->getPos().y > _map[i]->getPos().y - 1.f &&
            _players[playerNb]->getPos().y < _map[i]->getPos().y + 1.f) {
            return true;
            }
        }
    }
    else if (direction == "MoveUp") {
        for (size_t i = 0; i < _map.size(); i++) {
            if (_players[playerNb]->getPos().x > _map[i]->getPos().x - 1.f &&
                _players[playerNb]->getPos().x < _map[i]->getPos().x + 1.f &&
                _players[playerNb]->getPos().y + ammount > _map[i]->getPos().y - 1.f &&
                _players[playerNb]->getPos().y + ammount < _map[i]->getPos().y) {
                return true;
            }
        }
    }
    else if (direction == "MoveDown") {
        for (size_t i = 0; i < _map.size(); i++) {
            if (_players[playerNb]->getPos().x > _map[i]->getPos().x - 1.f &&
                _players[playerNb]->getPos().x < _map[i]->getPos().x + 1.f &&
                _players[playerNb]->getPos().y - ammount < _map[i]->getPos().y + 1.f &&
                _players[playerNb]->getPos().y - ammount > _map[i]->getPos().y) {
                return true;
            }
        }
    }
    return false;
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (action == "MoveRight" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addX(0.3f);
    else if (action == "MoveLeft" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addX(-0.3f);
    else if (action == "MoveUp" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addY(0.3f);
    else if (action == "MoveDown" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addY(-0.3f);
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (action == "MoveRight" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addX(-0.3f);
    else if (action == "MoveLeft" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addX(0.3f);
    else if (action == "MoveUp" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addY(-0.3f);
    else if (action == "MoveDown" && !checkCollision(playerNb, action, 0.3f))
        this->_players[playerNb]->addY(0.3f);
}
