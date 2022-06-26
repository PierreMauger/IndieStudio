/*
** EPITECH PROJECT, 2022
** MappingScene.hpp
** File description:
** MappingScene
*/

#ifndef MAPPING_SCENE_HPP
    #define MAPPING_SCENE_HPP

    #include "IScene.hpp"

namespace neo
{
    class MappingScene : public virtual IScene
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::map<int, std::unique_ptr<GameObject>> _buttons;

        public:
            MappingScene(std::shared_ptr<MessageBus> messageBus);
            ~MappingScene();

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
    };
}

#endif // MAPPING_SCENE_HPP
