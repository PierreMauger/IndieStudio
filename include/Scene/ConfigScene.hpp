/*
** EPITECH PROJECT, 2022
** ConfigScene.hpp
** File description:
** ConfigScene
*/

#ifndef CONFIGSCENE_HPP
    #define CONFIGSCENE_HPP

    #include "IScene.hpp"

namespace neo
{
    class ConfigScene : public virtual IScene
    {
        private:

        public:
            ConfigScene();
            ~ConfigScene() = default;

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // CONFIGSCENE_HPP
