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
    this->_x = 0;
    this->_y = 0;
    this->_functionTab = {
        std::bind(&Game::receiveInput, this, std::placeholders::_1),
    };
}

void Game::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
    // from data, handle player movement/bombs etc
}

void Game::update()
{

}

void Game::receiveInput(Packet data)
{
    int key = 0;

    data >> key;
    if (key == KEY_RIGHT) {
        Packet packet;
        packet << "Player moving left";
        this->postMessage(Message(packet, 0, 2));
    }
}
