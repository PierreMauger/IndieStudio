/*
** EPITECH PROJECT, 2022
** GraphicObject.cpp
** File description:
** GraphicObject
*/

#include "GraphicObject.hpp"

using namespace neo;

GraphicObject::GraphicObject(std::string name, glm::vec3 position) : _model(name)
{
    this->_name = name;
    this->_position = position;
}

glm::vec3 GraphicObject::getPosition() const
{
    return this->_position;
}

void GraphicObject::setPosition(glm::vec3 position)
{
    this->_position = position;
}

void GraphicObject::draw(neo::Shader &shader)
{
    this->_model.draw(shader);
}
