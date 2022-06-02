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
        Bomb(double timer, size_t fireUp, size_t playerId);
    };
}

#endif // BOMB_HPP