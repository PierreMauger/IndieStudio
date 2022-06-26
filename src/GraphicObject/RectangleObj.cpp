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

void RectangleObj::draw(Camera &camera)
{
    float height = GetScreenHeight();
    float width = GetScreenWidth();
    Color color = RED;

    if (this->_status)
        color = YELLOW;
    DrawRectangle(this->_pos.x * width / 2 + width / 2 - this->_scale.x * width / 2, this->_pos.y * height / 2 + height / 2 - this->_scale.y * height / 2, this->_scale.x * width, this->_scale.y * height, color);
    DrawText(this->_name.c_str(), this->_pos.x * width / 2 + width / 2 - this->_scale.x * width / 2, this->_pos.y * height / 2 + height / 2 - this->_scale.y * height / 2, 24, BLACK);
}

Rectangle RectangleObj::getBox() const
{
    float height = GetScreenHeight();
    float width = GetScreenWidth();

    return {this->_pos.x * width / 2 + width / 2 - this->_scale.x * width / 2, this->_pos.y * height / 2 + height / 2 - this->_scale.y * height / 2, this->_scale.x * width, this->_scale.y * height};
}
