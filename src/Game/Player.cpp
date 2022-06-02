/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

neo::Player::Player(std::string name, glm::vec3 pos, glm::vec3 size)
: GameObject(0, name, pos, size), _speed(CAST(glm::vec3, 0, 0, 0)), _cooldown(5), _bombUp(0), _speedUp(0), _fireUp(0), _wallPass(false)
{
}

glm::vec3 neo::Player::getSpeed() const
{
	return this->_speed;
}