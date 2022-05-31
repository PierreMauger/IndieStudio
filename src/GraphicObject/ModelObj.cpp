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

void ModelObj::draw(neo::Camera &camera)
{
    camera.setOnModel(glm::vec3(this->_pos.x, 0.0f, this->_pos.y));
    this->_model->draw(camera.getShader());
}
