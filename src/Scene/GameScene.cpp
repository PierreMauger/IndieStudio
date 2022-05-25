/*
** EPITECH PROJECT, 2022
** GameScene.cpp
** File description:
** GameScene
*/

#include "GameScene.hpp"

using namespace neo;

GameScene::GameScene()
{
}

void GameScene::update()
{
    // if (this->_speed.x != 0 || this->_speed.y != 0) {
        // this->_pos.x += this->_speed.x;
        // this->_pos.y += this->_speed.y;
        // Packet packet;
        // packet << this->_pos.x << this->_pos.y;
        // this->postMessage(Message(packet, 0, 2));
    // }
}

void GameScene::loadScene(std::shared_ptr<MessageBus> messageBus)
{
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    // if (action == "MoveRight")
        // this->_speed.x += 1;
    // if (action == "MoveLeft")
        // this->_speed.x -= 1;
    // if (action == "MoveUp")
        // this->_speed.y -= 1;
    // if (action == "MoveDown")
        // this->_speed.y += 1;
}

void GameScene::handleKeyRelease(int playerNb, std::string action)
{
    // if (action == "MoveRight")
        // this->_speed.x -= 1;
    // if (action == "MoveLeft")
        // this->_speed.x += 1;
    // if (action == "MoveUp")
        // this->_speed.y += 1;
    // if (action == "MoveDown")
        // this->_speed.y -= 1;
}
