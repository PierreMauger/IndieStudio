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
            glm::vec3 _rotation;
            int _status;
            bool _shiny;

        public:
            GraphicObject(GameObject obj);
            ~GraphicObject() = default;

            glm::vec3 getPos() const;
            glm::vec3 getScale() const;
            glm::vec3 getRotation() const;
            int getStatus() const;
            void setPos(glm::vec3 pos);
            void setRotation(glm::vec3 rotation);
            void setStatus(int status);
            bool getShiny() const;
            virtual void draw(Camera &camera) = 0;
            virtual Rectangle getBox() const = 0;
    };
}

#endif // GRAPHICOBJECT_HPP
