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
_core(_messageBus),
_graphics(_messageBus),
_input(_messageBus),
_loader(_messageBus)
{
}

void Neo::run()
{
    while (!WindowShouldClose()) {
        this->_input.update();
        this->_core.update();
        this->_graphics.draw();

        this->_messageBus->notify();
    }
}
