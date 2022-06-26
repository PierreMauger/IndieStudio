/*
** EPITECH PROJECT, 2022
** IScene.hpp
** File description:
** IScene
*/

#ifndef ISCENE_HPP
    #define ISCENE_HPP

    #include "includes.hpp"
    #include "MessageBus.hpp"

namespace neo
{
    class IScene
    {
        public:
            virtual ~IScene() = default;

            virtual void update() = 0;
            virtual void loadScene() = 0;

            virtual void handleKeyPressed(int playerID, std::string action) = 0;
            virtual void handleKeyReleased(int playerID, std::string action) = 0;
            virtual void handleButtonClicked(int button) = 0;
            virtual void handleConfig(std::vector<std::string> config) = 0;
            virtual void handleStartGame(Packet data) = 0;
            virtual void handleSaveMap() = 0;
    };
}

#endif // ISCENE_HPP
