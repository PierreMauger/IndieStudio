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
    this->_availableModels = {"RoboCat", "Asteroid1", "Asteroid2", "Asteroid3"};
    this->_playerConnected.resize(4, false);
    this->_playerModel.resize(4, 0);
    this->_playerConfig.resize(4, 0);
    this->_playerMode.resize(4, 0);

    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(70.0f));
    this->_objects[0]->setShiny(false);

    float pos = -1.0f + 0.28f;
    this->_buttons[0] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos            , 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[1] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 1 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[2] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 2 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[3] = std::make_unique<GameObject>(2, "Connect", glm::vec3(pos + 3 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[36] = std::make_unique<GameObject>(2, "Back", glm::vec3(pos, -0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    this->_buttons[37] = std::make_unique<GameObject>(2, "Start", glm::vec3(pos + 3 * 0.48f, -0.45f, 0.0f), glm::vec3(0.2f, 0.2f, 0.0f));
    for (int card = 0; card < 4; card++) {
        pos = -1.0f + 0.28f + card * 0.48f;

        this->_buttons[card + 4 * 1] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.23f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 2] = std::make_unique<GameObject>(3, "LeftArrow", glm::vec3(pos - 0.15f, 0.23f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 3] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.5f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 4] = std::make_unique<GameObject>(3, "LeftArrow", glm::vec3(pos - 0.15f, 0.5f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 5] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos - 0.15f, 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 6] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos        , 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 7] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.15f, 0.8f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
        this->_buttons[card + 4 * 8] = std::make_unique<GameObject>(3, "RightArrow", glm::vec3(pos + 0.18f, 0.05f, 0.0f), glm::vec3(0.02f, 0.05f, 0.0f));
    }
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
        if (object.first < 1)
            packet << object.second->getType() << object.first << *object.second;
    for (auto &button : this->_buttons)
        if (button.first < 4 || button.first > 35)
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
    if (button == 36) {
        for (int i = 0; i < this->_playerConnected.size(); i++)
            if (this->_playerConnected[i]) {
                this->deleteCard(i);
                this->_playerConnected[i] = false;
                this->_playerModel[i] = 0;
                this->_playerConfig[i] = 0;
                this->_playerMode[i] = 0;
            }
        Packet data;
        data << 0;
        this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
        data.clear();
        data << 0 << this->_playerConfig[0] << this->_playerMode[0];
        this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
    } else if (button == 37) {
        this->_messageBus->sendMessage(Message(Packet(), CoreCommand::START_GAME, Module::CORE));
        Packet data;
        data << 2;
        this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
    }
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
        if (this->_playerConnected[button % 4]) {
            this->deleteCard(button % 4);
            this->_playerConnected[button % 4] = false;
        }
    }
}

void ConfigScene::handleConfig(std::vector<std::string> config)
{
    this->_availableConfigs = config;
}

void ConfigScene::handleStartGame(Packet data)
{
}

void ConfigScene::addCard(int card)
{
    float pos = -1.0f + 0.28f + card * 0.48f;
    Packet data;

    data << this->_buttons[card]->getType() << card;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(3, "Card", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.45f, 0.0f));
    this->_objects[card + 1] = std::make_unique<GameObject>(0, this->_availableModels[this->_playerModel[card]], glm::vec3(pos * 7.0f, -1.5f, 0.0f), glm::vec3(0.5f));
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

    data.clear();
    data << card << this->_playerConfig[card] << this->_playerModel[card];
    this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::deleteCard(int card)
{
    float pos = -1.0f + 0.28f + card * 0.48f;
    Packet data;

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

    data.clear();
    data << card << this->_playerConfig[card] << 3;
    this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::changeModel(int card)
{
    int size = this->_availableModels.size();
    float pos = -1.0f + 0.28f + card * 0.48f;
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
    int playerNb = card % 4;
    Packet packet;

    if (card / 4 == 3) {
        this->_playerConfig[playerNb] = (this->_playerConfig[playerNb] + 1) % size;
    } else {
        this->_playerConfig[playerNb] = (this->_playerConfig[playerNb] + size - 1) % size;
    }
    packet << playerNb << this->_playerConfig[playerNb] << this->_playerMode[playerNb];
    this->_messageBus->sendMessage(Message(packet, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::changeMode(int card)
{
    int playerNb = card % 4;
    Packet packet;

    if (card / 4 == 5) {
        this->_playerMode[playerNb] = 0;
    } else if (card / 4 == 6) {
        this->_playerMode[playerNb] = 1;
    } else {
        this->_playerMode[playerNb] = 2;
    }
    packet << playerNb << this->_playerConfig[playerNb] << this->_playerMode[playerNb];
    this->_messageBus->sendMessage(Message(packet, InputCommand::CHANGE_CONFIG, Module::INPUT));
}
