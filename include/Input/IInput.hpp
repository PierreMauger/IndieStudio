/*
** EPITECH PROJECT, 2022
** Input.hpp
** File description:
** Input
*/

#ifndef IINPUT_HPP
    #define IINPUT_HPP

    #include "includes.hpp"

namespace neo
{
    class IInput
    {
        public:
            virtual ~IInput() = default;

            virtual void update() = 0;
    };
}

#endif // IINPUT_HPP
