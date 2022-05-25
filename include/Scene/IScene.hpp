/*
** EPITECH PROJECT, 2022
** IScene.hpp
** File description:
** IScene
*/

#ifndef ISCENE_HPP
    #define ISCENE_HPP

    #include "includes.hpp"

namespace neo
{
    class IScene
    {
        public:
            virtual ~IScene() = default;

            virtual void update() = 0;
            virtual void loadScene() = 0;

            virtual void handleKeyPressed(int playerNb, std::string action) = 0;
            virtual void handleKeyRelease(int playerNb, std::string action) = 0;
    };
}

#endif // ISCENE_HPP
