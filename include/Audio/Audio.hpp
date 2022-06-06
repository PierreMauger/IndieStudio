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

        public:
            Audio(std::shared_ptr<MessageBus> messageBus);
            ~Audio();

            // Node functions
            void onNotify(Message);

            // Interface functions
            void receivedLoad(Packet);

            void receivedPlay(Packet);
            void receivedPause(Packet);
            void receivedResume(Packet);
            void receivedStop(Packet);

    };
};

#endif // AUDIO_HPP
