/*
** EPITECH PROJECT, 2022
** Game.cpp
** File description:
** Game
*/

#include "Game.hpp"

using namespace neo;

Game::Game(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Game module created" << std::endl;
}

void Game::onNotify(Message message)
{
    Packet data = message.getData();
    std::string str;
    int nb;
    std::string str2;

    data >> str >> nb >> str2;
    std::cout << str << " " << nb << " " << str2 << std::endl;
    // from data, handle player movement/bombs etc
}

void Game::update()
{

}
