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
    const std::vector<std::string> tmpMap = {
                {"###########"},
                {"#1 WWWWW  #"},
                {"#  #W#W#  #"},
                {"#WWWWWWWWW#"},
                {"##W#W#W#W##"},
                {"#WWWWWWWWW#"},
                {"##W#####W##"},
                {"#WWWWWWWWW#"},
                {"#  #W#W#  #"},
                {"#  WWWWW 2#"},
                {"###########"}
    };

    this->_messageBus = messageBus;
    this->_players.insert(std::make_pair(0, std::make_unique<Player>("RoboCat", glm::vec3(0.f), glm::vec3(0.2f))));
    this->_players.insert(std::make_pair(1, std::make_unique<Player>("RoboCat", glm::vec3(0.f), glm::vec3(0.2f))));
    for (int i = 0, mapId = 0; i < tmpMap.size(); i++) {
        for (int j = 0; j < tmpMap[i].size(); j++) {
            if (tmpMap[i][j] == '#')
                _map.insert(std::make_pair(mapId, std::make_unique<Wall>("Cube", glm::vec3(i * 0.2f, j * 0.2f, 0), false, glm::vec3(0.2f))));
        }
    }
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
    Packet packet;
    int i = 0;

    for (auto& player : this->_players) {
        packet << player.second->getType() << i++ << *player.second;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
        packet.clear();
    }
    for (auto& wall : this->_map) {
        packet << wall.second->getType() << i++ << *wall.second;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
        packet.clear();
    }
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (this->_players.find(playerNb) == this->_players.end())
        return;
    if (action == "MoveRight") {
        this->_players[playerNb]->addX(0.1f);
        this->_players[playerNb]->setRotation(90.f);
    } else if (action == "MoveLeft") {
        this->_players[playerNb]->addX(-0.1f);
        this->_players[playerNb]->setRotation(270.f);
    } else if (action == "MoveUp") {
        this->_players[playerNb]->addY(0.1f);
        this->_players[playerNb]->setRotation(180.f);
    } else if (action == "MoveDown") {
        this->_players[playerNb]->addY(-0.1f);
        this->_players[playerNb]->setRotation(0.f);
    }
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (action == "MoveRight")
        this->_players[playerNb]->addX(-0.1f);
    else if (action == "MoveLeft")
        this->_players[playerNb]->addX(0.1f);
    else if (action == "MoveUp")
        this->_players[playerNb]->addY(-0.1f);
    else if (action == "MoveDown")
        this->_players[playerNb]->addY(0.1f);
}
