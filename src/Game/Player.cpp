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

void neo::Player::setSpeed(glm::vec3 speed)
{
    this->_speed = speed;
}

bool neo::Player::getDirection(int axis) const
{
    if (axis < 0 || axis > 3)
        return false;
    return this->_direction[axis];
}

void neo::Player::setDirection(int axis, bool val)
{
    if (axis < 0 || axis > 3)
        return;
    this->_direction[axis] = val;
}
