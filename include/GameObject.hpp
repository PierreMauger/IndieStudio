/*
** EPITECH PROJECT, 2022
** GameObject.hpp
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP

    #include "includes.hpp"

    #include <glm/glm.hpp>

namespace neo
{
    class GameObject
    {
        private:
            int _type;
            std::string _name;
            glm::vec3 _pos;
            glm::vec3 _scale;
            float _rotation;

        public:
            GameObject() = default;
            GameObject(int type, std::string name, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.0f));
            ~GameObject() = default;

            int getType() const;
            std::string getName() const;
            glm::vec3 getPos() const;
            glm::vec3 getScale() const;
            float getRotation() const;
            void setType(int type);
            void setName(std::string name);
            void setPos(glm::vec3 pos);
            void setScale(glm::vec3 scale);
            void setRotation(float rotation);

            void move(glm::vec3 speed);
    };
}

#endif // GAMEOBJECT_HPP
