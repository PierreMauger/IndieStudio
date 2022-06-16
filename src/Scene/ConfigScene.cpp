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

    this->_buttons[0] = std::make_unique<GameObject>(2, "Button", glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(50.0f, 30.0f, 0.0f));
    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);
}

ConfigScene::~ConfigScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
    this->_objects.clear();
    this->_buttons.clear();
}

void ConfigScene::update()
{
}

void ConfigScene::loadScene()
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << object.second->getType() << object.first << *object.second;
    for (auto &button : this->_buttons)
        packet << button.second->getType() <<  button.first << *button.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, 0.0f, 10.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
}

void ConfigScene::handleKeyPressed(int playerNb, std::string action)
{
}

void ConfigScene::handleKeyReleased(int playerNb, std::string action)
{
}
