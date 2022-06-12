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

namespace neo
{
    class GameScene : public virtual IScene
    {
        private:
            //update functions
            void updatePlayers(void);
            void explode(std::unique_ptr<Bomb> &bomb);
            void updateBombs(void);

            //others
            bool canPlaceBomb(int playerNb);

            //variables
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<Player>> _players;
            std::map<int, std::unique_ptr<Bomb>> _bombs;
            std::map<int, std::unique_ptr<Wall>> _walls;
            std::map<int, std::unique_ptr<PowerUp>> _powerUps;
            MapGenerator _mapGenerator;
            int _incrementor;

        public:
            GameScene(std::shared_ptr<MessageBus> messageBus);
            ~GameScene();

            // Interface functions
            void update();
            void loadScene();

            void handleKeyPressed(int playerNb, std::string action);
            void handleKeyReleased(int playerNb, std::string action);
    };
}

#endif // GAMESCENE_HPP
