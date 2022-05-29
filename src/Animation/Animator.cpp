/*
** EPITECH PROJECT, 2022
** Animator.cpp
** File description:
** Animator
*/

#include "Animator.hpp"

using namespace neo;

Animator::Animator(std::shared_ptr<Animation> animation)
{
    this->_currentAnimation = animation;
    this->_currentTime = 0.0f;
    this->_deltaTime = 0.0f;

    this->_finalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        this->_finalBoneMatrices.push_back(glm::mat4(1.0f));
}

void Animator::update(float deltaTime)
{
    this->_deltaTime = deltaTime;

    if (this->_currentAnimation) {
        this->_currentTime += this->_currentAnimation->getTicksPerSecond() * this->_deltaTime;
        this->_currentTime = fmod(this->_currentTime, this->_currentAnimation->getDuration());
        this->calculateBoneTransform(this->_currentAnimation->getRootNode(), glm::mat4(1.0f));
    }
}

void Animator::play(std::shared_ptr<Animation> animation)
{
    this->_currentAnimation = animation;
    this->_currentTime = 0.0f;
}

void Animator::calculateBoneTransform(const AssimpNodeData &node, const glm::mat4 &parentTransform)
{
    glm::mat4 nodeTransform = glm::mat4(1.0f);
    std::unique_ptr<Bone> bone = this->_currentAnimation->findBone(node.name);

    if (bone) {
        bone->update(this->_currentTime);
        nodeTransform = bone->getLocalTransform();
    }
    glm::mat4 globalTransform = parentTransform * nodeTransform;

    auto boneInfoMap = this->_currentAnimation->getBoneInfoMap();
    if (boneInfoMap.find(node.name) != boneInfoMap.end()) {
        int index = boneInfoMap[node.name].id;
        this->_finalBoneMatrices[index] = globalTransform * boneInfoMap[node.name].offset;
    }

    for (auto &child : node.children)
        this->calculateBoneTransform(child, globalTransform);
}

std::vector<glm::mat4> Animator::getFinalBoneMatrices() const
{
    return this->_finalBoneMatrices;
}
