/*
** EPITECH PROJECT, 2022
** GameObject.cpp
** File description:
** GameObject
*/

#include "GameObject.hpp"

using namespace neo;

GameObject::GameObject(std::string name, Vector2 pos)
{
    this->_name = name;
    this->_pos = pos;
    this->_size = {1, 1};
}

GameObject::GameObject(std::string name, Vector2 pos, Vector2 size)
{
    this->_name = name;
    this->_pos = pos;
    this->_size = size;
}

std::string GameObject::getName() const
{
    return this->_name;
}

Vector2 GameObject::getPos() const
{
    return this->_pos;
}

Vector2 GameObject::getSize() const
{
    return this->_size;
}

void GameObject::setPos(Vector2 pos)
{
    this->_pos = pos;
}

void GameObject::move(Vector2 speed)
{
    this->_pos.x += speed.x;
    this->_pos.y += speed.y;
}
