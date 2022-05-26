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
    this->_objects.insert(std::make_pair(0, std::make_unique<GameObject>("ressources/FloofFox_model.dae", (Vector2){1, 1})));
}

MenuScene::~MenuScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
}

void MenuScene::update()
{
}

void MenuScene::loadScene(std::shared_ptr<MessageBus> messageBus)
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << object.first << object.second->getPosition().x << object.second->getPosition().y << object.second->getName();
    messageBus->sendMessage(Message(packet, 0, 2));
}

void MenuScene::handleKeyPressed(int playerNb, std::string action)
{
}

void MenuScene::handleKeyRelease(int playerNb, std::string action)
{
}
