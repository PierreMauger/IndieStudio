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

void AnimatedModelObj::draw(neo::Camera &camera)
{
    // camera.setOnAnimatedModel(glm::vec3(this->_pos.x, this->_pos.y, 0));
    this->_model->draw(camera.getShader());
}
