/*
** EPITECH PROJECT, 2022
** GameObject.cpp
** File description:
** GameObject
*/

#include "GameObject.hpp"

using namespace neo;

GameObject::GameObject(int type, std::string name, Vector2 pos)
{
    this->_type = type;
    this->_name = name;
    this->_pos = pos;
    this->_size = {1, 1};
}

GameObject::GameObject(int type, std::string name, Vector2 pos, Vector2 size)
{
    this->_type = type;
    this->_name = name;
    this->_pos = pos;
    this->_size = size;
}

int GameObject::getType() const
{
    return this->_type;
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

void GameObject::setType(int type)
{
    this->_type = type;
}

void GameObject::setName(std::string name)
{
    this->_name = name;
}

void GameObject::setPos(Vector2 pos)
{
    this->_pos = pos;
}

void GameObject::setSize(Vector2 size)
{
    this->_size = size;
}

void GameObject::move(Vector2 speed)
{
    this->_pos.x += speed.x;
    this->_pos.y += speed.y;
}
