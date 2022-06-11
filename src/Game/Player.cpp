/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

neo::Player::Player(std::string name, glm::vec3 pos, glm::vec3 scale) : GameObject(0, name, pos, scale)
{
    this->_speed = glm::vec3(0.0f);
    this->_bombUp = 0;
    this->_speedUp = 0;
    this->_fireUp = 0;
    this->_wallPass = false;
    for (int i = 0; i < 4; i++)
        this->_direction[i] = false;
}

glm::vec3 &neo::Player::getSpeed()
{
	return this->_speed;
}

bool &neo::Player::getDirection(int axis)
{
    return this->_direction[axis];
}

size_t &neo::Player::getBombUp() {
    return this->_bombUp;
}

size_t &neo::Player::getSpeedUp()
{
    return this->_speedUp;
}

size_t &neo::Player::getFireUp()
{
    return this->_fireUp;
}

bool &neo::Player::getWallPass()
{
    return this->_wallPass;
}
