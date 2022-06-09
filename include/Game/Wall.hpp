/*
** EPITECH PROJECT, 2022
** Wall.hpp
** File description:
** Wall
*/

#ifndef WALL_HPP
    #define WALL_HPP

    #include "GameObject.hpp"

namespace neo
{
    class Wall : public virtual GameObject
    {
    private:
        bool _isDestructible;
    public:
        Wall(std::string name, glm::vec3 pos, bool isDestructible, glm::vec3 scale = glm::vec3(1.0f));
    };
}

#endif // WALL_HPP
