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
    this->_playerSpeed.insert(std::make_pair(0, glm::vec3{0.0f}));
    this->_playerSpeed.insert(std::make_pair(1, glm::vec3{0.0f}));
}

GameScene::~GameScene()
{
    for (auto &player : this->_players)
        player.second.reset();
}

void GameScene::update()
{
    for (auto &playerSpeed : this->_playerSpeed) {
        if (playerSpeed.second.x != 0 || playerSpeed.second.y != 0) {
            if (this->_players.find(playerSpeed.first) == this->_players.end())
                break;
            this->_players[playerSpeed.first]->move(playerSpeed.second);
            Packet packet;
            packet << playerSpeed.first << this->_players[playerSpeed.first]->getPos().x << this->_players[playerSpeed.first]->getPos().y << this->_players[playerSpeed.first]->getPos().z;
            this->_messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
        }
    }
}

void GameScene::loadScene()
{
    Packet packet;

    for (auto &player : this->_players)
        packet << 0 << player.first << *player.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (this->_playerSpeed.find(playerNb) == this->_playerSpeed.end())
        return;
    if (action == "MoveRight")
        this->_playerSpeed[playerNb].x += 0.1f;
    else if (action == "MoveLeft")
        this->_playerSpeed[playerNb].x -= 0.1f;
    else if (action == "MoveUp")
        this->_playerSpeed[playerNb].y += 0.1f;
    else if (action == "MoveDown")
        this->_playerSpeed[playerNb].y -= 0.1f;
}

void GameScene::handleKeyReleased(int playerNb, std::string action)
{
    if (this->_playerSpeed.find(playerNb) == this->_playerSpeed.end())
        return;
    if (action == "MoveRight")
        this->_playerSpeed[playerNb].x -= 0.1f;
    else if (action == "MoveLeft")
        this->_playerSpeed[playerNb].x += 0.1f;
    else if (action == "MoveUp")
        this->_playerSpeed[playerNb].y -= 0.1f;
    else if (action == "MoveDown")
        this->_playerSpeed[playerNb].y += 0.1f;
}
