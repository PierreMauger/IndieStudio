/*
** EPITECH PROJECT, 2022
** Graphics.cpp
** File description:
** Graphics
*/

#include "Graphics.hpp"

using namespace neo;

Graphics::Graphics(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Graphics module created" << std::endl;
}

void Graphics::onNotify(Message message)
{
    std::vector<std::byte> data = message.getData();

    // from data, draw elements on screen
}
