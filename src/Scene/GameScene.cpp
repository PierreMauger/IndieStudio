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
    this->_players.insert(std::make_pair(0, std::make_unique<Player>("RoboCat", glm::vec3(0.0f), glm::vec3(0.5f))));
    this->_players.insert(std::make_pair(1, std::make_unique<Player>("RoboCat", glm::vec3(0.0f), glm::vec3(0.5f))));
}

GameScene::~GameScene()
{
    for (auto &player : this->_players)
        player.second.reset();
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

    for (auto &player : this->_players)
        packet << player.second->getType() << player.first << *player.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.f, 0.f, 30.f) << glm::vec3(0.f, 0.f, 10.f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA, Module::GRAPHICS));
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
    if (action == "MoveRight" && this->_players[playerNb]->getSpeed().x > 0.f)
        this->_players[playerNb]->addX(-0.1f);
    else if (action == "MoveLeft" && this->_players[playerNb]->getSpeed().x < 0.f)
        this->_players[playerNb]->addX(0.1f);
    else if (action == "MoveUp" && this->_players[playerNb]->getSpeed().y > 0.f)
        this->_players[playerNb]->addY(-0.1f);
    else if (action == "MoveDown" && this->_players[playerNb]->getSpeed().y < 0.f)
        this->_players[playerNb]->addY(0.1f);
}
