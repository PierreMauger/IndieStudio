/*
** EPITECH PROJECT, 2022
** MenuScene.cpp
** File description:
** MenuScene
*/

#include "MenuScene.hpp"

using namespace neo;

MenuScene::MenuScene(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_objects.insert(std::make_pair(0, std::make_unique<GameObject>(0, "fox", (Vector2){0, 0})));
    this->_buttons.insert(std::make_pair(0, std::make_unique<GameObject>(0, "red", (Vector2){50, 500}, (Vector2){100, 50})));
    this->_buttons.insert(std::make_pair(1, std::make_unique<GameObject>(0, "red", (Vector2){250, 500}, (Vector2){100, 50})));

    this->_selectedButton = -1;
}

MenuScene::~MenuScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
}

void MenuScene::update()
{
}

void MenuScene::loadScene()
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << 0 << object.first << *object.second;
    for (auto &button : this->_buttons)
        packet << 2 <<  button.first << *button.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void MenuScene::handleKeyPressed(int playerNb, std::string action)
{
    if (playerNb != 0)
        return;
    if (action == "MoveRight" || action == "MoveLeft") {
        Packet packet;
        packet << this->_selectedButton << 0;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SELECT_BUTTON, Module::GRAPHICS));
        packet.clear();

        if (action == "MoveRight")
            this->_selectedButton = (this->_selectedButton + 1) % this->_buttons.size();
        else
            this->_selectedButton = (this->_selectedButton - 1) % this->_buttons.size();
        packet << this->_selectedButton << 1;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SELECT_BUTTON, Module::GRAPHICS));
    }
}

void MenuScene::handleKeyReleased(int playerNb, std::string action)
{
}
