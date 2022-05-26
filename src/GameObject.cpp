/*
** EPITECH PROJECT, 2022
** GameObject.cpp
** File description:
** GameObject
*/

#include "GameObject.hpp"

using namespace neo;

GameObject::GameObject(std::string name, Vector2 position)
{
    this->_name = name;
    this->_position = position;
}

std::string GameObject::getName() const
{
    return this->_name;
}

Vector2 GameObject::getPosition() const
{
    return this->_position;
}

void GameObject::setPosition(Vector2 position)
{
    this->_position = position;
}

void GameObject::move(Vector2 speed)
{
    this->_position.x += speed.x;
    this->_position.y += speed.y;
}
