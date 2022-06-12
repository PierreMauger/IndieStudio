/*
** EPITECH PROJECT, 2022
** ModelObj.cpp
** File description:
** ModelObj
*/

#include "ModelObj.hpp"

using namespace neo;

ModelObj::ModelObj(GameObject obj, std::shared_ptr<Model> model) : GraphicObject(obj)
{
    this->_model = model;
}

void ModelObj::draw(Camera &camera)
{
    camera.setOnModel(this->_pos, this->_scale, this->_rotation);
    this->_model->draw(camera.getShader());
}
