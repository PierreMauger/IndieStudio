/*
** EPITECH PROJECT, 2022
** RectangleObj.cpp
** File description:
** RectangleObj
*/

#include "RectangleObj.hpp"

using namespace neo;

RectangleObj::RectangleObj(std::string name, Vector2 pos) : GraphicObject(name, pos)
{
}

RectangleObj::RectangleObj(std::string name, Vector2 pos, Vector2 size) : GraphicObject(name, pos, size)
{
}

void RectangleObj::draw(neo::Shader &shader)
{
    if (this->_status)
        DrawRectangle(this->_pos.x, this->_pos.y, this->_size.x, this->_size.y, YELLOW);
    else
        DrawRectangle(this->_pos.x, this->_pos.y, this->_size.x, this->_size.y, RED);
}
