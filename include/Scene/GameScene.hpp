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
    #include "macros.hpp"
    #include "Bomb.hpp"
    #include "Player.hpp"
    #include "Wall.hpp"
    #include "PowerUp.hpp"
    #include "MapGenerator.hpp"
    #include "BotEngine.hpp"

namespace neo
{
    class BotEngine;

    class GameScene : public virtual IScene
    {
        private:
            //update functions
            void updatePlayers(void);
            void explode(std::unique_ptr<Bomb> &bomb);
            void updateBombs(void);
            void updateAI(void);

            //others
            bool canPlaceBomb(int playerID);

            //variables
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<Player>> _players;
            std::map<int, std::unique_ptr<Bomb>> _bombs;
            std::map<int, std::unique_ptr<Wall>> _walls;
            std::map<int, std::unique_ptr<PowerUp>> _powerUps;
            std::map<int, std::unique_ptr<GameObject>> _objects;
            std::unique_ptr<BotEngine> _botEngine;
            std::map<int, std::string> _winners;
            std::vector<std::string> _storedMap;
            int _top;
            Vector2 _mapSize;
            int _incrementor;
            float _winTimer;

        public:
            GameScene(std::shared_ptr<MessageBus> messageBus);
            ~GameScene();

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

            std::shared_ptr<MessageBus> getMessageBus();
            std::map<int, std::unique_ptr<Player>> &getPlayers();
            std::map<int, std::unique_ptr<Bomb>> &getBombs();
            std::map<int, std::unique_ptr<Wall>> &getWalls();
            std::map<int, std::unique_ptr<PowerUp>> &getPowerUps();
            Vector2 getMapSize();
    };
}

#endif // GAMESCENE_HPP
