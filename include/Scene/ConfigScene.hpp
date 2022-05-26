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
            ~ConfigScene();

            // Interface functions
            void update(std::shared_ptr<MessageBus> messageBus);
            void loadScene(std::shared_ptr<MessageBus> messageBus);

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyRelease(int playerNb, std::string action);
    };
}

#endif // CONFIGSCENE_HPP
