/*
** EPITECH PROJECT, 2022
** Packet.cpp
** File description:
** Packet
*/

#include "Packet.hpp"

using namespace neo;

std::vector<std::byte> Packet::getData() const
{
    return this->_data;
}

Packet &Packet::operator<<(const std::string &str)
{
    this->_data.push_back(static_cast<std::byte>(str.size()));
    for (auto c : str)
        this->_data.push_back((std::byte)c);
    return *this;
}

Packet &Packet::operator>>(std::string &str)
{
    int size = static_cast<int>(this->_data[0]);

    for (int i = 0; i < size; ++i)
        str.push_back((char)this->_data[i + 1]);
    this->_data.erase(this->_data.begin(), this->_data.begin() + size + 1);
    return *this;
}
