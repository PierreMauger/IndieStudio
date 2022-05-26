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
            Vector2 _pos;
            Vector2 _size;

        public:
            GameObject(std::string name, Vector2 pos);
            GameObject(std::string name, Vector2 pos, Vector2 size);
            ~GameObject() = default;

            std::string getName() const;
            Vector2 getPos() const;
            Vector2 getSize() const;
            void setPos(Vector2 pos);
            void move(Vector2 speed);
    };
}

#endif // GAMEOBJECT_HPP
