/*
** EPITECH PROJECT, 2022
** IInput.hpp
** File description:
** IInput
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
            virtual void editConfig(int key, std::string action) = 0;
    };
}

#endif // IINPUT_HPP
