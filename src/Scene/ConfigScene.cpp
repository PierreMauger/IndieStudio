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
    this->_availableModels = {"Red", "Yellow", "Green", "Blue"};
    this->_playerConnected.resize(4, false);
    this->_playerModel.resize(4, 0);
    this->_playerConfig.resize(4, 0);
    this->_playerMode.resize(4, 0);
    this->_map = this->_mapGenerator.generateProceduralMap(0, 20, 20);

    this->_objects[0] = std::make_unique<GameObject>(0, "SphereBackground", glm::vec3(0.0f), glm::vec3(100.0f));
    this->_objects[0]->setShiny(false);

    int it = 0;
    for (int i = 0; i < this->_map.size(); i++) {
        for (int j = 0; j < this->_map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)this->_map[i].size() - 1) / 2, -j + ((float)this->_map.size() - 1) / 2 + 12.5f, -50.0f};
            if (this->_map[i][j] == '#')
                this->_objects[it++ + 5] = std::make_unique<GameObject>(0, "Block", pos, glm::vec3(0.5f));
            else if (this->_map[i][j] == 'W')
                this->_objects[it++ + 5] = std::make_unique<GameObject>(0, "Wall", pos, glm::vec3(0.5f));
        }
    }

    float pos = -1.0f + 0.28f;
    this->_buttons[0] = std::make_unique<GameObject>(3, "Add", glm::vec3(pos            , 0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    this->_buttons[1] = std::make_unique<GameObject>(3, "Add", glm::vec3(pos + 1 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    this->_buttons[2] = std::make_unique<GameObject>(3, "Add", glm::vec3(pos + 2 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    this->_buttons[3] = std::make_unique<GameObject>(3, "Add", glm::vec3(pos + 3 * 0.48f, 0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    this->_buttons[44] = std::make_unique<GameObject>(3, "Back", glm::vec3(pos, -0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    this->_buttons[45] = std::make_unique<GameObject>(3, "Reload", glm::vec3(pos + 2.2 * 0.48f, -0.45f, 0.0f), glm::vec3(0.1f, 0.17f, 0.0f));
    this->_buttons[46] = std::make_unique<GameObject>(3, "Play", glm::vec3(pos + 3 * 0.48f, -0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    for (int card = 0; card < 4; card++) {
        pos = -1.0f + 0.28f + card * 0.48f;

        this->_buttons[card + 4 * 1] = std::make_unique<GameObject>(3, "Right", glm::vec3(pos + 0.175f, 0.23f, 0.0f), glm::vec3(0.02f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 2] = std::make_unique<GameObject>(3, "Left", glm::vec3(pos - 0.175f, 0.23f, 0.0f), glm::vec3(0.02f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 3] = std::make_unique<GameObject>(3, "Right", glm::vec3(pos + 0.15f, 0.55f, 0.0f), glm::vec3(0.02f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 4] = std::make_unique<GameObject>(3, "Left", glm::vec3(pos - 0.15f, 0.55f, 0.0f), glm::vec3(0.02f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 5] = std::make_unique<GameObject>(3, "Keyboard", glm::vec3(pos - 0.12f, 0.75f, 0.0f), glm::vec3(0.04f, 0.07f, 0.0f));
        this->_buttons[card + 4 * 6] = std::make_unique<GameObject>(3, "Controller", glm::vec3(pos        , 0.75f, 0.0f), glm::vec3(0.04f, 0.07f, 0.0f));
        this->_buttons[card + 4 * 7] = std::make_unique<GameObject>(3, "AI", glm::vec3(pos + 0.12f, 0.75f, 0.0f), glm::vec3(0.04f, 0.07f, 0.0f));
        this->_buttons[card + 4 * 8] = std::make_unique<GameObject>(3, "Close", glm::vec3(pos + 0.175f, 0.05f, 0.0f), glm::vec3(0.02f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 9] = std::make_unique<GameObject>(2, "", glm::vec3(pos, 0.55f, 0.0f), glm::vec3(0.1f, 0.035f, 0.0f));
        this->_buttons[card + 4 * 10] = std::make_unique<GameObject>(3, "Select", glm::vec3(pos - 0.12f, 0.75f, 0.0f), glm::vec3(0.04f, 0.070f, 0.0f));
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

    for (int i = 0; i < 4; i++)
        this->_buttons[i + 4 * 9]->setName(this->_availableConfigs[this->_playerConfig[i]]);

    for (auto &object : this->_objects)
        if (object.first < 1 || object.first > 4)
            packet << object.second->getType() << object.first << *object.second;
    for (auto &button : this->_buttons)
        if (button.first < 4 || button.first > 43)
            packet << button.second->getType() <<  button.first << *button.second;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));

    packet.clear();
    packet << 0 << glm::vec3(0.0f, 0.0f, 10.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_POS, Module::GRAPHICS));
    packet.clear();
    packet << 0 << glm::vec3(0.0f);
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::SET_CAMERA_NEXT_POS, Module::GRAPHICS));
}

void ConfigScene::handleKeyPressed(int playerID, std::string action)
{
    if (action == "Back")
        this->buttonBack();
}

void ConfigScene::handleKeyReleased(int playerID, std::string action)
{
}

void ConfigScene::handleButtonClicked(int button)
{
    if (button < this->_playerConnected.size()) {
        this->buttonAdd(button);
        return;
    }
    switch (button < 44 ? button / 4 : button) {
        case 1: case 2:
            this->changeModel(button);
            break;
        case 3: case 4:
            this->changeConfig(button);
            break;
        case 5: case 6: case 7:
            this->changeMode(button);
            break;
        case 8:
            this->buttonDelete(button % 4);
            break;
        case 44:
            this->buttonBack();
            break;
        case 45:
            this->buttonReset();
            break;
        case 46:
            this->buttonStart();
            break;
        default:
            break;
    }
    Packet playSound;
    playSound << "buttonClick.mp3";
    this->_messageBus->sendMessage(Message(playSound, AudioCommand::PLAY_SOUND, Module::AUDIO));
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
    this->_objects[card + 1] = std::make_unique<GameObject>(4, this->_availableModels[this->_playerModel[card]], glm::vec3(pos * 7.0f, -1.5f, 0.0f), glm::vec3(0.5f));
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
    data << this->_buttons[card + 4 * 9]->getType() << card + 4 * 9 << *this->_buttons[card + 4 * 9];
    data << this->_buttons[card + 4 * 10]->getType() << card + 4 * 10 << *this->_buttons[card + 4 * 10];
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
    data << this->_buttons[card + 4 * 9]->getType() << card + 4 * 9;
    data << this->_buttons[card + 4 * 10]->getType() << card + 4 * 10;
    data << this->_objects[card + 1]->getType() << card + 1;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    this->_buttons[card] = std::make_unique<GameObject>(3, "Add", glm::vec3(pos, 0.45f, 0.0f), glm::vec3(0.2f, 0.35f, 0.0f));
    data << this->_buttons[card]->getType() << card << *this->_buttons[card];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));

    data.clear();
    data << card % 4 << this->_playerConfig[card] << 3;
    this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::changeModel(int card)
{
    int size = this->_availableModels.size();
    float pos = -1.0f + 0.28f + card * 0.48f;
    int playerID = card % 4;
    Packet packet;

    if (card / 4 == 1) {
        this->_playerModel[playerID] = (this->_playerModel[playerID] + 1) % size;
    } else {
        this->_playerModel[playerID] = (this->_playerModel[playerID] + size - 1) % size;
    }
    this->_objects[playerID + 1]->setName(this->_availableModels[this->_playerModel[playerID]]);

    packet << this->_objects[playerID + 1]->getType() << playerID + 1;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::DELETE, Module::GRAPHICS));
    packet << *this->_objects[playerID + 1];
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::changeConfig(int card)
{
    int size = this->_availableConfigs.size();
    int playerID = card % 4;
    Packet packet;

    if (card / 4 == 3) {
        this->_playerConfig[playerID] = (this->_playerConfig[playerID] + 1) % size;
    } else {
        this->_playerConfig[playerID] = (this->_playerConfig[playerID] + size - 1) % size;
    }
    this->_buttons[playerID + 4 * 9]->setName(this->_availableConfigs[this->_playerConfig[playerID]]);

    packet << this->_buttons[playerID + 4 * 9]->getType() << playerID + 4 * 9;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::DELETE, Module::GRAPHICS));
    packet << *this->_buttons[playerID + 4 * 9];
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));
    packet.clear();

    packet << playerID << this->_playerConfig[playerID] << this->_playerMode[playerID];
    this->_messageBus->sendMessage(Message(packet, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::changeMode(int card)
{
    int playerID = card % 4;
    float pos = -1.0f + 0.28f + playerID * 0.48f;
    Packet packet;

    if (card / 4 == 5) {
        this->_playerMode[playerID] = 0;
    } else if (card / 4 == 6) {
        this->_playerMode[playerID] = 1;
    } else {
        this->_playerMode[playerID] = 2;
    }

    packet << this->_buttons[playerID + 4 * 10]->getType() << playerID + 4 * 10;
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::DELETE, Module::GRAPHICS));
    this->_buttons[playerID + 4 * 10]->setPos(glm::vec3(pos - 0.12f + 0.12f * this->_playerMode[playerID], 0.75f, 0.0f));
    packet << *this->_buttons[playerID + 4 * 10];
    this->_messageBus->sendMessage(Message(packet, GraphicsCommand::ADD, Module::GRAPHICS));

    packet.clear();
    packet << playerID << this->_playerConfig[playerID] << this->_playerMode[playerID];
    this->_messageBus->sendMessage(Message(packet, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::buttonAdd(int playerID)
{
    if (!this->_playerConnected[playerID]) {
        this->addCard(playerID);
        this->_playerConnected[playerID] = true;
    }
}

void ConfigScene::buttonDelete(int playerID)
{
    if (this->_playerConnected[playerID]) {
        this->deleteCard(playerID);
        this->_playerConnected[playerID] = false;
    }
}

void ConfigScene::buttonBack()
{
    Packet data;

    for (int i = 0; i < this->_playerConnected.size(); i++)
        if (this->_playerConnected[i]) {
            this->deleteCard(i);
            this->_playerConnected[i] = false;
            this->_playerModel[i] = 0;
            this->_playerConfig[i] = 0;
            this->_playerMode[i] = 0;
        }
    data << 0;
    this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
    data.clear();
    data << 0 << this->_playerConfig[0] << 0;
    data << 1 << this->_playerConfig[0] << 1;
    this->_messageBus->sendMessage(Message(data, InputCommand::CHANGE_CONFIG, Module::INPUT));
}

void ConfigScene::buttonReset()
{
    Packet data;

    this->_map = this->_mapGenerator.generateProceduralMap(0, 20, 20);
    for (int i = 5; i < this->_objects.size(); i++)
        data << this->_objects[i]->getType() << i;
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::DELETE, Module::GRAPHICS));
    data.clear();

    int it = 0;
    for (int i = 0; i < this->_map.size(); i++) {
        for (int j = 0; j < this->_map[i].size(); j++) {
            glm::vec3 pos = {i - ((float)this->_map[i].size() - 1) / 2, -j + ((float)this->_map.size() - 1) / 2 + 12.5f, -50.0f};
            if (this->_map[i][j] == '#')
                this->_objects[it++ + 5] = std::make_unique<GameObject>(0, "Block", pos, glm::vec3(0.5f));
            else if (this->_map[i][j] == 'W')
                this->_objects[it++ + 5] = std::make_unique<GameObject>(0, "Wall", pos, glm::vec3(0.5f));
        }
    }
    data.clear();
    for (int i = 5; i < this->_objects.size(); i++)
        data << this->_objects[i]->getType() << i << *this->_objects[i];
    this->_messageBus->sendMessage(Message(data, GraphicsCommand::ADD, Module::GRAPHICS));
}

void ConfigScene::buttonStart()
{
    Packet data;

    data << 3;
    this->_map = this->_mapGenerator.setPlayer(this->_map, this->_playerConnected, this->_playerMode);
    data << static_cast<int>(this->_map.size());
    for (auto &line : this->_map)
        data << line;
    for (int i = 0; i < this->_playerConnected.size(); i++)
        if (this->_playerConnected[i])
            data << this->_availableModels[this->_playerModel[i]];
    this->_messageBus->sendMessage(Message(data, CoreCommand::START_GAME, Module::CORE));

    data.clear();
    data << 3;
    this->_messageBus->sendMessage(Message(data, CoreCommand::CHANGE_SCENE, Module::CORE));
    for (int i = 0; i < this->_playerConnected.size(); i++)
        if (this->_playerConnected[i]) {
            this->_playerConnected[i] = false;
            this->_playerModel[i] = 0;
            this->_playerConfig[i] = 0;
            this->_playerMode[i] = 0;
        }
}
