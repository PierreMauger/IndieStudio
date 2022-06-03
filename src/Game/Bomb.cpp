/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb
*/

#include "Bomb.hpp"

neo::Bomb::Bomb(double timer, size_t fireUp, size_t playerId)
{
    this->_timer = timer;
    this->_fireUp = fireUp;
    this->_playerId = playerId;
}
