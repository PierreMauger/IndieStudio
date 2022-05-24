/*
** EPITECH PROJECT, 2022
** Input.cpp
** File description:
** Input
*/

#include "Input.hpp"

using namespace neo;

Input::Input(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    this->_functionTab = {
        std::bind(&Input::receiveKeyConfig, this, std::placeholders::_1),
    };
}

void Input::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}

void Input::update()
{
    for (int i = 0; i < this->_configs.size(); i++)
        for (auto &conf : this->_configs[i].getActConfig())
            this->checkInputStatus(conf.second, conf.first, i);
}

void Input::checkInputStatus(int key, std::string action, int playerNb)
{
    if (key <= 25) {
        if (IsGamepadAvailable(0)) {
            this->checkButtonStatus(key, action, playerNb);
            this->checkJoystickStatus(key, action, playerNb);
        }
    } else {
        this->checkKeyStatus(key, action, playerNb);
    }
}

void Input::checkKeyStatus(int key, std::string action, int playerNb)
{
    if (IsKeyPressed(key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, 0, 1));
    }
    if (IsKeyReleased(key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, 1, 1));
    }
}

void Input::checkButtonStatus(int key, std::string action, int playerNb)
{
    if (IsGamepadButtonPressed(0, key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, 0, 1));
    } else if (IsGamepadButtonReleased(0, key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, 1, 1));
    }
}

float Input::checkAxisStatus(int gamepad, int key, std::string action)
{
    int axis = (key + 1) % 2;
    float value = GetGamepadAxisMovement(gamepad, axis);

    if (key % 4 < 2)
        value = -value;
    if (axis) {
        if (value < 0.5f)
            return value;
    } else {
        if (value > 0.5f)
            return value;
    }
    return 0;
}

void Input::checkJoystickStatus(int key, std::string action, int playerNb)
{
    if (key >= 18) {
        int i = key - 18;

        if (this->checkAxisStatus(0, key, action) && !this->_configs[playerNb].getAxisInputs()[i]) {
            Packet data;
            data << playerNb << action;
            this->postMessage(Message(data, 0, 1));
            this->_configs[playerNb].getAxisInputs()[i] = true;
        } else if (!this->checkAxisStatus(0, key, action) && this->_configs[playerNb].getAxisInputs()[i]) {
            Packet data;
            data << playerNb << action;
            this->postMessage(Message(data, 1, 1));
            this->_configs[playerNb].getAxisInputs()[i] = false;
        }
    }
}

void Input::editConfig(int key, std::string action)
{

}

void Input::receiveKeyConfig(Packet data)
{
    PlayerConfig config;

    data >> config;
    this->_configs.push_back(config);
}
