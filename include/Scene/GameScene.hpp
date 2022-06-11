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

namespace neo
{
    class GameScene : public virtual IScene
    {
        enum directions {
            RIGHT,
            LEFT,
            UP,
            DOWN
        };

        private:
            // map generation
            std::vector<std::string> generateProceduralMap(std::size_t nb_player, std::size_t x, std::size_t y);
            std::vector<std::string> generateCornerMap(std::size_t x, std::size_t y);
            std::vector<std::string> copySymmetrical(std::size_t nb_player, std::vector<std::string>);
            void forcePathX(std::vector<std::string> &map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            void forcePathY(std::vector<std::string> &map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            bool findPathX(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            bool findPathY(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            std::string multiplier_str(std::string chr, std::size_t size);

            //update functions
            void GameScene::updatePlayers(void);
            void GameScene::updateBombs(void);

            //others
            bool GameScene::canPlaceBomb(int playerNb);

            //variables
            std::shared_ptr<MessageBus> _messageBus;
            std::map<int, std::unique_ptr<Player>> _players;
            std::map<int, std::unique_ptr<Bomb>> _bombs;
            std::map<int, std::unique_ptr<Wall>> _map;
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
