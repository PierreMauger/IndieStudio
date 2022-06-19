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
    this->_found = false;
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
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2 + 1][pos.x + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 2;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x - 1.0f, pos.y, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2][pos.x + gameScene->getMapGenerator().getWidth() / 2 - 1] == false) {
        return 3;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x, pos.y - 1.0f, pos.z)) &&
        this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2 - 1][pos.x + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 4;
    }
    return 0;
}

void BotEngine::checkEnd(GameScene *gameScene, glm::vec3 pos)
{
    this->_visited[-pos.y + gameScene->getMapGenerator().getHeight() / 2][pos.x + gameScene->getMapGenerator().getWidth() / 2] = true;
    for (auto &[bomb_key, bomb] : gameScene->getBombs())
        if (pos.x + 0.5f == bomb->getPos().x &&
            bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > pos.y - 1.0f &&
            pos.y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
            pos.y - 0.5f == bomb->getPos().y &&
            bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > pos.x &&
            pos.x + 1.0f > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp())
            return;
    this->_found = true;
}

void BotEngine::recursive(GameScene *gameScene, glm::vec3 pos)
{
    int neighbor = getNeighbor(gameScene, pos);

    this->checkEnd(gameScene, pos);
    while (neighbor && !this->_found) {
        switch (neighbor) {
        case 1: this->recursive(gameScene, glm::vec3(pos.x + 1.0f, pos.y, pos.z));
            break;
        case 2: this->recursive(gameScene, glm::vec3(pos.x, pos.y + 1.0f, pos.z));
            break;
        case 3: this->recursive(gameScene, glm::vec3(pos.x - 1.0f, pos.y, pos.z));
            break;
        case 4: this->recursive(gameScene, glm::vec3(pos.x, pos.y - 1.0f, pos.z));
            break;
        default:
            break;
        }
        neighbor = getNeighbor(gameScene, pos);
    }
    if (this->_found)
        this->_path.push_back(glm::vec3(pos.x + 0.5f, pos.y - 0.5f, pos.z));
}

void BotEngine::dodgeBombs(GameScene *gameScene, const int &bot_key, std::unique_ptr<Player> &bot)
{
    for (auto &[bomb_key, bomb] : gameScene->getBombs()) {
        if (std::floor(bot->getPos().x) + 0.5f == bomb->getPos().x &&
            bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > bot->getPos().y &&
            bot->getPos().y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
            std::floor(bot->getPos().y) + 0.5f == bomb->getPos().y &&
            bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > bot->getPos().x &&
            bot->getPos().x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp()) {
            if (this->_path.empty()) {
                for (size_t i = 0; i < this->_visited.size(); i++)
                    for (size_t j = 0; j < this->_visited.size(); j++)
                        this->_visited[i][j] = false;
                recursive(gameScene, glm::vec3(std::floor(bot->getPos().x), std::ceil(bot->getPos().y), bot->getPos().z));
                if (!this->_path.empty())
                    this->_path.pop_back();
                this->_found = false;
            }
        }
        if (!this->_path.empty()) {
            if (!this->_found) {
                if (_path.back().x == std::floor(bot->getPos().x) + 1.5f) {
                    doAction(gameScene, bot_key, "MoveRight", true);
                    this->_direction = RIGHT;
                }
                if (_path.back().y == std::floor(bot->getPos().y) + 1.5f) {
                    doAction(gameScene, bot_key, "MoveUp", true);
                    this->_direction = UP;
                }
                if (_path.back().x == std::floor(bot->getPos().x) - 0.5f) {
                    doAction(gameScene, bot_key, "MoveLeft", true);
                    this->_direction = LEFT;
                }
                if (_path.back().y == std::floor(bot->getPos().y) - 0.5f) {
                    doAction(gameScene, bot_key, "MoveDown", true);
                    this->_direction = DOWN;
                }
                this->_found = true;
            }
            else {
                if (this->_direction == RIGHT && bot->getPos().x > _path.back().x ||
                    this->_direction == UP && bot->getPos().y > _path.back().y ||
                    this->_direction == LEFT && bot->getPos().x < _path.back().x ||
                    this->_direction == DOWN && bot->getPos().y < _path.back().y) {
                    if (this->_direction == RIGHT)
                        doAction(gameScene, bot_key, "MoveRight", false);
                    if (this->_direction == UP)
                        doAction(gameScene, bot_key, "MoveUp", false);
                    if (this->_direction == LEFT)
                        doAction(gameScene, bot_key, "MoveLeft", false);
                    if (this->_direction == DOWN)
                        doAction(gameScene, bot_key, "MoveDown", false);
                    this->_path.pop_back();
                    this->_found = false;
                }
            }
        }
    }
}

void BotEngine::updateBot(GameScene *gameScene)
{
    for (auto &[player_key, player] : gameScene->getPlayers()) {
        if (!player->isBot())
            continue;
        dodgeBombs(gameScene, player_key, player);
    }
}
