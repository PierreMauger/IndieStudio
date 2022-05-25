/*
** EPITECH PROJECT, 2022
** MenuScene.hpp
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP
    #define MENUSCENE_HPP

    #include "IScene.hpp"

namespace neo
{
    class MenuScene : public virtual IScene
    {
        private:

        public:
            MenuScene();
            ~MenuScene() = default;

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // MENUSCENE_HPP
