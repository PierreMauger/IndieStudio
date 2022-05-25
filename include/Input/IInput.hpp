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
            virtual float checkAxisStatus(int gamepad, int key, std::string action) = 0;
            virtual void checkInputStatus(int key, std::string action, int playerNb) = 0;
            virtual void checkKeyStatus(int key, std::string action, int playerNb) = 0;
            virtual void checkButtonStatus(int key, std::string action, int playerNb) = 0;
            virtual void checkJoystickStatus(int key, std::string action, int playerNb) = 0;
    };
}

#endif // IINPUT_HPP
