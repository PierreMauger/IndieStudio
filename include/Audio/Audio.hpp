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

        public:
            Audio(std::shared_ptr<MessageBus> messageBus);
            ~Audio() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void playSound();
            void playMusic();
            void pauseMusic();
    };
}

#endif // AUDIO_HPP
