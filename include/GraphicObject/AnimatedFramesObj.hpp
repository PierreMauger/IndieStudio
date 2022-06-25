/*
** EPITECH PROJECT, 2022
** AnimatedFramesObj.hpp
** File description:
** AnimatedFramesObj
*/

#ifndef ANIMATED_FRAMES_OBJ_HPP
    #define ANIMATED_FRAMES_OBJ_HPP

    #include "includes.hpp"
    #include "GraphicObject.hpp"
    #include "Model.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class AnimatedFramesObj : public GraphicObject
    {
        private:
            std::vector<std::shared_ptr<Model>> _model;
            int _currentFrame;

        public:
            AnimatedFramesObj(GameObject obj, std::vector<std::shared_ptr<Model>> _model);
            ~AnimatedFramesObj() = default;

            void draw(Camera &camera);
            Rectangle getBox() const;
    };
}

#endif // ANIMATED_MODEL_OBJ_HPP
