/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

neo::Player::Player(std::string name, Vector2 pos)
: GameObject(0, name, pos), _speed(CAST(Vector2, 0, 0)), _cooldown(5), _bombUp(0), _speedUp(0), _fireUp(0), _wallPass(false)
{
}

Vector2 neo::Player::getSpeed() const
{
	return this->_speed;
}