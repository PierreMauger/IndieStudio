/*
** EPITECH PROJECT, 2022
** MenuScene.cpp
** File description:
** MenuScene
*/

#include "MenuScene.hpp"

using namespace neo;

MenuScene::MenuScene()
{
}

void MenuScene::update()
{
}

void MenuScene::loadScene(std::shared_ptr<MessageBus> messageBus)
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << object.first << object.second->getPosition().x << object.second->getPosition().y << object.second->getName();
    if (this->_objects.size())
        messageBus->sendMessage(Message(packet, 0, 2));
}

void MenuScene::handleKeyPressed(int playerNb, std::string action)
{
}

void MenuScene::handleKeyRelease(int playerNb, std::string action)
{
}
