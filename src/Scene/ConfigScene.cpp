/*
** EPITECH PROJECT, 2022
** ConfigScene.cpp
** File description:
** ConfigScene
*/

#include "ConfigScene.hpp"

using namespace neo;

ConfigScene::ConfigScene(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
}

ConfigScene::~ConfigScene()
{
    // for (auto &object : this->_objects)
        // object.second.reset();
}

void ConfigScene::update()
{
    Packet packet;

    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void ConfigScene::loadScene()
{

}

void ConfigScene::handleKeyPressed(int playerNb, std::string action)
{
}

void ConfigScene::handleKeyReleased(int playerNb, std::string action)
{
}
