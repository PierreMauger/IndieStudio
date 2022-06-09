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
    // if (IsAudioDeviceReady() == false)
        // TODO
    this->_functionTab.push_back(std::bind(&Audio::receivedLoadSounds, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedLoadMusics, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedPlaySound, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedPlayMusic, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedPauseMusic, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedResumeMusic, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Audio::receivedStopMusic, this, std::placeholders::_1));
}

Audio::~Audio()
{
    this->_sounds.clear();
}

void Audio::run()
{
    SetTraceLogLevel(LOG_NONE);
    InitAudioDevice();

    while (this->_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        this->_messageBus->notify(Module::AUDIO);
    }
    if (IsAudioDeviceReady() == true)
        CloseAudioDevice();
}

void Audio::receivedLoadSounds(Packet packet)
{
    std::string fileName;
    Sound sound;

    while (packet.checkSize(1)) {
        packet >> fileName;
        sound = LoadSound(("resources/audio/sounds/" + fileName).c_str());
        if (sound.frameCount == 0) {
            std::cerr << "[ERROR] cannot load " << fileName << std::endl;
            continue;
        }
        this->_sounds[fileName] = std::make_shared<Sound>(sound);
    }
}

void Audio::receivedLoadMusics(Packet packet)
{
    std::string fileName;
    Sound sound;

    while (packet.checkSize(1)) {
        packet >> fileName;
        sound = LoadSound(("resources/audio/musics/" + fileName).c_str());
        if (sound.frameCount == 0) {
            std::cerr << "[ERROR] cannot load " << fileName << std::endl;
            continue;
        }
        this->_musics[fileName] = std::make_shared<Sound>(sound);
    }
}

void Audio::receivedPlaySound(Packet packet)
{
    std::string soundName;

    packet >> soundName;
    if (this->_sounds.find(soundName) == this->_sounds.end())
        return;
    PlaySoundMulti(*this->_sounds[soundName]);
}

void Audio::receivedPlayMusic(Packet packet)
{
    std::string musicName;

    packet >> musicName;
    if (this->_musics.find(musicName) == this->_musics.end())
        return;
    PlaySound(*this->_musics[musicName]);
}

void Audio::receivedPauseMusic(Packet packet)
{
    std::string musicName;

    packet >> musicName;
    if (this->_musics.find(musicName) == this->_musics.end())
        return;
    PauseSound(*this->_musics[musicName]);
}

void Audio::receivedResumeMusic(Packet packet)
{
    std::string musicName;

    packet >> musicName;
    if (this->_musics.find(musicName) == this->_musics.end())
        return;
    ResumeSound(*this->_musics[musicName]);
}

void Audio::receivedStopMusic(Packet packet)
{
    std::string musicName;

    packet >> musicName;
    if (this->_musics.find(musicName) == this->_musics.end())
        return;
    StopSound(*this->_musics[musicName]);
}
