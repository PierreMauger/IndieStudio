/*
** EPITECH PROJECT, 2022
** BotEngine.cpp
** File description:
** BotEngine
*/

#include "BotEngine.hpp"

using namespace neo;

// int BotEngine::getNeighbor(pos_t actPos)
// {
//     if (canMoveToPos({actPos.x + 1, actPos.y}) && this->_visited[actPos.y][actPos.x + 1] == false) {
//         return 1;
//     }
//     else if (canMoveToPos({actPos.x, actPos.y + 1}) && this->_visited[actPos.y + 1][actPos.x] == false) {
//         return 2;
//     }
//     else if (canMoveToPos({actPos.x - 1, actPos.y}) && this->_visited[actPos.y][actPos.x - 1] == false) {
//         return 3;
//     }
//     else if (canMoveToPos({actPos.x, actPos.y - 1}) && this->_visited[actPos.y - 1][actPos.x] == false) {
//         return 4;
//     }
//     return 0;
// }

// void BotEngine::checkEnd(pos_t actPos, pos_t goalPos)
// {
//     this->_visited[actPos.y][actPos.x] = true;
//     if (actPos.x == goalPos.x && actPos.y == goalPos.y) {
//         this->_found = true;
//     }
// }

// void BotEngine::recursive(pos_t actPos, pos_t goalPos)
// {
//     int neighbor = getNeighbor(actPos);

//     this->checkEnd(actPos, goalPos);
//     while (neighbor != 0 && this->_found == false) {
//         switch (neighbor) {
//         case 1: this->recursive({actPos.x + 1, actPos.y}, goalPos);
//             break;
//         case 2: this->recursive({actPos.x, actPos.y + 1}, goalPos);
//             break;
//         case 3: this->recursive({actPos.x - 1, actPos.y}, goalPos);
//             break;
//         case 4: this->recursive({actPos.x, actPos.y - 1}, goalPos);
//             break;
//         default:
//             break;
//         }
//         neighbor = getNeighbor(actPos);
//     }
// }

void BotEngine::getDirection(std::unique_ptr<Player> &bot, std::unique_ptr<Bomb> &bomb)
{
    
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
            getDirection(bot, bomb);
            return;
        }
    }
}

void BotEngine::updateBot(std::shared_ptr<MessageBus> messageBus, std::map<int, std::unique_ptr<Player>> &players,
std::map<int, std::unique_ptr<Bomb>> &bombs, std::map<int, std::unique_ptr<Wall>> &walls,
std::map<int, std::unique_ptr<PowerUp>> &powerUps)
{
    this->_messageBus = std::move(messageBus);
    this->_players = std::move(players);
    this->_bombs = std::move(bombs);
    this->_walls = std::move(walls);
    this->_powerUps = std::move(powerUps);
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