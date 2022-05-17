/*
** EPITECH PROJECT, 2022
** Animator.hpp
** File description:
** Animator
*/

#ifndef ANIMATOR_HPP
    #define ANIMATOR_HPP

    #include "includes.hpp"
    #include "Animation.hpp"

namespace neo
{
    class Animator
    {
        private:
            std::vector<glm::mat4> _finalBoneMatrices;
            Animation *_currentAnimation;
            float _currentTime;
            float _deltaTime;

        public:
            Animator(Animation *animation);
            ~Animator() = default;

            void update(float deltaTime);
            void play(Animation *animation);
            void calculateBoneTransform(const AssimpNodeData *node, const glm::mat4 &parentTransform);
            std::vector<glm::mat4> getFinalBoneMatrices();
    };
}

#endif // ANIMATOR_HPP
