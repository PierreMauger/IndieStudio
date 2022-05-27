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
            std::shared_ptr<MessageBus> _messageBus;

        public:
            ConfigScene(std::shared_ptr<MessageBus> messageBus);
            ~ConfigScene();

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyReleased(int playerNb, std::string action);
    };
}

#endif // CONFIGSCENE_HPP
