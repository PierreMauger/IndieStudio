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

    for (int i = KEY_RIGHT; i <= KEY_UP; i++) {
        if (IsKeyPressed(i)) {
            data << i;
            this->postMessage(Message(data, 0, 1));
        }
        if (IsKeyReleased(i)) {
            data << i;
            this->postMessage(Message(data, 1, 1));
        }
    }
}
