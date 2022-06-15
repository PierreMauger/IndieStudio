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
    if (this->_status) {
        glDisable(GL_DEPTH_TEST);
        camera.setOnModel(this->_pos - glm::vec3(0.f, 0.f, this->_scale.z * 0.1f), this->_scale * glm::vec3(1.1f), this->_rotation);
        camera.getShader().setBool("outline", true);
        this->_model->draw(camera.getShader());
        glEnable(GL_DEPTH_TEST);
    }
    if (this->_shiny)
        camera.getShader().setBool("shiny", true);
    camera.getShader().setBool("outline", false);
    this->_animator->update(GetFrameTime());
    camera.setOnAnimatedModel(this->_pos, this->_scale, this->_rotation, *this->_animator);
    this->_model->draw(camera.getShader());
}
