/*
** EPITECH PROJECT, 2022
** Neo.hpp
** File description:
** Neo
*/

#include "Neo.hpp"

using namespace neo;

Neo::Neo() :
_messageBus(std::make_shared<MessageBus>()),
_audio(_messageBus)
{
}
