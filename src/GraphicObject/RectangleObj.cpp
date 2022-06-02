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

void RectangleObj::draw(neo::Camera &camera)
{
    if (this->_status)
        DrawRectangle(this->_pos.x, this->_pos.y, this->_scale.x, this->_scale.y, YELLOW);
    else
        DrawRectangle(this->_pos.x, this->_pos.y, this->_scale.x, this->_scale.y, RED);
}
