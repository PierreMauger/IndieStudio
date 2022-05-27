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
            int _type;
            std::string _name;
            Vector2 _pos;
            Vector2 _size;

        public:
            GameObject() = default;
            GameObject(int type, std::string name, Vector2 pos);
            GameObject(int type, std::string name, Vector2 pos, Vector2 size);
            ~GameObject() = default;

            int getType() const;
            std::string getName() const;
            Vector2 getPos() const;
            Vector2 getSize() const;
            void setType(int type);
            void setName(std::string name);
            void setPos(Vector2 pos);
            void setSize(Vector2 size);

            void move(Vector2 speed);
    };
}

#endif // GAMEOBJECT_HPP
