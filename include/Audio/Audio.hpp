/*
** EPITECH PROJECT, 2022
** Audio.hpp
** File description:
** Audio
*/

#ifndef AUDIO_HPP
    #define AUDIO_HPP

    #include "IAudio.hpp"
    #include "Node.hpp"
    #include "ModuleList.hpp"

namespace neo
{
    class Audio : public virtual Node, public virtual IAudio
    {
        private:
            std::map<std::string, std::shared_ptr<Sound>> _sounds;
            std::map<std::string, std::shared_ptr<Sound>> _musics;

        public:
            Audio(std::shared_ptr<MessageBus> messageBus);
            ~Audio();

            // Node functions
            void onNotify(Message);

            // Interface functions
            void receivedLoadSounds(Packet);
            void receivedLoadMusics(Packet);

            void receivedPlaySound(Packet);

            void receivedPlayMusic(Packet);
            void receivedPauseMusic(Packet);
            void receivedResumeMusic(Packet);
            void receivedStopMusic(Packet);

    };
};

#endif // AUDIO_HPP
