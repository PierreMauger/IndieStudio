/*
** EPITECH PROJECT, 2022
** ModelObj.cpp
** File description:
** ModelObj
*/

#include "ModelObj.hpp"

using namespace neo;

ModelObj::ModelObj(GameObject obj, std::shared_ptr<neo::Model> model) : GraphicObject(obj)
{
    this->_model = model;
}

void ModelObj::draw(neo::Shader &shader)
{
    this->_model->draw(shader);
}
