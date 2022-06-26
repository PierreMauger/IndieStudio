/*
** EPITECH PROJECT, 2022
** WinningScene.cpp
** File description:
** WinningScene
*/

#include "WinningScene.hpp"

using namespace neo;

WinningScene::WinningScene(std::shared_ptr<MessageBus> messageBus)
{
    float pos = -1.0f + 0.28f;

    this->_messageBus = messageBus;
    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);
    this->_objects[1] = std::make_unique<GameObject>(0, "Podium", glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.8f));
    this->_objects[1]->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
    this->_buttons[0] = std::make_unique<GameObject>(3, "Back", glm::vec3(pos, -0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
}

WinningScene::~WinningScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
    this->_objects.clear();
    this->_buttons.clear();
}

void WinningScene::update()
{
}

void WinningScene::loadScene()
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << object.second->getType() << object.first << *object.second;
    for (auto &button : this->_buttons)
        packet << button.second->getType() <<  button.first << *button.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(10.0f, 0.0f, 5.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 0 << glm::vec3(0.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
}

void WinningScene::handleKeyPressed(int playerID, std::string action)
{
}

void WinningScene::handleKeyReleased(int playerID, std::string action)
{
}

void WinningScene::handleButtonClicked(int button)
{
    if (button == 0) {
        Packet data;

        data << 0;
        this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
        data.clear();
        data << 0 << 0 << 0;
        data << 1 << 0 << 1;
        this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
    }
}

void WinningScene::handleConfig(std::vector<std::string> config)
{
}

void WinningScene::handleStartGame(Packet data)
{
    std::map<int, std::string> models;
    int it = 0;

    while (data.checkSize(1)) {
        std::string model;
        int place = 0;

        data >> model >> place;
        models[place] = (model);
    }
    std::vector<glm::vec3> pos;
    pos.push_back(glm::vec3(0.0f, 0.0f, 1.3f));
    pos.push_back(glm::vec3(0.0f, -1.8f, 0.5f));
    pos.push_back(glm::vec3(0.0f, 1.8f, -0.4f));
    pos.push_back(glm::vec3(0.0f, 3.6f, -2.0f));
    for (auto &model : models) {
        this->_objects[it + 2] = std::make_unique<GameObject>(4, model.second, pos[model.first - 1], glm::vec3(0.5f));
        this->_objects[it + 2]->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        it++;
    }
}
