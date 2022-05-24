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
    this->_pos = {0, 0};
    this->_speed = {0, 0};

    this->_functionTab = {
        std::bind(&Game::receiveKeyPressed, this, std::placeholders::_1),
        std::bind(&Game::receiveKeyReleased, this, std::placeholders::_1),
    };
}

void Game::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}

void Game::update()
{
    if (this->_speed.x != 0 || this->_speed.y != 0) {
        this->_pos.x += this->_speed.x;
        this->_pos.y += this->_speed.y;
        Packet packet;
        packet << this->_pos.x << this->_pos.y;
        this->postMessage(Message(packet, 0, 2));
    }
}

void Game::receiveKeyPressed(Packet data)
{
    std::string key;
    int playerNb = 0;

    data >> playerNb >> key;
    if (key == "MoveRight")
        this->_speed.x += 1;
    if (key == "MoveLeft")
        this->_speed.x -= 1;
    if (key == "MoveUp")
        this->_speed.y -= 1;
    if (key == "MoveDown")
        this->_speed.y += 1;
}

void Game::receiveKeyReleased(Packet data)
{
    std::string key;
    int playerNb = 0;

    data >> playerNb >> key;
    if (key == "MoveRight")
        this->_speed.x -= 1;
    if (key == "MoveLeft")
        this->_speed.x += 1;
    if (key == "MoveUp")
        this->_speed.y += 1;
    if (key == "MoveDown")
        this->_speed.y -= 1;
}
