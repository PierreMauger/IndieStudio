/*
** EPITECH PROJECT, 2022
** GraphicObject.hpp
** File description:
** GraphicObject
*/

#ifndef GRAPHICOBJECT_HPP
    #define GRAPHICOBJECT_HPP

    #include "includes.hpp"
    #include "Model.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class GraphicObject
    {
        private:
            std::string _name;
            glm::vec3 _position;
            neo::Model _model;
            // Animation _animation;
            // Animator _animator;

        public:
            GraphicObject(std::string name, glm::vec3 pos);
            ~GraphicObject() = default;

            void setPosition(glm::vec3 pos);
            void draw(neo::Shader &shader);
    };
}

#endif // GRAPHICOBJECT_HPP
