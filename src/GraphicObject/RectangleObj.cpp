/*
** EPITECH PROJECT, 2022
** RectangleObj.cpp
** File description:
** RectangleObj
*/

#include "RectangleObj.hpp"

using namespace neo;

RectangleObj::RectangleObj(GameObject obj) : GraphicObject(obj)
{
}

void RectangleObj::draw(neo::Shader &shader)
{
    if (this->_status)
        DrawRectangle(this->_pos.x, this->_pos.y, this->_size.x, this->_size.y, YELLOW);
    else
        DrawRectangle(this->_pos.x, this->_pos.y, this->_size.x, this->_size.y, RED);
}
