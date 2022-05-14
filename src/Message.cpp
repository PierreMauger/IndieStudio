/*
** EPITECH PROJECT, 2022
** Message.cpp
** File description:
** Message
*/

#include "Message.hpp"

using namespace neo;

Message::Message(Packet data, int status, int target)
{
    this->_data = data;
    this->_status = status;
    this->_target = target;
}

Packet Message::getData() const
{
    return this->_data;
}

int Message::getTarget() const
{
    return this->_target;
}

int Message::getStatus() const
{
    return this->_status;
}
