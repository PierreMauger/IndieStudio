/*
** EPITECH PROJECT, 2022
** Bomb.hpp
** File description:
** Bomb
*/

#ifndef BOMB_HPP
	#define BOMB_HPP

    #include "GameObject.hpp"

namespace neo
{
    class Bomb : public virtual GameObject
    {
    private:
        double _timer;
        size_t _fireUp;
    public:
        Bomb(std::string name, glm::vec3 pos, size_t fireUp, glm::vec3 scale = glm::vec3(1.0f));
    };
}

#endif // BOMB_HPP
