/*
** EPITECH PROJECT, 2022
** IAudio.hpp
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP
    #define IAUDIO_HPP

    #include "includes.hpp"

namespace neo
{
    class IAudio
    {
        public:
            virtual ~IAudio() = default;

            virtual void playSound() = 0;
            virtual void playMusic() = 0;
            virtual void pauseMusic() = 0;
    };
}

#endif // IAUDIO_HPP
