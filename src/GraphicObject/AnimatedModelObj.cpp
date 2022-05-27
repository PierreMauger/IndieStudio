/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.cpp
** File description:
** AnimatedModelObj
*/

#include "AnimatedModelObj.hpp"

using namespace neo;

AnimatedModelObj::AnimatedModelObj(GameObject obj) : GraphicObject(obj)
{
    this->_model = std::make_unique<Model>(obj.getName());
}

void AnimatedModelObj::draw(neo::Shader &shader)
{
    this->_model->draw(shader);
}
