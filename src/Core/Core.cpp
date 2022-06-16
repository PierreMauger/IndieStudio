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

    this->_functionTab.push_back(std::bind(&Core::receiveKeyPressed, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Core::receiveKeyReleased, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Core::receiveGraphicsReady, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Core::receiveChangeScene, this, std::placeholders::_1));
}

void Core::run()
{
    std::srand(std::time(0));
    while (this->_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        this->update();
        this->_messageBus->notify(Module::CORE);
    }
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
