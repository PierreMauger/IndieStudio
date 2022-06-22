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
        // recursive backtracking functions
        void recursive(GameScene *gameScene, glm::vec3 pos, const int &bot_key, bool dodgeBombs);
        void checkEnd(GameScene *gameScene, glm::vec3 pos, const int &bot_key, bool dodgeBombs);
        int getNeighbor(GameScene *gameScene, glm::vec3 pos, bool dodgeBombs);
        bool canMoveToPos(GameScene *gameScene, glm::vec3 pos, bool dodgeBombs);

        //main bot functions
        void dodgeBombs(GameScene *gameScene, const int &bot_key, std::unique_ptr<Player> &bot);
        void searchPlayer(GameScene *gameScene, const int &bot_key, std::unique_ptr<Player> &bot);
        
        // bot input function
        void doAction(GameScene *gameScene, const int &bot_key, std::string action, bool isPressed);

        // bot recursive backtracking variables
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
