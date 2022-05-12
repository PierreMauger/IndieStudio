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
    #include "Game.hpp"
    #include "Graphics.hpp"
    #include "Input.hpp"
    #include "Loader.hpp"

namespace neo
{
    class Neo
    {
        private:
            std::shared_ptr<MessageBus> _messageBus;
            Audio _audio;
            Game _game;
            Graphics _graphics;
            Input _input;
            Loader _loader;

        public:
            Neo();
            ~Neo() = default;
    };
}

#endif // NEO_HPP
