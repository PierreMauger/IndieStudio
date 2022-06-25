/*
** EPITECH PROJECT, 2022
** AnimatedFramesObj.cpp
** File description:
** AnimatedFramesObj
*/

#include "AnimatedFramesObj.hpp"

using namespace neo;

AnimatedFramesObj::AnimatedFramesObj(GameObject obj, std::vector<std::shared_ptr<Model>> model) : GraphicObject(obj)
{
    this->_model = model;
    this->_currentFrame = 0;
}

void AnimatedFramesObj::draw(Camera &camera)
{
    this->_currentFrame = (this->_currentFrame + 1) % this->_model.size();
    if (this->_status) {
        glDisable(GL_DEPTH_TEST);
        camera.setOnModel(this->_pos - glm::vec3(0.0f, 0.0f, this->_scale.z * 0.1f), this->_scale * glm::vec3(1.1f), this->_rotation);
        camera.getShader().setBool("outline", true);
        this->_model[this->_currentFrame]->draw(camera.getShader());
        glEnable(GL_DEPTH_TEST);
    }
    if (this->_shiny)
        camera.getShader().setBool("shiny", true);
    camera.getShader().setBool("outline", false);
    camera.setOnModel(this->_pos, this->_scale, this->_rotation);
    this->_model[this->_currentFrame]->draw(camera.getShader());
}

Rectangle AnimatedFramesObj::getBox() const
{
    return {0, 0, 0, 0};
}
