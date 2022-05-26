/*
** EPITECH PROJECT, 2022
** MenuScene.hpp
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP
    #define MENUSCENE_HPP

    #include "IScene.hpp"
    #include "GameObject.hpp"

namespace neo
{
    class MenuScene : public virtual IScene
    {
        private:
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, std::unique_ptr<GameObject>> _buttons;

        public:
            MenuScene();
            ~MenuScene();

            // Interface functions
            void update(std::shared_ptr<MessageBus> messageBus);
            void loadScene(std::shared_ptr<MessageBus> messageBus);

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // MENUSCENE_HPP
