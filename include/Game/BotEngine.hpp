/*
** EPITECH PROJECT, 2022
** BotEngine.hpp
** File description:
** BotEngine
*/

#ifndef BOTENGINE_HPP
	#define BOTENGINE_HPP

    #include "GameScene.hpp"

namespace neo
{
    class GameScene;
    
    class BotEngine
    {
    private:
        void dodgeBombs(GameScene *gameScene, const int &bot_key, std::unique_ptr<Player> &bot);
        // dodgeBombs functions
        void getDirection(GameScene *gameScene, std::unique_ptr<Player> &bot, std::unique_ptr<Bomb> &bomb);
        void recursive(GameScene *gameScene, glm::vec3 pos, const int &bot_key);
        void checkEnd(GameScene *gameScene, glm::vec3 pos, const int &bot_key);
        int getNeighbor(GameScene *gameScene, glm::vec3 pos);
        bool canMoveToPos(GameScene *gameScene, glm::vec3 pos);
        
        void doAction(GameScene *gameScene, const int &bot_key, std::string action, bool isPressed);

        std::vector<std::vector<bool>> _visited;
        std::map<int, bool> _founds;
        std::map<int, std::vector<glm::vec3>> _paths;
        std::map<int, directions> _directions;
    public:
        BotEngine();

        void updateBot(GameScene *gameScene);
    };
}

#endif // BOTENGINE_HPP
