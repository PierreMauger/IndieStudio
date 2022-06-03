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
    #include "Camera.hpp"

namespace neo
{
    class GraphicObject
    {
        protected:
            std::string _name;
            glm::vec3 _pos;
            glm::vec3 _scale;
            float _rotation;
            int _status;

        public:
            GraphicObject(GameObject obj);
            ~GraphicObject() = default;

            glm::vec3 getPos() const;
            glm::vec3 getScale() const;
            float getRotation() const;
            void setPos(glm::vec3 pos);
            void setRotation(float rotation);
            void setStatus(int status);
            virtual void draw(neo::Camera &camera) = 0;
    };
}

#endif // GRAPHICOBJECT_HPP
