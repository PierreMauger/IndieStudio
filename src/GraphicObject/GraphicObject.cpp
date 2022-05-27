/*
** EPITECH PROJECT, 2022
** GraphicObject.cpp
** File description:
** GraphicObject
*/

#include "GraphicObject.hpp"

using namespace neo;

GraphicObject::GraphicObject(std::string name, Vector2 pos)
{
    this->_name = name;
    this->_pos = pos;
    this->_size = (Vector2){0, 0};
    this->_status = 0;
}

GraphicObject::GraphicObject(std::string name, Vector2 pos, Vector2 size)
{
    this->_name = name;
    this->_pos = pos;
    this->_size = size;
    this->_status = 0;
}

Vector2 GraphicObject::getPos() const
{
    return this->_pos;
}

Vector2 GraphicObject::getSize() const
{
    return this->_size;
}

void GraphicObject::setPos(Vector2 pos)
{
    this->_pos = pos;
}

void GraphicObject::setStatus(int status)
{
    this->_status = status;
}
