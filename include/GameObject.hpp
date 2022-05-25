/*
** EPITECH PROJECT, 2022
** GameObject.hpp
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP

    #include "includes.hpp"

namespace neo
{
    class GameObject
    {
        private:
            std::string _name;
            Vector2 _position;

        public:
            GameObject(std::string name, Vector2 position);
            ~GameObject() = default;

            std::string getName() const;
            Vector2 getPosition() const;
            void setPosition(Vector2 position);
    };
}

#endif // GAMEOBJECT_HPP
