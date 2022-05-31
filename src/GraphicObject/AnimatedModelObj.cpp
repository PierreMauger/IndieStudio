/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.cpp
** File description:
** AnimatedModelObj
*/

#include "AnimatedModelObj.hpp"

using namespace neo;

AnimatedModelObj::AnimatedModelObj(GameObject obj, std::shared_ptr<neo::Model> model, std::shared_ptr<neo::Animation> animation) : GraphicObject(obj)
{
    this->_model = model;
    this->_animation = animation;
    this->_animator = std::make_unique<Animator>(this->_animation);
}

void AnimatedModelObj::draw(neo::Camera &camera)
{
    this->_animator->update(GetFrameTime());
    camera.setOnAnimatedModel(glm::vec3(this->_pos.x, 0.0f, this->_pos.y), *this->_animator);
    this->_model->draw(camera.getShader());
}
