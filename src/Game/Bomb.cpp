/*
** EPITECH PROJECT, 2022
** Bomb.cpp
** File description:
** Bomb
*/

#include "Bomb.hpp"

neo::Bomb::Bomb(std::string name, glm::vec3 pos, size_t fireUp, glm::vec3 scale) : GameObject(0, name, pos, scale)
{
    this->_timer = 3.0;
    this->_fireUp = fireUp;
}
