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

void Input::run()
{
    SetTargetFPS(60);

    while (this->_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        this->update();
        this->_messageBus->notify(Module::INPUT);
    }
}

void Input::update()
{
    for (int i = 0; i < this->_configs.size(); i++)
        for (auto &conf : this->_configs[i].getActConfig())
            this->checkInputStatus(conf.second, conf.first, i);
}

void Input::editConfig(int key, std::string action)
{

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
        this->postMessage(Message(data, CoreCommand::KEY_PRESSED, Module::CORE));
    }
    if (IsKeyReleased(key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, CoreCommand::KEY_RELEASED, Module::CORE));
    }
}

void Input::checkButtonStatus(int key, std::string action, int playerNb)
{
    if (IsGamepadButtonPressed(0, key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, CoreCommand::KEY_PRESSED, Module::CORE));
    } else if (IsGamepadButtonReleased(0, key)) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, CoreCommand::KEY_RELEASED, Module::CORE));
    }
}

float Input::checkAxisStatus(int gamepad, int key, std::string action)
{
    int axis = (key + 1) % 2;
    float value = GetGamepadAxisMovement(gamepad, key >= 22 ? axis + 2 : axis);

    if (key % 4 < 2)
        value = -value;
    if (axis && value < -0.5f)
        return value;
    else if (!axis && value > 0.5f)
        return value;
    return 0;
}

void Input::checkJoystickStatus(int key, std::string action, int playerNb)
{
    int i = key - 18;

    if (i < 0)
        return;
    if (this->checkAxisStatus(0, key, action) && !this->_configs[playerNb].getAxisInputs()[i]) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, CoreCommand::KEY_PRESSED, Module::CORE));
        this->_configs[playerNb].getAxisInputs()[i] = true;
    } else if (!this->checkAxisStatus(0, key, action) && this->_configs[playerNb].getAxisInputs()[i]) {
        Packet data;
        data << playerNb << action;
        this->postMessage(Message(data, CoreCommand::KEY_RELEASED, Module::CORE));
        this->_configs[playerNb].getAxisInputs()[i] = false;
    }
}

void Input::receiveKeyConfig(Packet data)
{
    PlayerConfig config;

    while (data.checkSize(1)) {
        data >> config;
        this->_configs.push_back(config);
    }
}
