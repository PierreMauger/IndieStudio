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
}

void BotEngine::doAction(GameScene *gameScene, const int &bot_key, std::string action)
{
    Packet data;

    data << bot_key << action;
    gameScene->getMessageBus()->sendMessage(Message(data, CoreCommand::KEY_PRESSED, Module::CORE));
}

bool BotEngine::canMoveToPos(GameScene *gameScene, glm::vec3 pos)
{
    for (auto &[wall_key, wall] : gameScene->getWalls())
        if (pos.x + 0.5f == wall->getPos().x && pos.y + 0.5f == wall->getPos().y)
            return false;
    for (auto &[bomb_key, bomb] : gameScene->getBombs())
        if (pos.x + 0.5f == bomb->getPos().x && pos.y + 0.5f == bomb->getPos().y)
            return false;
    return true;
}

int BotEngine::getNeighbor(GameScene *gameScene, glm::vec3 pos)
{
    if (canMoveToPos(gameScene, glm::vec3(pos.x + 1.f, pos.y, pos.z)) &&
        this->_visited[std::abs(pos.y) + gameScene->getMapGenerator().getHeight() / 2][std::abs(pos.x) + gameScene->getMapGenerator().getWidth() / 2 + 1] == false) {
        return 1;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x, pos.y + 1.f, pos.z)) &&
    this->_visited[std::abs(pos.y) + gameScene->getMapGenerator().getHeight() / 2 + 1][std::abs(pos.x) + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 2;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x - 1.f, pos.y, pos.z)) &&
        this->_visited[std::abs(pos.y) + gameScene->getMapGenerator().getHeight() / 2][std::abs(pos.x) + gameScene->getMapGenerator().getWidth() / 2 - 1] == false) {
        return 3;
    }
    else if (canMoveToPos(gameScene, glm::vec3(pos.x, pos.y - 1.f, pos.z)) &&
        this->_visited[std::abs(pos.y) + gameScene->getMapGenerator().getHeight() / 2 - 1][std::abs(pos.x) + gameScene->getMapGenerator().getWidth() / 2] == false) {
        return 4;
    }
    return 0;
}

void BotEngine::checkEnd(GameScene *gameScene, glm::vec3 pos)
{
    this->_visited[std::abs(pos.y) + gameScene->getMapGenerator().getHeight() / 2][std::abs(pos.x) + gameScene->getMapGenerator().getWidth() / 2] = true;
    for (auto &[bomb_key, bomb] : gameScene->getBombs())
        if (pos.x + 0.5f == bomb->getPos().x &&
            bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > pos.y &&
            pos.y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
            pos.y + 0.5f == bomb->getPos().y &&
            bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > pos.x &&
            pos.x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp())
            return;
    this->_found = true;
}

void BotEngine::recursive(GameScene *gameScene, glm::vec3 pos)
{
    int neighbor = getNeighbor(gameScene, pos);

    this->checkEnd(gameScene, pos);
    while (neighbor != 0 && this->_found == false) {
        switch (neighbor) {
        case 1: this->recursive(gameScene, glm::vec3(pos.x + 1.f, pos.y, pos.z));
            break;
        case 2: this->recursive(gameScene, glm::vec3(pos.x, pos.y + 1.f, pos.z));
            break;
        case 3: this->recursive(gameScene, glm::vec3(pos.x - 1.f, pos.y, pos.z));
            break;
        case 4: this->recursive(gameScene, glm::vec3(pos.x, pos.y - 1.f, pos.z));
            break;
        default:
            break;
        }
        neighbor = getNeighbor(gameScene, pos);
    }
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
            this->_found = false;
            recursive(gameScene, glm::vec3(std::floor(bot->getPos().x), std::floor(bot->getPos().y), bot->getPos().z));
            for (size_t i = 0; i < this->_visited.size(); i++) {
                for (size_t j = 0; j < this->_visited[i].size(); j++)
                    printf("%d ", this->_visited[i][j] ? 1 : 0);
                printf("\n");
            }
            printf("\n");
            for (size_t i = 0; i < gameScene->getMapGenerator().getHeight(); i++)
                for (size_t j = 0; j < gameScene->getMapGenerator().getWidth(); j++)
                    this->_visited[i][j] = false;
            return;
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
