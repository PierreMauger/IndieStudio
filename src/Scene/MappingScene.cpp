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
    float pos = -1.0f + 0.28f;

    this->_messageBus = messageBus;
    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);
    this->_buttons[0] = std::make_unique<GameObject>(3, "Back", glm::vec3(pos, -0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
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
    if (action == "Back") {
        Packet data;

        data << 0;
        this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
    }
}

void MappingScene::handleKeyReleased(int playerID, std::string action)
{
}

void MappingScene::handleButtonClicked(int button)
{
    if (button == 0) {
        Packet data;

        data << 0;
        this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
    }
}

void MappingScene::handleConfig(std::vector<std::string> config)
{
}

void MappingScene::handleStartGame(Packet data)
{
}
