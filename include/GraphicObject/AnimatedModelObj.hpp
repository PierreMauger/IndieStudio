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
            std::unique_ptr<neo::Model> _model;

        public:
            AnimatedModelObj(std::string name, Vector2 pos);
            AnimatedModelObj(std::string name, Vector2 pos, Vector2 size);
            ~AnimatedModelObj() = default;

            void draw(neo::Shader &shader);
    };
}

#endif // ANIMATED_MODEL_OBJ_HPP
