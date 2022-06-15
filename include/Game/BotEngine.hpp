/*
** EPITECH PROJECT, 2022
** BotEngine.hpp
** File description:
** BotEngine
*/

#ifndef BOTENGINE_HPP
	#define BOTENGINE_HPP

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
    class BotEngine
    {
    private:
        void getDirection(std::unique_ptr<Player> &bot, std::unique_ptr<Bomb> &bomb);
        void dodgeBombs(std::unique_ptr<Player> &bot);
        void recursive(glm::vec3 pos);
        void checkEnd(glm::vec3 pos);
        int getNeighbor(glm::vec3 pos);
        bool canMoveToPos(glm::vec3 pos);

        std::shared_ptr<MessageBus> _messageBus;
        std::map<int, std::unique_ptr<Player>> _players;
        std::map<int, std::unique_ptr<Bomb>> _bombs;
        std::map<int, std::unique_ptr<Wall>> _walls;
        std::map<int, std::unique_ptr<PowerUp>> _powerUps;
        MapGenerator _mapGenerator;
        std::vector<std::vector<bool>> _visited;
        bool _found;
    public:
        BotEngine();

        void updateBot(std::shared_ptr<MessageBus> messageBus,
            std::map<int, std::unique_ptr<Player>> &players,
            std::map<int, std::unique_ptr<Bomb>> &bombs,
            std::map<int, std::unique_ptr<Wall>> &walls,
            std::map<int, std::unique_ptr<PowerUp>> &powerUps,
            MapGenerator mapGenerator);
    };
}

#endif // BOTENGINE_HPP
