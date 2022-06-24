/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb
*/

#include "Bomb.hpp"

using namespace neo;

Bomb::Bomb(std::string name, glm::vec3 pos, size_t fireUp, size_t playerId, glm::vec3 scale) : GameObject(1, name, pos, scale)
{
    this->_timer = GetTime();
    this->_fireUp = fireUp;
    this->_playerId = playerId;
}

double &Bomb::getTimer()
{
    return this->_timer;
}

const size_t Bomb::getPlayerId() const
{
    return this->_playerId;
}

const size_t Bomb::getFireUp() const
{
    return _fireUp;
}
