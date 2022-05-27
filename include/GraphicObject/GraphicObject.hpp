/*
** EPITECH PROJECT, 2022
** GraphicObject.hpp
** File description:
** GraphicObject
*/

#ifndef GRAPHICOBJECT_HPP
    #define GRAPHICOBJECT_HPP

    #include "includes.hpp"
    #include "GameObject.hpp"
    #include "Model.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class GraphicObject
    {
        protected:
            std::string _name;
            Vector2 _pos;
            Vector2 _size;
            int _status;

        public:
            GraphicObject(GameObject obj);
            ~GraphicObject() = default;

            Vector2 getPos() const;
            Vector2 getSize() const;
            void setPos(Vector2 pos);
            void setStatus(int status);
            virtual void draw(neo::Shader &shader) = 0;
    };
}

#endif // GRAPHICOBJECT_HPP
