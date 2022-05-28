/*
** EPITECH PROJECT, 2022
** AnimatedModelObj.hpp
** File description:
** AnimatedModelObj
*/

#ifndef ANIMATED_MODEL_OBJ_HPP
    #define ANIMATED_MODEL_OBJ_HPP

    #include "includes.hpp"
    #include "GraphicObject.hpp"
    #include "Model.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class AnimatedModelObj : public GraphicObject
    {
        private:
            std::shared_ptr<neo::Model> _model;
            std::shared_ptr<neo::Animation> _animation;
            std::unique_ptr<neo::Animator> _animator;

        public:
            AnimatedModelObj(GameObject obj, std::shared_ptr<neo::Model> model, std::shared_ptr<neo::Animation> animation);
            ~AnimatedModelObj() = default;

            void draw(neo::Camera &camera);
    };
}

#endif // ANIMATED_MODEL_OBJ_HPP
