/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb
*/

#include "Bomb.hpp"

neo::Bomb::Bomb(std::string name, glm::vec3 pos, size_t fireUp, size_t playerId, glm::vec3 scale) : GameObject(0, name, pos, scale)
{
    this->_timer = GetTime();
    this->_fireUp = fireUp;
    this->_playerId = playerId;
}

const double neo::Bomb::getTimer() const
{
    return this->_timer;
}

const size_t neo::Bomb::getPlayerId() const
{
    return this->_playerId;
}

const size_t neo::Bomb::getFireUp() const
{
    return _fireUp;
}