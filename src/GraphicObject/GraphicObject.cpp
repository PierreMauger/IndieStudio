/*
** EPITECH PROJECT, 2022
** GraphicObject.cpp
** File description:
** GraphicObject
*/

#include "GraphicObject.hpp"

using namespace neo;

GraphicObject::GraphicObject(std::string name, glm::vec3 pos)
{
    this->_name = name;
    this->_position = pos;
    this->_size = glm::vec3(0, 0, 0);
}

GraphicObject::GraphicObject(std::string name, glm::vec3 pos, glm::vec3 size)
{
    this->_name = name;
    this->_position = pos;
    this->_size = size;
}

glm::vec3 GraphicObject::getPos() const
{
    return this->_position;
}

glm::vec3 GraphicObject::getSize() const
{
    return this->_size;
}

void GraphicObject::setPos(glm::vec3 pos)
{
    this->_position = pos;
}
