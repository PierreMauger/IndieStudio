/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.cpp
** File description:
** AnimatedModelObj
*/

#include "AnimatedModelObj.hpp"

using namespace neo;

AnimatedModelObj::AnimatedModelObj(std::string name, glm::vec3 pos) : GraphicObject(name, pos)
{
    this->_model = std::make_unique<Model>(name);
}

AnimatedModelObj::AnimatedModelObj(std::string name, glm::vec3 pos, glm::vec3 size) : GraphicObject(name, pos, size)
{
    this->_model = std::make_unique<Model>(name);
}

void AnimatedModelObj::draw(neo::Shader &shader)
{
    this->_model->draw(shader);
}
