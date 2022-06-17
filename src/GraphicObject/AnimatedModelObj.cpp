/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.cpp
** File description:
** AnimatedModelObj
*/

#include "AnimatedModelObj.hpp"

using namespace neo;

AnimatedModelObj::AnimatedModelObj(GameObject obj, std::shared_ptr<Model> model, std::shared_ptr<Animation> animation) : GraphicObject(obj)
{
    this->_model = model;
    this->_animation = animation;
    this->_animator = std::make_unique<Animator>(this->_animation);
}

void AnimatedModelObj::draw(Camera &camera)
{
    this->_animator->update(GetFrameTime());
    camera.setOnAnimatedModel(this->_pos, this->_scale, this->_rotation, *this->_animator);
    this->_model->draw(camera.getShader());
}
