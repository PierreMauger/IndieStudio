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
    this->_players.insert(std::make_pair(0, std::make_unique<Player>("RoboCat", glm::vec3(0, 0, 0))));
    this->_players.insert(std::make_pair(1, std::make_unique<Player>("RoboCat", glm::vec3(0, 0, 0))));
}

GameScene::~GameScene()
{
    for (auto &player : this->_players)
        player.second.reset();
}

void GameScene::update()
{
    for (int i = 0; i < _players.size(); i++) {
        if (!(!_players[i]->getSpeed().x && !_players[i]->getSpeed().y && !_players[i]->getSpeed().z)) {
            this->_players[i]->move(_players[i]->getSpeed());
            Packet packet;
            packet << i << this->_players[i]->getPos().x << this->_players[i]->getPos().y << this->_players[i]->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
        }
    }
}

void GameScene::loadScene()
{
    Packet packet;

    for (auto &player : this->_players)
        packet << player.second->getType() << player.first << *player.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (action == "MoveRight")
        this->_players[playerNb]->addX(0.1f);
    else if (action == "MoveLeft")
        this->_players[playerNb]->subX(0.1f);
    else if (action == "MoveUp")
        this->_players[playerNb]->addY(0.1f);
    else if (action == "MoveDown")
        this->_players[playerNb]->subY(0.1f);
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (action == "MoveRight")
        this->_players[playerNb]->subX(0.1f);
    else if (action == "MoveLeft")
        this->_players[playerNb]->addX(0.1f);
    else if (action == "MoveUp")
        this->_players[playerNb]->subY(0.1f);
    else if (action == "MoveDown")
        this->_players[playerNb]->addY(0.1f);
}
