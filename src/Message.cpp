/*
** EPITECH PROJECT, 2022
** Message.cpp
** File description:
** Message
*/

#include "Message.hpp"

using namespace neo;

Message::Message(std::vector<std::byte> data, int target)
{
    this->_data = data;
    this->_target = target;
}

std::vector<std::byte> Message::getData() const
{
    return this->_data;
}

int Message::getTarget() const
{
    return this->_target;
}
