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
    this->_pos = glm::vec3(0.0f);
    this->_front = glm::vec3(0.0f);
    this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->_nextPos = glm::vec3(0.0f);
    this->_nextFront = glm::vec3(0.0f);
    this->_rotating = false;

    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
    this->_projection = glm::perspective(glm::radians(45.0f), (float)GetScreenWidth() / (float)GetScreenHeight(), 0.1f, 200.0f);
    this->_model = glm::mat4(1.0f);
}

neo::Shader &neo::Camera::getShader()
{
    return this->_shader;
}

void neo::Camera::update()
{
    glm::vec3 forward = glm::normalize(this->_pos - this->_front);
    if (this->_rotating)
        forward = glm::vec3(forward.x, forward.z, forward.y);
    if (forward != glm::vec3(0.0f, 0.0f, 1.0f)) {
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 0.0f, 1.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));
        this->_up = up;
    } else {
        this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
}

void neo::Camera::setMovement(glm::vec3 const &nextPos, glm::vec3 const &nextFront)
{
    this->_nextPos = nextPos;
    this->_nextFront = nextFront;
}

void neo::Camera::setPos(glm::vec3 const &pos)
{
    this->_pos = pos;
    this->_front = -pos;

    this->update();
}

void neo::Camera::setRotating(bool rotating)
{
    this->_rotating = rotating;
}

void neo::Camera::setRotation(glm::vec3 const &rotation)
{
    this->_rotation = rotation;
}

void neo::Camera::setShader(float time)
{
    if (this->_nextPos != glm::vec3(0.0f) && this->_pos != this->_nextPos) {
        float distance = glm::distance(this->_pos, this->_nextPos);
        float speed = 0.02f;
        if (distance < speed) {
            this->_pos = this->_nextPos;
            this->_nextPos = glm::vec3(0.0f);
        } else {
            this->_pos += (this->_nextPos - this->_pos) * speed;
        }
        this->_front = -this->_pos;
        this->_view = glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
    }
    if (this->_rotating) {
        glm::vec3 temp = glm::vec3(0.0f);
        float camX = static_cast<float>(std::sin(glm::radians(this->_rotation.x)) * this->_pos.x);
        float camY = static_cast<float>(std::cos(glm::radians(this->_rotation.x)) * this->_pos.x);
        float camZ = static_cast<float>(std::sin(glm::radians(this->_rotation.y)) * this->_pos.z);
        temp = glm::vec3(camY, camX, this->_pos.z + camZ);
        this->_view = glm::lookAt(temp, this->_pos + this->_front, this->_up);
        this->_shader.setVec3("viewPos", temp);
        this->_shader.setVec3("lightPos", temp);
    } else {
        this->_shader.setVec3("viewPos", this->_pos);
        this->_shader.setVec3("lightPos", this->_pos);
    }
    this->_shader.setVec3("lightColor", glm::vec3(1.0f));
    this->_shader.setMat4("view", this->_view);
    this->_shader.setMat4("projection", this->_projection);
    this->_shader.setFloat("time", time);
}

void neo::Camera::setOnModel(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->_shader.setMat4("model", model);

    for (std::size_t i = 0; i < 100; i++)
        this->_shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", glm::mat4(1.0f));
}

void neo::Camera::setOnAnimatedModel(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, Animator &animator)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->_shader.setMat4("model", model);

    auto transforms = animator.getFinalBoneMatrices();
    for (std::size_t i = 0; i < 100; i++)
        this->_shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}
