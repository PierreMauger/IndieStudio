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
        size_t _playerId;
    public:
        Bomb(std::string name, glm::vec3 pos, size_t fireUp, size_t playerId, glm::vec3 scale = glm::vec3(1.0f));
        double &getTimer();
        const size_t getPlayerId() const;
        const size_t getFireUp() const;
    };
}

#endif // BOMB_HPP
