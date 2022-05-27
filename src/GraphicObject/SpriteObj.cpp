/*
** EPITECH PROJECT, 2022
** SpriteObj.cpp
** File description:
** SpriteObj
*/

#include "SpriteObj.hpp"

using namespace neo;

SpriteObj::SpriteObj(std::string name, Vector2 pos) : GraphicObject(name, pos)
{
}

SpriteObj::SpriteObj(std::string name, Vector2 pos, Vector2 size) : GraphicObject(name, pos, size)
{
}

void SpriteObj::draw(neo::Shader &shader)
{
    DrawRectangle(this->_position.x, this->_position.y, this->_size.x, this->_size.y, RED);
}
