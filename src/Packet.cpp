/*
** EPITECH PROJECT, 2022
** Packet.cpp
** File description:
** Packet
*/

#include "Packet.hpp"

using namespace neo;

bool Packet::checkSize(size_t size) const
{
    return (this->_data.size() >= size);
}

std::vector<std::byte> Packet::getData() const
{
    return this->_data;
}

Packet &Packet::operator<<(int data)
{
    this->_data.push_back(static_cast<std::byte>(data & 0xFF));
    this->_data.push_back(static_cast<std::byte>(data >> 8 & 0xFF));
    this->_data.push_back(static_cast<std::byte>(data >> 16 & 0xFF));
    this->_data.push_back(static_cast<std::byte>(data >> 24 & 0xFF));
    return *this;
}

Packet &Packet::operator<<(const std::string &data)
{
    *this << static_cast<int>(data.size());
    for (auto &c : data)
        this->_data.push_back(static_cast<std::byte>(c));
    return *this;
}

Packet &Packet::operator>>(int &data)
{
    if (this->checkSize(sizeof(int))) {
        data = 0;
        for (size_t i = 0; i < sizeof(int); i++)
            data += static_cast<int>(this->_data[i]) << (i * 8);
        this->_data.erase(this->_data.begin(), this->_data.begin() + sizeof(int));
    }
    return *this;
}

Packet &Packet::operator>>(std::string &data)
{
    int size = 0;
    *this >> size;

    if (size && this->checkSize(size)) {
        data.clear();
        for (size_t i = 0; i < size; i++)
            data += static_cast<char>(this->_data[i]);
        this->_data.erase(this->_data.begin(), this->_data.begin() + size);
    }
    return *this;
}
