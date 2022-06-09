/*
** EPITECH PROJECT, 2022
** PlayerConfig.cpp
** File description:
** PlayerConfig
*/

#include "PlayerConfig.hpp"

using namespace neo;

PlayerConfig::PlayerConfig()
{
    this->_axisInputs.reserve(8);
    for (int i = 0; i < 8; i++)
        this->_axisInputs.push_back(false);
}

std::map<std::string, int> &PlayerConfig::getActConfig()
{
    if (this->_mode)
        return this->_controllerConfig;
    else
        return this->_keyboardConfig;
}

std::map<std::string, int> &PlayerConfig::getKeyboardConfig()
{
    return this->_keyboardConfig;
}

std::map<std::string, int> &PlayerConfig::getControllerConfig()
{
    return this->_controllerConfig;
}

std::map<std::string, bool> &PlayerConfig::getButtonInputs()
{
    return this->_buttonInputs;
}

std::vector<bool> &PlayerConfig::getAxisInputs()
{
    return this->_axisInputs;
}

bool PlayerConfig::getMode() const
{
    return this->_mode;
}

void PlayerConfig::setKeyboardConfig(std::map<std::string, int> config)
{
    this->_keyboardConfig = config;
    for (auto &conf : this->_keyboardConfig)
        this->_buttonInputs[conf.first] = false;
}

void PlayerConfig::setControllerConfig(std::map<std::string, int> config)
{
    this->_controllerConfig = config;
}

void PlayerConfig::setMode(bool mode)
{
    this->_mode = mode;
}

void PlayerConfig::setKey(bool mode, std::string action, int key)
{
    if (mode)
        this->_controllerConfig[action] = key;
    else
        this->_keyboardConfig[action] = key;
}
