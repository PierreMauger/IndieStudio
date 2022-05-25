/*
** EPITECH PROJECT, 2022
** Core.cpp
** File description:
** Core
*/

#include "Core.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "ConfigScene.hpp"

using namespace neo;

Core::Core(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    this->_currentScene = 0;

    this->_scenes.push_back(std::make_shared<MenuScene>());
    this->_scenes.push_back(std::make_shared<GameScene>());
    this->_scenes.push_back(std::make_shared<ConfigScene>());

    this->_functionTab = {
        std::bind(&Core::receiveKeyPressed, this, std::placeholders::_1),
        std::bind(&Core::receiveKeyReleased, this, std::placeholders::_1),
    };
}

void Core::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}

void Core::update()
{
    this->_scenes[this->_currentScene]->update();

    // if (this->_speed.x != 0 || this->_speed.y != 0) {
        // this->_pos.x += this->_speed.x;
        // this->_pos.y += this->_speed.y;
        // Packet packet;
        // packet << this->_pos.x << this->_pos.y;
        // this->postMessage(Message(packet, 0, 2));
    // }
}

void Core::receiveKeyPressed(Packet data)
{
    std::string action;
    int playerNb = 0;

    data >> playerNb >> action;
    this->_scenes[this->_currentScene]->handleKeyPressed(playerNb, action);
    // if (action == "MoveRight")
        // this->_speed.x += 1;
    // if (action == "MoveLeft")
        // this->_speed.x -= 1;
    // if (action == "MoveUp")
        // this->_speed.y -= 1;
    // if (action == "MoveDown")
        // this->_speed.y += 1;
}

void Core::receiveKeyReleased(Packet data)
{
    std::string action;
    int playerNb = 0;

    data >> playerNb >> action;
    this->_scenes[this->_currentScene]->handleKeyRelease(playerNb, action);
    // if (action == "MoveRight")
        // this->_speed.x -= 1;
    // if (action == "MoveLeft")
        // this->_speed.x += 1;
    // if (action == "MoveUp")
        // this->_speed.y += 1;
    // if (action == "MoveDown")
        // this->_speed.y -= 1;
}
