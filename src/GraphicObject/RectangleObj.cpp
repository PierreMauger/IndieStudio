/*
** EPITECH PROJECT, 2022
** RectangleObj.cpp
** File description:
** RectangleObj
*/

#include "RectangleObj.hpp"

using namespace neo;

RectangleObj::RectangleObj(std::string name, glm::vec3 pos) : GraphicObject(name, pos)
{
}

RectangleObj::RectangleObj(std::string name, glm::vec3 pos, glm::vec3 size) : GraphicObject(name, pos, size)
{
}

void RectangleObj::draw(neo::Shader &shader)
{
    DrawRectangle(this->_position.x, this->_position.y, this->_size.x, this->_size.y, RED);
}
