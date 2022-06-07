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
            packet << i << this->_players[i]->getPos().x << this->_players[i]->getPos().y << this->_players[i]->getPos().z << this->_players[i]->getRotation();
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
                {"#  #W#W#  #"},
                {"#WWWWWWWWW#"},
                {"##W#W#W#W##"},
                {"#WWWWWWWWW#"},
                {"##W#W#W#W##"},
                {"#WWWWWWWWW#"},
                {"#  #W#W#  #"},
                {"#  WWWWW 1#"},
                {"###########"}
    };
    glm::vec3 pos(0.f);
    Packet packet;
    int i = 0;

    for (int i = 0, mapId = 0, screenWidth = GetScreenWidth(), screenHeight = GetScreenHeight(); i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            printf("%f %f %d %d %f %f\n", pos.x, pos.y, screenWidth, screenHeight, (float)screenWidth / tmpMap[0].size(), (float)screenHeight / tmpMap.size());
            if (tmpMap[i][j] == '#')
                _map.insert(std::make_pair(mapId++, std::make_unique<Wall>("Block", pos, false,
                    glm::vec3(screenWidth / tmpMap[0].size(), screenHeight / tmpMap.size(), 1.f))));
            if (tmpMap[i][j] == 'W')
                _map.insert(std::make_pair(mapId++, std::make_unique<Wall>("Wall", pos, true,
                    glm::vec3(screenWidth / tmpMap[0].size(), screenHeight / tmpMap.size(), 1.f))));
            if (tmpMap[i][j] >= '0' && tmpMap[i][j] <= '9')
                this->_players.insert(std::make_pair(tmpMap[i][j] - '0', std::make_unique<Player>("RoboCat", pos,
                    glm::vec3(screenWidth / tmpMap[0].size(), screenHeight / tmpMap.size(), 1.f))));
            pos.x += screenWidth / tmpMap[0].size();
        }
        pos.x = 0.f;
        pos.y += screenHeight / tmpMap.size();
    }
    for (auto& player : this->_players)
        packet << player.second->getType() << i++ << *player.second;
    for (auto& wall : this->_map)
        packet << wall.second->getType() << i++ << *wall.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (this->_players.find(playerNb) == this->_players.end())
        return;
    if (action == "MoveRight") {
        this->_players[playerNb]->addX(10.f);
        this->_players[playerNb]->setRotation(90.f);
    } else if (action == "MoveLeft") {
        this->_players[playerNb]->addX(-10.f);
        this->_players[playerNb]->setRotation(270.f);
    } else if (action == "MoveUp") {
        this->_players[playerNb]->addY(10.f);
        this->_players[playerNb]->setRotation(180.f);
    } else if (action == "MoveDown") {
        this->_players[playerNb]->addY(-10.f);
        this->_players[playerNb]->setRotation(0.f);
    }
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (action == "MoveRight")
        this->_players[playerNb]->addX(-10.f);
    else if (action == "MoveLeft")
        this->_players[playerNb]->addX(10.f);
    else if (action == "MoveUp")
        this->_players[playerNb]->addY(-10.f);
    else if (action == "MoveDown")
        this->_players[playerNb]->addY(10.f);
}
