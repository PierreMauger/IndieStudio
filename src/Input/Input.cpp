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
    this->_axisInputs.reserve(8);
    for (int i = 0; i < 8; i++)
        this->_axisInputs.push_back(false);

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
    this->checkInputStatus(this->_config.getActConfig()["MoveRight"]);
    this->checkInputStatus(this->_config.getActConfig()["MoveLeft"]);
    this->checkInputStatus(this->_config.getActConfig()["MoveUp"]);
    this->checkInputStatus(this->_config.getActConfig()["MoveDown"]);
}

void Input::checkInputStatus(int key)
{
    if (key <= 25) {
        this->checkButtonStatus(key);
        this->checkJoystickStatus(key);
    } else {
        this->checkKeyStatus(key);
    }
}

void Input::checkKeyStatus(int key)
{
    if (IsKeyPressed(key)) {
        Packet data;
        data << key;
        this->postMessage(Message(data, 0, 1));
    }
    if (IsKeyReleased(key)) {
        Packet data;
        data << key;
        this->postMessage(Message(data, 1, 1));
    }
}

void Input::checkButtonStatus(int key)
{
    if (IsGamepadButtonPressed(0, key)) {
        Packet data;
        data << key;
        this->postMessage(Message(data, 0, 1));
    }
    if (IsGamepadButtonReleased(0, key)) {
        Packet data;
        data << key;
        this->postMessage(Message(data, 1, 1));
    }
}

void Input::checkJoystickStatus(int key)
{
    if (IsGamepadAvailable(0)) {

        if (GetGamepadAxisMovement(0, 1) < -0.5f && !this->_axisInputs[0] && key == 18) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[0] = true;
        } else if (GetGamepadAxisMovement(0, 1) > -0.5f && this->_axisInputs[0] && key == 18) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[0] = false;
        }

        if (GetGamepadAxisMovement(0, 0) > 0.5f && !this->_axisInputs[1] && key == 19) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[1] = true;
        } else if (GetGamepadAxisMovement(0, 0) < 0.5f && this->_axisInputs[1] && key == 19) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[1] = false;
        }

        if (GetGamepadAxisMovement(0, 1) > 0.5f && !this->_axisInputs[2] && key == 20) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[2] = true;
        } else if (GetGamepadAxisMovement(0, 1) < 0.5f && this->_axisInputs[2] && key == 20) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[2] = false;
        }

        if (GetGamepadAxisMovement(0, 0) < -0.5f && !this->_axisInputs[3] && key == 21) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[3] = true;
        } else if (GetGamepadAxisMovement(0, 0) > -0.5f && this->_axisInputs[3] && key == 21) {
            Packet data;
            data << key - 17;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[3] = false;
        }
    }
}

void Input::editConfig(int key, std::string action)
{

}

void Input::receiveKeyConfig(Packet data)
{
    data >> this->_config;
}
