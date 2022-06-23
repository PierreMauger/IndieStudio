/*
** EPITECH PROJECT, 2022
** ConfigScene.hpp
** File description:
** ConfigScene
*/

#ifndef CONFIGSCENE_HPP
    #define CONFIGSCENE_HPP

    #include "IScene.hpp"
    #include "MapGenerator.hpp"

namespace neo
{
    class ConfigScene : public virtual IScene
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, std::unique_ptr<GameObject>> _buttons;
            std::vector<bool> _playerConnected;
            std::vector<int> _playerModel;
            std::vector<int> _playerConfig;
            std::vector<int> _playerMode;
            std::vector<std::string> _availableModels;
            std::vector<std::string> _availableConfigs;
            MapGenerator _mapGenerator;
            std::vector<std::string> _map;

            void addCard(int card);
            void deleteCard(int card);
            void changeModel(int card);
            void changeConfig(int card);
            void changeMode(int card);

        public:
            ConfigScene(std::shared_ptr<MessageBus> messageBus);
            ~ConfigScene();

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyReleased(int playerNb, std::string action);
            void handleButtonClicked(int button);
            void handleConfig(std::vector<std::string> config);
            void handleStartGame(Packet data);
    };
}

#endif // CONFIGSCENE_HPP
