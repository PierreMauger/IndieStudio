/*
** EPITECH PROJECT, 2022
** SpriteObj.cpp
** File description:
** SpriteObj
*/

#include "SpriteObj.hpp"

using namespace neo;

SpriteObj::SpriteObj(GameObject obj) : GraphicObject(obj)
{
}

void SpriteObj::draw(Camera &camera)
{
    DrawRectangle(this->_pos.x, this->_pos.y, this->_scale.x, this->_scale.y, RED);
}
