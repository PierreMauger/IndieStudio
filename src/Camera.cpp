/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** Camera
*/

#include "Camera.hpp"

using namespace neo;

neo::Camera::Camera() : _shader("resources/shaders/camera.vs", "resources/shaders/camera.fs")
{
    this->_pos = glm::vec3(0.0f, 0.0f, 10.0f);
    this->_front = glm::vec3(0.0f, 0.0f, -10.0f);
    this->_up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->lookAt(this->_pos, this->_front, this->_up);
}

neo::Shader &neo::Camera::getShader()
{
    return this->_shader;
}

// glm::perspective(glm::radians(this->_fov), this->_aspect, this->_near, this->_far);
void neo::Camera::lookAt(glm::vec3 const &pos, glm::vec3 const &front, glm::vec3 const &up)
{
    this->_pos = pos;
    this->_front = front;
    this->_up = up;
    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
    this->_projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    this->_model = glm::mat4(1.0f);
}

void neo::Camera::move(glm::vec3 const &dir)
{
    this->_pos += dir;
    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
}

void neo::Camera::setPos(glm::vec3 const &pos)
{
    this->_pos = pos;
    this->_front = glm::vec3(-pos.x, -pos.y, -pos.z);
    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
}

void neo::Camera::centerOn(glm::vec3 const &pos)
{
    this->_pos = pos - this->_front;
    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
}

void neo::Camera::setRotating(bool rotating)
{
    this->_rotating = rotating;
    if (this->_rotating) {
        this->_up = glm::vec3(0.0f, 0.0f, 1.0f);
    } else {
        this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

void neo::Camera::setShader(float time)
{
    if (this->_rotating) {
        float camX = static_cast<float>(std::sin(glm::radians(time)) * 5.0f);
        float camY = static_cast<float>(std::cos(glm::radians(time)) * 5.0f);
        this->_pos = glm::vec3(camX, camY, this->_pos.z);
        this->_front = glm::vec3(-camX, -camY, -this->_pos.z);
        this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
    }

    this->_shader.setMat4("view", this->_view);
    this->_shader.setMat4("projection", this->_projection);
    this->_shader.setFloat("time", time);
    this->_shader.setVec3("viewPos", this->_pos);
    this->_shader.setVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
}

void neo::Camera::setOnModel(glm::vec3 pos, glm::vec3 scale, float rotation)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    this->_shader.setMat4("model", model);

    for (std::size_t i = 0; i < 100; i++)
        this->_shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", glm::mat4(1.0f));
}

void neo::Camera::setOnAnimatedModel(glm::vec3 pos, glm::vec3 scale, float rotation, Animator &animator)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    this->_shader.setMat4("model", model);

    auto transforms = animator.getFinalBoneMatrices();
    for (std::size_t i = 0; i < 100; i++)
        this->_shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}
