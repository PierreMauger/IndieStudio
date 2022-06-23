/*
** EPITECH PROJECT, 2022
** BotEngine.cpp
** File description:
** BotEngine
*/

#include "BotEngine.hpp"

using namespace neo;

BotEngine::BotEngine()
{
    this->_visited = std::vector<std::vector<bool>>(20, std::vector<bool>(20, false));
    for (size_t i = 0; i < 4; i++)
        this->_founds[i] = false;
}

void BotEngine::doAction(GameScene *gameScene, const int &bot_key, std::string action, bool isPressed)
{
    Packet data;

    data << bot_key << action;
    gameScene->getMessageBus()->sendMessage(Message(data, isPressed ? CoreCommand::KEY_PRESSED : CoreCommand::KEY_RELEASED, Module::CORE));
}

bool BotEngine::canMoveToPos(GameScene *gameScene, glm::vec3 pos)
{
    for (auto &[wall_key, wall] : gameScene->getWalls())
        if (pos.x + 0.5f == wall->getPos().x && pos.y - 0.5f == wall->getPos().y)
            return false;
    for (auto &[bomb_key, bomb] : gameScene->getBombs())
        if (pos.x + 0.5f == bomb->getPos().x && pos.y - 0.5f == bomb->getPos().y)
            return false;
    return true;
}

int BotEngine::getNeighbor(GameScene *gameScene, glm::vec3 pos)
{
    if (canMoveToPos(gameScene, glm::vec3(pos.x + 1.0f, pos.y, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2][pos.x + gameScene->getMapGenerator().getWidth() / 2 + 1] == false) {
        return 1;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x, pos.y + 1.0f, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2 - 1][pos.x + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 2;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x - 1.0f, pos.y, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2][pos.x + gameScene->getMapGenerator().getWidth() / 2 - 1] == false) {
        return 3;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x, pos.y - 1.0f, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2 + 1][pos.x + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 4;
    }
    return 0;
}

void BotEngine::checkEnd(GameScene *gameScene, glm::vec3 pos, const int &bot_key, bool dodgeBombs)
{
    this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2][pos.x + gameScene->getMapGenerator().getWidth() / 2] = true;
    if (dodgeBombs) {
        for (auto &[bomb_key, bomb] : gameScene->getBombs()) {
            if (pos.x + 0.5f == bomb->getPos().x &&
                bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > pos.y &&
                pos.y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
                pos.y - 0.5f == bomb->getPos().y &&
                bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > pos.x &&
                pos.x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp())
                return;
        }
        this->_founds[bot_key] = true;
    }
    else {
        for (auto &[player_key, player] : gameScene->getPlayers()) {
            if (player_key != bot_key &&
                pos.x + 0.5f == std::floor(player->getPos().x) + 0.5f &&
                pos.y - 0.5f == std::floor(player->getPos().y) + 0.5f) {
                this->_founds[bot_key] = true;
                return;
            }
        }
    }
}

void BotEngine::recursive(GameScene *gameScene, glm::vec3 pos, const int &bot_key, bool dodgeBombs)
{
    int neighbor = getNeighbor(gameScene, pos);

    this->checkEnd(gameScene, pos, bot_key, dodgeBombs);
    while (neighbor && !this->_founds[bot_key]) {
        switch (neighbor) {
            case 1: this->recursive(gameScene, glm::vec3(pos.x + 1.0f, pos.y, pos.z), bot_key, dodgeBombs);
                break;
            case 2: this->recursive(gameScene, glm::vec3(pos.x, pos.y + 1.0f, pos.z), bot_key, dodgeBombs);
                break;
            case 3: this->recursive(gameScene, glm::vec3(pos.x - 1.0f, pos.y, pos.z), bot_key, dodgeBombs);
                break;
            case 4: this->recursive(gameScene, glm::vec3(pos.x, pos.y - 1.0f, pos.z), bot_key, dodgeBombs);
                break;
            default:
                break;
        }
        neighbor = getNeighbor(gameScene, pos);
    }
    if (this->_founds[bot_key])
        this->_paths[bot_key].push_back(glm::vec3(pos.x + 0.5f, pos.y - 0.5f, pos.z));
}

void BotEngine::startRecursive(GameScene *gameScene, const int &bot_key, std::unique_ptr<Player> &bot, bool dodgeBombs)
{
    if (this->_paths[bot_key].empty() && !this->_founds[bot_key]) {
        recursive(gameScene, glm::vec3(std::floor(bot->getPos().x), std::ceil(bot->getPos().y), bot->getPos().z), bot_key, dodgeBombs);
        for (size_t i = 0; i < this->_visited.size(); i++)
            for (size_t j = 0; j < this->_visited.size(); j++)
                this->_visited[i][j] = false;
        if (!this->_paths[bot_key].empty()) {
            this->_paths[bot_key].pop_back();
            this->_founds[bot_key] = false;
        }
        else
            this->_founds[bot_key] = true;
    }
}

void BotEngine::updateBot(GameScene *gameScene)
{
    for (auto &[player_key, player] : gameScene->getPlayers()) {
        if (!player->isBot())
            continue;
        for (auto &[bomb_key, bomb] : gameScene->getBombs()) {
            if (std::floor(player->getPos().x) + 0.5f == bomb->getPos().x &&
                bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > player->getPos().y &&
                player->getPos().y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
                std::floor(player->getPos().y) + 0.5f == bomb->getPos().y &&
                bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > player->getPos().x &&
                player->getPos().x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp()) {
                startRecursive(gameScene, player_key, player, true);
                break;
            }
        }
        startRecursive(gameScene, player_key, player, false);
        if (!this->_paths[player_key].empty()) {
            if (!this->_founds[player_key]) {
                if (_paths[player_key].back().x == std::floor(player->getPos().x) + 1.5f) {
                    doAction(gameScene, player_key, "MoveRight", true);
                    this->_directions[player_key] = RIGHT;
                }
                if (_paths[player_key].back().y == std::floor(player->getPos().y) + 1.5f) {
                    doAction(gameScene, player_key, "MoveUp", true);
                    this->_directions[player_key] = UP;
                }
                if (_paths[player_key].back().x == std::floor(player->getPos().x) - 0.5f) {
                    doAction(gameScene, player_key, "MoveLeft", true);
                    this->_directions[player_key] = LEFT;
                }
                if (_paths[player_key].back().y == std::floor(player->getPos().y) - 0.5f) {
                    doAction(gameScene, player_key, "MoveDown", true);
                    this->_directions[player_key] = DOWN;
                }
                this->_founds[player_key] = true;
            }
            else {
                if (this->_directions[player_key] == RIGHT && player->getPos().x > _paths[player_key].back().x ||
                    this->_directions[player_key] == UP && player->getPos().y > _paths[player_key].back().y ||
                    this->_directions[player_key] == LEFT && player->getPos().x < _paths[player_key].back().x ||
                    this->_directions[player_key] == DOWN && player->getPos().y < _paths[player_key].back().y) {
                    if (this->_directions[player_key] == RIGHT)
                        doAction(gameScene, player_key, "MoveRight", false);
                    if (this->_directions[player_key] == UP)
                        doAction(gameScene, player_key, "MoveUp", false);
                    if (this->_directions[player_key] == LEFT)
                        doAction(gameScene, player_key, "MoveLeft", false);
                    if (this->_directions[player_key] == DOWN)
                        doAction(gameScene, player_key, "MoveDown", false);
                    this->_paths[player_key].pop_back();
                    this->_founds[player_key] = false;
                }
            }
        }
    }
}
