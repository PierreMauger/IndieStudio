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
    this->_scenes.push_back(std::make_shared<ConfigScene>());
    this->_scenes.push_back(std::make_shared<GameScene>());

    this->_scenes[this->_currentScene]->loadScene(this->_messageBus);

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
    this->_scenes[this->_currentScene]->update(this->_messageBus);
}

void Core::receiveKeyPressed(Packet data)
{
    std::string action;
    int playerNb = 0;

    data >> playerNb >> action;
    this->_scenes[this->_currentScene]->handleKeyPressed(playerNb, action);
}

void Core::receiveKeyReleased(Packet data)
{
    std::string action;
    int playerNb = 0;

    data >> playerNb >> action;
    this->_scenes[this->_currentScene]->handleKeyRelease(playerNb, action);
}
