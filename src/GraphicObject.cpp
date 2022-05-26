/*
** EPITECH PROJECT, 2022
** GraphicObject.cpp
** File description:
** GraphicObject
*/

#include "GraphicObject.hpp"

using namespace neo;

GraphicObject::GraphicObject(std::string name, glm::vec3 pos) : _model(name)
{
    this->_name = name;
    this->_position = pos;
    this->_size = glm::vec3(0, 0, 0);
}

GraphicObject::GraphicObject(std::string name, glm::vec3 pos, glm::vec3 size) : _model(name)
{
    this->_name = name;
    this->_position = pos;
    this->_size = size;
}

glm::vec3 GraphicObject::getPos() const
{
    return this->_position;
}

void GraphicObject::setPos(glm::vec3 pos)
{
    this->_position = pos;
}

void GraphicObject::draw(neo::Shader &shader)
{
    this->_model.draw(shader);
}
