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
    std::vector<std::byte> data = message.getData();

    // should not receive any message, but will send on player input
}

void Input::update()
{

}
