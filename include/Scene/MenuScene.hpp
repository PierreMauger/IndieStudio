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
            std::map<int, GameObject> _objects;
            // Rectangle _rectangle;
            // Vector2 _modelPos;

        public:
            MenuScene();
            ~MenuScene() = default;

            // Interface functions
            void update();
            void loadScene(std::shared_ptr<MessageBus> messageBus);

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // MENUSCENE_HPP
