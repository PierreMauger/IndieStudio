/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

neo::Player::Player(std::string name, glm::vec3 pos, glm::vec3 scale)
: GameObject(0, name, pos, scale), _speed(glm::vec3(0.0f)), _cooldown(5), _bombUp(0), _speedUp(0), _fireUp(0), _wallPass(false)
{
}

glm::vec3 neo::Player::getSpeed() const
{
	return this->_speed;
}

void neo::Player::addX(float val)
{
	_speed.x += val;
}

void neo::Player::addY(float val)
{
	_speed.y += val;
}
