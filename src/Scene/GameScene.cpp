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
                    _players[i]->getPos().y - 0.5f + (_players[i]->getDirection(UP) ? 0.3f : _players[i]->getDirection(DOWN) ? -0.3f : 0.f), 1.f, 1.f),
                CAST(Rectangle, _map[j]->getPos().x - 0.5f, _map[j]->getPos().y - 0.5f, 1.f, 1.f))) {
                _players[i]->setSpeed(glm::vec3(0.f));
                break;
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
