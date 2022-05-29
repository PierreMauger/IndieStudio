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
            std::shared_ptr<Animation> _currentAnimation;
            float _currentTime;
            float _deltaTime;

        public:
            Animator(std::shared_ptr<Animation> animation);
            ~Animator() = default;

            void update(float deltaTime);
            void play(std::shared_ptr<Animation> animation);
            void calculateBoneTransform(const AssimpNodeData &node, const glm::mat4 &parentTransform);
            std::vector<glm::mat4> getFinalBoneMatrices() const;
    };
}

#endif // ANIMATOR_HPP
