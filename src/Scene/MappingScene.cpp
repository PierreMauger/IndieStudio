/*
** EPITECH PROJECT, 2022
** MappingScene.cpp
** File description:
** MappingScene
*/

#include "MappingScene.hpp"

using namespace neo;

MappingScene::MappingScene(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);

    int it = 0;
}

MappingScene::~MappingScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
    this->_objects.clear();
    this->_buttons.clear();
}

void MappingScene::update()
{
}

void MappingScene::loadScene()
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

void MappingScene::handleKeyPressed(int playerID, std::string action)
{
}

void MappingScene::handleKeyReleased(int playerID, std::string action)
{
}

void MappingScene::handleButtonClicked(int button)
{
}

void MappingScene::handleConfig(std::vector<std::string> config)
{
}

void MappingScene::handleStartGame(Packet data)
{
}
