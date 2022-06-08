/*
** EPITECH PROJECT, 2022
** Player.hpp
** File description:
** Player
*/

#ifndef PLAYER_HPP
	#define PLAYER_HPP

    #include "GameObject.hpp"
    #include "Bomb.hpp"

namespace neo
{
    class Player : public virtual GameObject
    {
    private:
        glm::vec3 _speed;
        bool _direction[4];
        size_t _bombUp;
        size_t _speedUp;
        size_t _fireUp;
        bool _wallPass;

    public:
        Player(std::string name, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.f));
        glm::vec3 &getSpeed();
        void setSpeed(glm::vec3 speed);
        bool getDirection(int axis) const;
        void setDirection(int axis, bool val);
    };
}

#endif // PLAYER_HPP
