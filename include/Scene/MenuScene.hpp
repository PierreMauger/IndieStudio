/*
** EPITECH PROJECT, 2022
** MenuScene.hpp
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP
    #define MENUSCENE_HPP

    #include "IScene.hpp"
    #include "ModelObj.hpp"
    #include "AnimatedModelObj.hpp"
    #include "RectangleObj.hpp"
    #include "SpriteObj.hpp"
    #include "macros.hpp"

namespace neo
{
    class MenuScene : public virtual IScene
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, std::unique_ptr<GameObject>> _buttons;
            int _selectedButton;

        public:
            MenuScene(std::shared_ptr<MessageBus> messageBus);
            ~MenuScene();

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

        private:
            void handleMainPressed(int playerID, std::string action);
            void handleBackPressed(int playerID, std::string action);
            void handleMovePressed(int playerID, std::string action);
    };
}

#endif // MENUSCENE_HPP
