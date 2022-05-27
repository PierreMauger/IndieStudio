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
        protected:
            std::string _name;
            glm::vec3 _position;
            glm::vec3 _size;

        public:
            GraphicObject(std::string name, glm::vec3 pos);
            GraphicObject(std::string name, glm::vec3 pos, glm::vec3 size);
            ~GraphicObject() = default;

            glm::vec3 getPos() const;
            glm::vec3 getSize() const;
            void setPos(glm::vec3 pos);
            virtual void draw(neo::Shader &shader) = 0;
    };
}

#endif // GRAPHICOBJECT_HPP
