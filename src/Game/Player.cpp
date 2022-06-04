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
}

glm::vec3 neo::Player::getSpeed() const
{
	return this->_speed;
}

void neo::Player::addX(float val)
{
	this->_speed.x += val;
}

void neo::Player::addY(float val)
{
	this->_speed.y += val;
}
