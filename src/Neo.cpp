/*
** EPITECH PROJECT, 2022
** Neo.cpp
** File description:
** Neo
*/

#include "Neo.hpp"

using namespace neo;

Neo::Neo() :
_messageBus(std::make_shared<MessageBus>()),
_audio(_messageBus),
_loader(_messageBus),
_core(_messageBus),
_graphics(_messageBus),
_input(_messageBus)
{
    std::srand(std::time(nullptr));
}

void Neo::run()
{
    std::thread audioThread(&Audio::run, &this->_audio);
    std::thread loaderThread(&Loader::run, &this->_loader);
    std::thread coreThread(&Core::run, &this->_core);
    std::thread graphicsThread(&Graphics::run, &this->_graphics);
    std::thread inputThread(&Input::run, &this->_input);

    audioThread.join();
    loaderThread.join();
    coreThread.join();
    graphicsThread.join();
    inputThread.join();
}
