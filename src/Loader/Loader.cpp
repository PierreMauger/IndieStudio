/*
** EPITECH PROJECT, 2022
** Loader.cpp
** File description:
** Loader
*/

#include "Loader.hpp"

using namespace neo;

Loader::Loader(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Loader module created" << std::endl;
}

void Loader::onNotify(Message message)
{
    Packet data = message.getData();

    // from data, load ressources
}
