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
    #include "macros.hpp"

namespace neo
{
    class Player : public virtual GameObject
    {
    private:
        std::vector<Bomb> _bombs;
        Vector2 _speed;
        double _cooldown;
        size_t _bombUp;
        size_t _speedUp;
        size_t _fireUp;
        bool _wallPass;
    public:
        Player(std::string name, Vector2 pos);
        Vector2 getSpeed() const;
    };
}

#endif // PLAYER_HPP