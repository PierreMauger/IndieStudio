/*
** EPITECH PROJECT, 2022
** GameScene.hpp
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP
    #define GAMESCENE_HPP

    #include "IScene.hpp"

namespace neo
{
    class GameScene : public virtual IScene
    {
        private:

        public:
            GameScene();
            ~GameScene();

            // Interface functions
            void update();
            void loadScene(std::shared_ptr<MessageBus> messageBus);

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // GAMESCENE_HPP
