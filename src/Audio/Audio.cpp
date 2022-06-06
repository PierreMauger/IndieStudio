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
    InitAudioDevice();

    // if (IsAudioDeviceReady() == false)
        // TODO
    this->_functionTab = {
        std::bind(&Audio::receivedLoad, this, std::placeholders::_1),
        std::bind(&Audio::receivedPlay, this, std::placeholders::_1),
        std::bind(&Audio::receivedPause, this, std::placeholders::_1),
        std::bind(&Audio::receivedResume, this, std::placeholders::_1),
        std::bind(&Audio::receivedStop, this, std::placeholders::_1),
    };
}

Audio::~Audio()
{
    this->_sounds.clear();
    if (IsAudioDeviceReady() == true)
        CloseAudioDevice();
}

void Audio::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}

void Audio::receivedLoad(Packet packet)
{
    std::string fileName;
    Sound sound;

    while (packet.checkSize(1)) {
        packet >> fileName;
        sound = LoadSound(("resources/audio/" + fileName).c_str());
        if (sound.frameCount == 0)
            continue;
        this->_sounds[fileName] = std::make_shared<Sound>(sound);
    }
}

void Audio::receivedPlay(Packet packet)
{
    std::string soundName;

    packet >> soundName;
    PlaySound(*this->_sounds[soundName]);
}

void Audio::receivedPause(Packet packet)
{
    std::string soundName;

    packet >> soundName;
    PauseSound(*this->_sounds[soundName]);
}

void Audio::receivedResume(Packet packet)
{
    std::string soundName;

    packet >> soundName;
    ResumeSound(*this->_sounds[soundName]);
}

void Audio::receivedStop(Packet packet)
{
    std::string soundName;

    packet >> soundName;
    StopSound(*this->_sounds[soundName]);
}
