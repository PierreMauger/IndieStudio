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
    this->_objects.insert(std::make_pair(0, std::make_unique<GameObject>("ressources/models/FloofFox.dae", (Vector2){1, 1})));
    this->_buttons.insert(std::make_pair(0, std::make_unique<GameObject>("red", (Vector2){25, 10}, (Vector2){100, 50})));
}

MenuScene::~MenuScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
}

void MenuScene::update(std::shared_ptr<MessageBus> messageBus)
{
}

void MenuScene::loadScene(std::shared_ptr<MessageBus> messageBus)
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << object.first << object.second->getPos().x << object.second->getPos().y << object.second->getName();
    messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD_MODEL, Module::GRAPHICS));

    packet.clear();
    for (auto &button : this->_buttons)
        packet << button.first << button.second->getPos().x << button.second->getPos().y << button.second->getSize().x << button.second->getSize().y << button.second->getName();
    messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD_BUTTON, Module::GRAPHICS));
}

void MenuScene::handleKeyPressed(int playerNb, std::string action)
{
}

void MenuScene::handleKeyRelease(int playerNb, std::string action)
{
}
