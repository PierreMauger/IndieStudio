/*
** EPITECH PROJECT, 2022
** GameScene.hpp
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP
    #define GAMESCENE_HPP

    #include "IScene.hpp"
    #include "GameObject.hpp"

namespace neo
{
    class GameScene : public virtual IScene
    {
        private:
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, Vector2> _playerSpeed;

        public:
            GameScene();
            ~GameScene();

            // Interface functions
            void update(std::shared_ptr<MessageBus> messageBus);
            void loadScene(std::shared_ptr<MessageBus> messageBus);

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyReleased(int playerNb, std::string action);
    };
}

#endif // GAMESCENE_HPP
