/*
** EPITECH PROJECT, 2022
** Input.cpp
** File description:
** Input
*/

#include "Input.hpp"

using namespace neo;

Input::Input(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Input module created" << std::endl;
}

void Input::onNotify(Message message)
{
    Packet data = message.getData();

    // should not receive any message, but will send on player input
}

void Input::update()
{
    Packet data;

    if (IsKeyPressed(KEY_RIGHT)) {
        data << KEY_RIGHT;
        this->postMessage(Message(data, 0, 1));
    }
}
