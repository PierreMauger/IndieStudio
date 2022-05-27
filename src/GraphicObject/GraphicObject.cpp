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
    this->_size = obj.getSize();
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
