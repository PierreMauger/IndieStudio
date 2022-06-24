/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb
*/

#include "Bomb.hpp"

using namespace neo;

Bomb::Bomb(std::string name, glm::vec3 pos, size_t fireUp, size_t playerId, glm::vec3 scale) : GameObject(0, name, pos, scale)
{
    this->_timer = GetTime();
    this->_fireUp = fireUp;
    this->_playerId = playerId;
    this->_state = 0;
    this->_stop = {false};
}

double &Bomb::getTimer()
{
    return this->_timer;
}

int &Bomb::getState()
{
    return this->_state;
}

bool &Bomb::getStop(size_t id)
{
    return this->_stop[id];
}

std::map<int, std::unique_ptr<GameObject>> &Bomb::getExplosions()
{
    return this->_explosions;
}

const size_t Bomb::getPlayerId() const
{
    return this->_playerId;
}

const size_t Bomb::getFireUp() const
{
    return _fireUp;
}
