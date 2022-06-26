/*
** EPITECH PROJECT, 2022
** GameObject.cpp
** File description:
** GameObject
*/

#include "GameObject.hpp"

using namespace neo;

GameObject::GameObject(int type, std::string name, glm::vec3 pos, glm::vec3 scale)
{
    this->_type = type;
    this->_name = name;
    this->_pos = pos;
    this->_scale = scale;
    this->_rotation = glm::vec3(0.0f);
    this->_shiny = true;
}

int GameObject::getType() const
{
    return this->_type;
}

std::string GameObject::getName() const
{
    return this->_name;
}

glm::vec3 GameObject::getPos() const
{
    return this->_pos;
}

glm::vec3 GameObject::getScale() const
{
    return this->_scale;
}

glm::vec3 GameObject::getRotation() const
{
    return this->_rotation;
}

bool GameObject::getShiny() const
{
    return this->_shiny;
}

void GameObject::setType(int type)
{
    this->_type = type;
}

void GameObject::setName(std::string name)
{
    this->_name = name;
}

void GameObject::setPos(glm::vec3 pos)
{
    this->_pos = pos;
}

void GameObject::setScale(glm::vec3 scale)
{
    this->_scale = scale;
}

void GameObject::setRotation(glm::vec3 rotation)
{
    this->_rotation = rotation;
}

void GameObject::setShiny(bool shiny)
{
    this->_shiny = shiny;
}

void GameObject::move(glm::vec3 speed)
{
    if (speed.x && speed.y) {
        speed.x /= 1.414f;
        speed.y /= 1.414f;
    }
    this->_pos.x += speed.x;
    this->_pos.y += speed.y;
}

void GameObject::teleport(glm::vec3 pos)
{
    this->_pos.x = pos.x;
    this->_pos.y = pos.y;
}