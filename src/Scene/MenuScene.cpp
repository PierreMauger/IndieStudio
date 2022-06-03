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
    this->_objects.insert(std::make_pair(0, std::make_unique<GameObject>(0, "RoboCat", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
    this->_objects.insert(std::make_pair(1, std::make_unique<GameObject>(0, "RoboCat", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f))));
    this->_buttons.insert(std::make_pair(0, std::make_unique<GameObject>(2, "red", glm::vec3(50, 500, 0), glm::vec3(100, 50, 0))));
    this->_buttons.insert(std::make_pair(1, std::make_unique<GameObject>(2, "red", glm::vec3(250, 500, 0), glm::vec3(100, 50, 0))));
    this->_buttons.insert(std::make_pair(2, std::make_unique<GameObject>(2, "red", glm::vec3(450, 500, 0), glm::vec3(100, 50, 0))));

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
        packet << object.second->getType() << object.first << *object.second;
    for (auto &button : this->_buttons)
        packet << button.second->getType() <<  button.first << *button.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void MenuScene::handleKeyPressed(int playerNb, std::string action)
{
    if (playerNb != 0)
        return;
    if (action == "Back") {
        Packet packet;
        packet << this->_selectedButton << 0;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SELECT_BUTTON, Module::GRAPHICS));
        this->_selectedButton = -1;
        return;
    }
    if (action == "Main") {
        if (this->_selectedButton == -1)
            return;
        if (this->_selectedButton == 0)
            return;
        Packet packet;
        packet << this->_selectedButton;
        this->_messageBus->sendMessage(Message(packet, CoreCommand::CHANGE_SCENE, Module::CORE));
        this->_selectedButton = -1;
    }
    if (action == "MoveRight" || action == "MoveLeft") {
        Packet packet;
        packet << this->_selectedButton << 0;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SELECT_BUTTON, Module::GRAPHICS));
        packet.clear();
        if (action == "MoveRight")
            this->_selectedButton = (this->_selectedButton + 1) % this->_buttons.size();
        else {
            if (this->_selectedButton == 0)
                this->_selectedButton = this->_buttons.size();
            this->_selectedButton = (this->_selectedButton - 1) % this->_buttons.size();
        }
        packet << this->_selectedButton << 1;
        this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SELECT_BUTTON, Module::GRAPHICS));
    }
}

void MenuScene::handleKeyReleased(int playerNb, std::string action)
{
}
