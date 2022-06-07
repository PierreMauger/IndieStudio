/*
** EPITECH PROJECT, 2022
** Core.cpp
** File description:
** Core
*/

#include "Core.hpp"
#include "MenuScene.hpp"
#include "ConfigScene.hpp"
#include "GameScene.hpp"

using namespace neo;

Core::Core(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    this->_currentScene = 2;

    this->_scenes.push_back(std::make_unique<MenuScene>(this->_messageBus));
    this->_scenes.push_back(std::make_unique<ConfigScene>(this->_messageBus));
    this->_scenes.push_back(std::make_unique<GameScene>(this->_messageBus));

    this->_functionTab = {
        std::bind(&Core::receiveKeyPressed, this, std::placeholders::_1),
        std::bind(&Core::receiveKeyReleased, this, std::placeholders::_1),
        std::bind(&Core::receiveGraphicsReady, this, std::placeholders::_1),
        std::bind(&Core::receiveChangeScene, this, std::placeholders::_1),
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
    this->_scenes[this->_currentScene]->handleKeyReleased(playerNb, action);
}

void Core::receiveGraphicsReady(Packet data)
{
    this->_scenes[this->_currentScene]->loadScene();
}

void Core::receiveChangeScene(Packet data)
{
    int scene = 0;

    data >> scene;
    this->_currentScene = scene;
    if (scene < this->_scenes.size())
        this->_scenes[scene]->loadScene();
}
