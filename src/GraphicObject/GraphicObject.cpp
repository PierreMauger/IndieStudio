/*
** EPITECH PROJECT, 2022
** GraphicObject.cpp
** File description:
** GraphicObject
*/

#include "GraphicObject.hpp"

using namespace neo;

GraphicObject::GraphicObject(GameObject obj)
{
    this->_name = obj.getName();
    this->_pos = obj.getPos();
    this->_scale = obj.getScale();
    this->_shiny = obj.getShiny();
    this->_rotation = obj.getRotation();
    this->_status = 0;
}

glm::vec3 GraphicObject::getPos() const
{
    return this->_pos;
}

glm::vec3 GraphicObject::getScale() const
{
    return this->_scale;
}

glm::vec3 GraphicObject::getRotation() const
{
    return this->_rotation;
}

int GraphicObject::getStatus() const
{
    return this->_status;
}

void GraphicObject::setPos(glm::vec3 pos)
{
    this->_pos = pos;
}

void GraphicObject::setRotation(glm::vec3 rotation)
{
    this->_rotation = rotation;
}

void GraphicObject::setStatus(int status)
{
    this->_status = status;
}

bool GraphicObject::getShiny() const
{
    return this->_shiny;
}
