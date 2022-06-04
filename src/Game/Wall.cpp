/*
** EPITECH PROJECT, 2022
** Wall.cpp
** File description:
** Wall
*/

#include "Wall.hpp"

neo::Wall::Wall(std::string name, glm::vec3 pos, bool isDestructible, glm::vec3 scale) : GameObject(0, name, pos, scale)
{
    this->_isDestructible = isDestructible;
}