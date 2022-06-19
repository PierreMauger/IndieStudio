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
    this->_playerModel.resize(4, 0);
    this->_playerConfig.resize(4, 0);
    this->_availableModels = {"RoboCat", "Asteroid1", "Asteroid2", "Asteroid3"};

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
    if (button < this->_playerConnected.size()) {
        if (!this->_playerConnected[button]) {
            this->addCard(button);
            this->_playerConnected[button] = true;
        }
    } else if (button / 4 == 1 || button / 4 == 2) {
        this->changeModel(button);
    } else if (button / 4 == 3 || button / 4 == 4) {
        this->changeConfig(button);
    } else if (button / 4 == 5 || button / 4 == 6 || button / 4 == 7) {
        this->changeMode(button);
    } else if (button / 4 == 8) {
        if (!this->_playerConnected[button]) {
            this->deleteCard(button % 4);
            this->_playerConnected[button % 4] = false;
        }
    }
}

void ConfigScene::handleConfig(std::vector<std::string> config)
{
    this->_availableConfigs = config;
}

void ConfigScene::addCard(int card)
{
    Packet data;
    float pos = -1.f + 0.28f + card * 0.48f;

    data << this->_buttons[card]->getType() << card;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(3, "Card", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.45f, 0.0f));
    this->_buttons[card + 4 * 1] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.23f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 2] = std::make_unique<GameObject>(3, "LeftArrow", glm::vec3(pos - 0.15f, 0.23f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 3] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.5f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 4] = std::make_unique<GameObject>(3, "LeftArrow", glm::vec3(pos - 0.15f, 0.5f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 5] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos - 0.15f, 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 6] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos        , 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 7] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_buttons[card + 4 * 8] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.18f, 0.05f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    this->_objects[card + 1] = std::make_unique<GameObject>(0, "RoboCat", glm::vec3(pos * 7.0f, -1.5f, 0.0f), glm::vec3(0.5f));
    this->_objects[card + 1]->setRotation(glm::vec3(270.0f, 0.0f, 0.0f));
    data << this->_buttons[card]->getType() << card << *this->_buttons[card];
    data << this->_buttons[card + 4 * 1]->getType() << card + 4 * 1 << *this->_buttons[card + 4 * 1];
    data << this->_buttons[card + 4 * 2]->getType() << card + 4 * 2 << *this->_buttons[card + 4 * 2];
    data << this->_buttons[card + 4 * 3]->getType() << card + 4 * 3 << *this->_buttons[card + 4 * 3];
    data << this->_buttons[card + 4 * 4]->getType() << card + 4 * 4 << *this->_buttons[card + 4 * 4];
    data << this->_buttons[card + 4 * 5]->getType() << card + 4 * 5 << *this->_buttons[card + 4 * 5];
    data << this->_buttons[card + 4 * 6]->getType() << card + 4 * 6 << *this->_buttons[card + 4 * 6];
    data << this->_buttons[card + 4 * 7]->getType() << card + 4 * 7 << *this->_buttons[card + 4 * 7];
    data << this->_buttons[card + 4 * 8]->getType() << card + 4 * 8 << *this->_buttons[card + 4 * 8];
    data << this->_objects[card + 1]->getType() << card + 1 << *this->_objects[card + 1];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::deleteCard(int card)
{
    Packet data;
    float pos = -1.f + 0.28f + card * 0.48f;

    data << this->_buttons[card]->getType() << card;
    data << this->_buttons[card + 4 * 1]->getType() << card + 4 * 1;
    data << this->_buttons[card + 4 * 2]->getType() << card + 4 * 2;
    data << this->_buttons[card + 4 * 3]->getType() << card + 4 * 3;
    data << this->_buttons[card + 4 * 4]->getType() << card + 4 * 4;
    data << this->_buttons[card + 4 * 5]->getType() << card + 4 * 5;
    data << this->_buttons[card + 4 * 6]->getType() << card + 4 * 6;
    data << this->_buttons[card + 4 * 7]->getType() << card + 4 * 7;
    data << this->_buttons[card + 4 * 8]->getType() << card + 4 * 8;
    data << this->_objects[card + 1]->getType() << card + 1;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    data << this->_buttons[card]->getType() << card << *this->_buttons[card];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::changeModel(int card)
{
    int size = this->_availableModels.size();
    float pos = -1.f + 0.28f + card * 0.48f;
    int playerNb = card % 4;
    Packet packet;

    if (card / 4 == 1) {
        this->_playerModel[playerNb] = (this->_playerModel[playerNb] + 1) % size;
    } else {
        this->_playerModel[playerNb] = (this->_playerModel[playerNb] + size - 1) % size;
    }
    this->_objects[playerNb + 1]->setName(this->_availableModels[this->_playerModel[playerNb]]);

    packet << this->_objects[playerNb + 1]->getType() << playerNb + 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::DELETE, Module::GRAPHICS));
    packet << *this->_objects[playerNb + 1];
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::changeConfig(int card)
{
    int size = this->_availableConfigs.size();

    if (card / 4 == 1) {
        this->_playerConfig[card % 4] = (this->_playerConfig[card % 4] + 1) % size;
    } else {
        this->_playerConfig[card % 4] = (this->_playerConfig[card % 4] + size - 1) % size;
    }
}

void ConfigScene::changeMode(int card)
{
    std::cout << "Change mode for player " << card % 4 << std::endl;
}
