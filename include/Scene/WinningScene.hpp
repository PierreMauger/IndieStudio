/*
** EPITECH PROJECT, 2022
** WinningScene.hpp
** File description:
** WinningScene
*/

#ifndef WINNING_SCENE_HPP
    #define WINNING_SCENE_HPP

    #include "IScene.hpp"

namespace neo
{
    class WinningScene : public virtual IScene
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, std::unique_ptr<GameObject>> _buttons;

        public:
            WinningScene(std::shared_ptr<MessageBus> messageBus);
            ~WinningScene();

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerID, std::string action);
            void handleKeyReleased(int playerID, std::string action);
            void handleButtonClicked(int button);
            void handleConfig(std::vector<std::string> config);
            void handleStartGame(Packet data);
            void handleSaveMap();
            void handleMapLoaded(Packet data);
    };
}

#endif // WINNING_SCENE_HPP
