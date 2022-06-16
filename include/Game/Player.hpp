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

using namespace neo;

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
        bool _isBot;
    public:
        Player(std::string name, glm::vec3 pos, bool isBot, glm::vec3 scale = glm::vec3(1.0f));
        glm::vec3 &getSpeed();
        bool &getDirection(int axis);
        size_t &getBombUp();
        size_t &getSpeedUp();
        size_t &getFireUp();
        bool &getWallPass();
        bool &isBot();
    };
}

#endif // PLAYER_HPP
