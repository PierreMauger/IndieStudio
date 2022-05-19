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
    std::cout << "Input module created" << std::endl;
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
    for (int i = KEY_RIGHT; i <= KEY_UP; i++) {
        if (IsKeyPressed(i)) {
            Packet data;
            data << i;
            this->postMessage(Message(data, 0, 1));
        }
        if (IsKeyReleased(i)) {
            Packet data;
            data << i;
            this->postMessage(Message(data, 1, 1));
        }
    }
    if (IsGamepadAvailable(0)) {
        for (int i = GAMEPAD_BUTTON_LEFT_FACE_UP; i <= GAMEPAD_BUTTON_RIGHT_THUMB; i++) {
            if (IsGamepadButtonPressed(0, i)) {
                Packet data;
                data << i;
                this->postMessage(Message(data, 0, 1));
            }
            if (IsGamepadButtonReleased(0, i)) {
                Packet data;
                data << i;
                this->postMessage(Message(data, 1, 1));
            }
        }
        if (GetGamepadAxisMovement(0, 0) > 0.5f && !this->_axisInputs[0]) {
            Packet data;
            data << 2;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[0] = true;
        } else if (GetGamepadAxisMovement(0, 0) < 0.5f && this->_axisInputs[0]) {
            Packet data;
            data << 2;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[0] = false;
        }

        if (GetGamepadAxisMovement(0, 1) > 0.5f && !this->_axisInputs[1]) {
            Packet data;
            data << 3;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[1] = true;
        } else if (GetGamepadAxisMovement(0, 1) < 0.5f && this->_axisInputs[1]) {
            Packet data;
            data << 3;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[1] = false;
        }

        if (GetGamepadAxisMovement(0, 0) < -0.5f && !this->_axisInputs[2]) {
            Packet data;
            data << 4;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[2] = true;
        } else if (GetGamepadAxisMovement(0, 0) > -0.5f && this->_axisInputs[2]) {
            Packet data;
            data << 4;
            this->postMessage(Message(data, 1, 1));
            this->_axisInputs[2] = false;
        }

        if (GetGamepadAxisMovement(0, 1) < -0.5f && !this->_axisInputs[3]) {
            Packet data;
            data << 1;
            this->postMessage(Message(data, 0, 1));
            this->_axisInputs[3] = true;
        } else if (GetGamepadAxisMovement(0, 1) > -0.5f && this->_axisInputs[3]) {
            Packet data;
            data << 1;
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
    for (auto &it : this->_config)
        std::cout << it.first << ": " << it.second << std::endl;
}
