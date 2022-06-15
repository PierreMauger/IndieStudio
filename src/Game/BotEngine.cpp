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

bool BotEngine::canMoveToPos(glm::vec3 pos)
{
    for (auto &[wall_key, wall] : this->_walls)
        if (pos.x + 0.5f == wall->getPos().x && pos.y + 0.5f == wall->getPos().y)
            return false;
    return true;
}

int BotEngine::getNeighbor(glm::vec3 pos)
{
    printf("%f %f\n", pos.x, pos.y);
    if (canMoveToPos(glm::vec3(pos.x + 1.f, pos.y, pos.z)) && this->_visited[pos.y][pos.x + 1] == false) {
        return 1;
    }
    else if (canMoveToPos(glm::vec3(pos.x, pos.y + 1.f, pos.z)) && this->_visited[pos.y + 1][pos.x] == false) {
        return 2;
    }
    else if (canMoveToPos(glm::vec3(pos.x - 1.f, pos.y, pos.z)) && this->_visited[pos.y][pos.x - 1] == false) {
        return 3;
    }
    else if (canMoveToPos(glm::vec3(pos.x, pos.y - 1.f, pos.z)) && this->_visited[pos.y - 1][pos.x] == false) {
        return 4;
    }
    return 0;
}

void BotEngine::checkEnd(glm::vec3 pos)
{
    this->_visited[pos.y][pos.x] = true;
    for (auto &[bomb_key, bomb] : this->_bombs)
        if (pos.x + 0.5f == bomb->getPos().x &&
            bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > pos.y &&
            pos.y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
            pos.y + 0.5f == bomb->getPos().y &&
            bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > pos.x &&
            pos.x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp())
            return;
    this->_found = true;
}

void BotEngine::recursive(glm::vec3 pos)
{
    int neighbor = getNeighbor(pos);

    this->checkEnd(pos);
    while (neighbor != 0 && this->_found == false) {
        switch (neighbor) {
        case 1: this->recursive(glm::vec3(pos.x + 1.f, pos.y, pos.z));
            break;
        case 2: this->recursive(glm::vec3(pos.x, pos.y + 1.f, pos.z));
            break;
        case 3: this->recursive(glm::vec3(pos.x - 1.f, pos.y, pos.z));
            break;
        case 4: this->recursive(glm::vec3(pos.x, pos.y - 1.f, pos.z));
            break;
        default:
            break;
        }
        neighbor = getNeighbor(pos);
    }
}

void BotEngine::dodgeBombs(std::unique_ptr<Player> &bot)
{
    for (auto &[bomb_key, bomb] : this->_bombs) {
        if (std::floor(bot->getPos().x) + 0.5f == bomb->getPos().x &&
            bomb->getPos().y + 2.5f + 1.0f * bomb->getFireUp() > bot->getPos().y &&
            bot->getPos().y > bomb->getPos().y - 2.5f - 1.0f * bomb->getFireUp() ||
            std::floor(bot->getPos().y) + 0.5f == bomb->getPos().y &&
            bomb->getPos().x + 2.5f + 1.0f * bomb->getFireUp() > bot->getPos().x &&
            bot->getPos().x > bomb->getPos().x - 2.5f - 1.0f * bomb->getFireUp()) {
            this->_found = false;
            this->_visited.clear();
            for (size_t i = 0; i < _mapGenerator.getHeight(); i++) {
                this->_visited.push_back(std::vector<bool>());
                for (size_t j = 0; j < _mapGenerator.getWidth(); j++)
                    this->_visited[i].push_back(false);
            }
            recursive(glm::vec3(std::floor(bot->getPos().x), std::floor(bot->getPos().y), bot->getPos().z));
            for (size_t i = 0; i < this->_visited.size(); i++) {
                for (size_t j = 0; j <  this->_visited[i].size(); j++)
                    printf("%d ", this->_visited[i][j] ? 1 : 0);
                printf("\n");
            }
            printf("\n");
            return;
        }
    }
}

void BotEngine::updateBot(std::shared_ptr<MessageBus> messageBus, std::map<int, std::unique_ptr<Player>> &players,
std::map<int, std::unique_ptr<Bomb>> &bombs, std::map<int, std::unique_ptr<Wall>> &walls,
std::map<int, std::unique_ptr<PowerUp>> &powerUps, MapGenerator mapGenerator)
{
    this->_messageBus = std::move(messageBus);
    this->_players = std::move(players);
    this->_bombs = std::move(bombs);
    this->_walls = std::move(walls);
    this->_powerUps = std::move(powerUps);
    this->_mapGenerator = mapGenerator;
    for (auto &[player_key, player] : this->_players) {
        if (!player->isBot())
            continue;
        dodgeBombs(player);
    }
    messageBus = std::move(this->_messageBus);
    players = std::move(this->_players);
    bombs = std::move(this->_bombs);
    walls = std::move(this->_walls);
    powerUps = std::move(this->_powerUps);
}
