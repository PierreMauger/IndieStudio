/*
** EPITECH PROJECT, 2022
** Audio.hpp
** File description:
** Audio
*/

#include "Audio.hpp"

using namespace neo;

Audio::Audio(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
}

void Audio::onNotify(Message message)
{
    std::vector<std::byte> data = message.getData();

    // from data, get the sound/music to play
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
