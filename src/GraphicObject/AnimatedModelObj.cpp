/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.cpp
** File description:
** AnimatedModelObj
*/

#include "AnimatedModelObj.hpp"

using namespace neo;

AnimatedModelObj::AnimatedModelObj(GameObject obj, std::shared_ptr<neo::Model> model) : GraphicObject(obj)
{
    this->_model = model;
}

void AnimatedModelObj::draw(neo::Shader &shader)
{
    this->_model->draw(shader);
}
