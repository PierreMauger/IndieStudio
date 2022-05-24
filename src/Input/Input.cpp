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
    for (auto &conf : this->_config.getActConfig())
        this->checkInputStatus(conf.second, conf.first, 0);
}

void Input::checkInputStatus(int key, std::string action, int playerNb)
{
    if (key <= 25) {
        if (IsGamepadAvailable(0)) {
            this->checkButtonStatus(key, action);
            this->checkJoystickStatus(key, action, playerNb);
        }
    } else {
        this->checkKeyStatus(key, action);
    }
}

void Input::checkKeyStatus(int key, std::string action)
{
    if (IsKeyPressed(key)) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
    }
    if (IsKeyReleased(key)) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
    }
}

void Input::checkButtonStatus(int key, std::string action)
{
    if (IsGamepadButtonPressed(0, key)) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
    }
    if (IsGamepadButtonReleased(0, key)) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
    }
}

void Input::checkJoystickStatus(int key, std::string action, int playerNb)
{
    if (GetGamepadAxisMovement(0, 1) < -0.5f && !this->_config.getAxisInputs()[0] && key == 18) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
        this->_config.getAxisInputs()[0] = true;
    } else if (GetGamepadAxisMovement(0, 1) > -0.5f && this->_config.getAxisInputs()[0] && key == 18) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
        this->_config.getAxisInputs()[0] = false;
    }

    if (GetGamepadAxisMovement(0, 0) > 0.5f && !this->_config.getAxisInputs()[1] && key == 19) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
        this->_config.getAxisInputs()[1] = true;
    } else if (GetGamepadAxisMovement(0, 0) < 0.5f && this->_config.getAxisInputs()[1] && key == 19) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
        this->_config.getAxisInputs()[1] = false;
    }

    if (GetGamepadAxisMovement(0, 1) > 0.5f && !this->_config.getAxisInputs()[2] && key == 20) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
        this->_config.getAxisInputs()[2] = true;
    } else if (GetGamepadAxisMovement(0, 1) < 0.5f && this->_config.getAxisInputs()[2] && key == 20) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
        this->_config.getAxisInputs()[2] = false;
    }

    if (GetGamepadAxisMovement(0, 0) < -0.5f && !this->_config.getAxisInputs()[3] && key == 21) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 0, 1));
        this->_config.getAxisInputs()[3] = true;
    } else if (GetGamepadAxisMovement(0, 0) > -0.5f && this->_config.getAxisInputs()[3] && key == 21) {
        Packet data;
        data << action;
        this->postMessage(Message(data, 1, 1));
        this->_config.getAxisInputs()[3] = false;
    }
}

void Input::editConfig(int key, std::string action)
{

}

void Input::receiveKeyConfig(Packet data)
{
    data >> this->_config;
}
