/*
** EPITECH PROJECT, 2022
** ModelObj.cpp
** File description:
** ModelObj
*/

#include "ModelObj.hpp"

using namespace neo;

ModelObj::ModelObj(GameObject obj) : GraphicObject(obj)
{
    this->_model = std::make_unique<Model>(obj.getName());
}


void ModelObj::draw(neo::Shader &shader)
{
    this->_model->draw(shader);
}
