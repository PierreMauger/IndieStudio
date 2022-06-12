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
            std::shared_ptr<Model> _model;
            std::shared_ptr<Animation> _animation;
            std::unique_ptr<Animator> _animator;

        public:
            AnimatedModelObj(GameObject obj, std::shared_ptr<Model> model, std::shared_ptr<Animation> animation);
            ~AnimatedModelObj() = default;

            void draw(Camera &camera);
    };
}

#endif // ANIMATED_MODEL_OBJ_HPP
