/*
** EPITECH PROJECT, 2022
** Neo.hpp
** File description:
** Neo
*/

#ifndef NEO_HPP
    #define NEO_HPP

    #include "includes.hpp"
    #include "Audio.hpp"

namespace neo
{
    class Neo
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            Audio _audio;

        public:
            Neo();
            ~Neo() = default;
    };
}

#endif // NEO_HPP
