/*
** EPITECH PROJECT, 2022
** utils.hpp
** File description:
** utils
*/

#ifndef UTILS_HPP
	#define UTILS_HPP

    #include "GameObject.hpp"

namespace neo
{
    enum directions {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    enum goals {
        NONE,
        WALL,
        PLAYER,
        SAFE
    };

    static const std::array<std::string, 10> powerUps = {
        "BombUp",
        "BombUp",
        "BombUp",
        "SpeedUp",
        "SpeedUp",
        "SpeedUp",
        "FireUp",
        "FireUp",
        "FireUp",
        "WallPass"
    };
}

#endif // UTILS_HPP