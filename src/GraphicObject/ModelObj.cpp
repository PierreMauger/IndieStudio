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
    if (this->_status) {
        glDisable(GL_DEPTH_TEST);
        camera.setOnModel(this->_pos - glm::vec3(0.f, 0.f, this->_scale.z * 0.1f), this->_scale * glm::vec3(1.1f), this->_rotation);
        camera.getShader().setBool("outline", true);
        this->_model->draw(camera.getShader());
        glEnable(GL_DEPTH_TEST);
    }
    camera.getShader().setBool("shiny", this->_shiny);
    camera.getShader().setBool("outline", false);
    camera.setOnModel(this->_pos, this->_scale, this->_rotation);
    this->_model->draw(camera.getShader());
}
