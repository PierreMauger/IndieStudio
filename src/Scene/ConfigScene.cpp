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
    this->_playerConnected.resize(4, false);

    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);

    float pos = -1.f + 0.28f;
    this->_buttons[0] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos            , 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[1] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 1 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[2] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 2 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[3] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 3 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
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
    packet.clear();
    packet << 0 << glm::vec3(0.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
}

void ConfigScene::handleKeyPressed(int playerNb, std::string action)
{
}

void ConfigScene::handleKeyReleased(int playerNb, std::string action)
{
}

void ConfigScene::handleButtonClicked(int button)
{
    if (this->_playerConnected[button]) {
        this->deleteCard(button);
        this->_playerConnected[button] = false;
    } else {
        this->addCard(button);
        this->_playerConnected[button] = true;
    }
}

void ConfigScene::addCard(int card)
{
    Packet data;
    float pos = -1.f + 0.28f + card * 0.48f;

    data << this->_buttons[card]->getType() << card;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(3, "Card", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.45f, 0.0f));
    this->_objects[card + 1] = std::make_unique<GameObject>(0, "RoboCat", glm::vec3((pos) * 7.0f, -1.5f, 0.0f), glm::vec3(0.5f));
    this->_objects[card + 1]->setRotation(glm::vec3(270.0f, 0.0f, 0.0f));
    data << this->_buttons[card]->getType() << card << *this->_buttons[card];
    data << this->_objects[card + 1]->getType() << card + 1 << *this->_objects[card + 1];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::deleteCard(int card)
{
    Packet data;
    float pos = -1.f + 0.28f + card * 0.48f;

    data << this->_buttons[card]->getType() << card;
    data << this->_objects[card + 1]->getType() << card + 1;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    data << this->_buttons[card]->getType() << card << *this->_buttons[card];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));
}
