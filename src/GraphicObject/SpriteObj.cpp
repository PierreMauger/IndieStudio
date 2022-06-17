/*
** EPITECH PROJECT, 2022
** SpriteObj.cpp
** File description:
** SpriteObj
*/

#include "SpriteObj.hpp"

using namespace neo;

SpriteObj::SpriteObj(GameObject obj, std::shared_ptr<Texture2D> texture) : GraphicObject(obj)
{
    this->_texture = texture;
    this->_coords = glm::vec2(texture.get()->width, texture.get()->height);
}

void SpriteObj::draw(Camera &camera)
{
    DrawTexturePro(*this->_texture.get(), {0, 0, this->_coords.x, this->_coords.y}, this->getBox(), {0, 0}, 0, WHITE);
}

Rectangle SpriteObj::getBox() const
{
    float height = GetScreenHeight();
    float width = GetScreenWidth();

    return {this->_pos.x * width / 2 + width / 2 - this->_scale.x * width / 2, this->_pos.y * height / 2 + height / 2 - this->_scale.y * height / 2, this->_scale.x * width, this->_scale.y * height};
}
