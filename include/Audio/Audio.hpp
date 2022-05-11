/*
** EPITECH PROJECT, 2022
** Audio.hpp
** File description:
** Audio
*/

#ifndef AUDIO_HPP
    #define AUDIO_HPP

    #include "Node.hpp"
    #include "IAudio.hpp"

namespace neo
{
    class Audio : public virtual Node, public virtual IAudio
    {
        private:
            // attributes

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
