/*
** EPITECH PROJECT, 2022
** Audio.cpp
** File description:
** Audio
*/

#include "Audio.hpp"

using namespace neo;

Audio::Audio(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Audio module created" << std::endl;
}

void Audio::onNotify(Message message)
{
    Packet data = message.getData();
}

void Audio::playSound()
{
}

void Audio::playMusic()
{
}

void Audio::pauseMusic()
{
}
