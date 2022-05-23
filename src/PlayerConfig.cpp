/*
** EPITECH PROJECT, 2022
** PlayerConfig.cpp
** File description:
** PlayerConfig
*/

#include "PlayerConfig.hpp"

using namespace neo;

std::map<std::string, int> PlayerConfig::getConfig() const
{
    if (this->_mode)
        return this->_controllerConfig;
    else
        return this->_keyboardConfig;
}

bool PlayerConfig::getMode() const
{
    return this->_mode;
}

void PlayerConfig::setKeyboardConfig(std::map<std::string, int> config)
{
    this->_keyboardConfig = config;
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
