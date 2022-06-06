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

bool Packet::checkSize(size_t size) const
{
    return this->_data.size() >= size;
}

void Packet::clear()
{
    this->_data.clear();
}

void Packet::append(const void *data, size_t size)
{
    if (data && size) {
        this->_data.resize(this->_data.size() + size);
        std::memcpy(&this->_data[this->_data.size() - size], data, size);
    }
}

Packet &Packet::operator<<(int data)
{
    this->append(&data, sizeof(int));
    return *this;
}

Packet &Packet::operator<<(float data)
{
    this->append(&data, sizeof(float));
    return *this;
}

Packet &Packet::operator<<(const std::string &data)
{
    *this << static_cast<int>(data.size());

    this->append(data.c_str(), data.size());
    return *this;
}

Packet &Packet::operator<<(const glm::vec3 &data)
{
    *this << data.x << data.y << data.z;

    return *this;
}

Packet &Packet::operator<<(std::map<std::string, int> &data)
{
    *this << static_cast<int>(data.size());

    for (auto &it : data) {
        *this << it.first;
        *this << it.second;
    }
    return *this;
}

Packet &Packet::operator<<(PlayerConfig &data)
{
    *this << data.getMode();
    *this << data.getControllerConfig();
    *this << data.getKeyboardConfig();
    return *this;
}

Packet &Packet::operator<<(GameObject &data)
{
    *this << data.getType();
    *this << data.getName();
    *this << data.getPos();
    *this << data.getScale();
    return *this;
}

Packet &Packet::operator>>(int &data)
{
    if (this->checkSize(sizeof(int))) {
        std::memcpy(&data, &this->_data[0], sizeof(int));
        this->_data.erase(this->_data.begin(), this->_data.begin() + sizeof(int));
    }
    return *this;
}

Packet &Packet::operator>>(float &data)
{
    if (this->checkSize(sizeof(float))) {
        std::memcpy(&data, &this->_data[0], sizeof(float));
        this->_data.erase(this->_data.begin(), this->_data.begin() + sizeof(float));
    }
    return *this;
}

Packet &Packet::operator>>(std::string &data)
{
    int size = 0;
    *this >> size;

    if (size && this->checkSize(size)) {
        data.clear();
        data.resize(size);
        std::memcpy(&data[0], &this->_data[0], size);
        this->_data.erase(this->_data.begin(), this->_data.begin() + size);
    }
    return *this;
}

Packet &Packet::operator>>(glm::vec3 &data)
{
    if (this->checkSize(sizeof(float) * 3)) {
        float x, y, z = 0.0f;
        *this >> x >> y >> z;
        data = glm::vec3(x, y, z);
    }
    return *this;
}

Packet &Packet::operator>>(std::map<std::string, int> &data)
{
    int size = 0;
    *this >> size;

    for (int i = 0; i < size; i++) {
        std::string action;
        int key = 0;

        *this >> action;
        *this >> key;
        data[action] = key;
    }
    return *this;
}

Packet &Packet::operator>>(PlayerConfig &data)
{
    int mode = 0;
    *this >> mode;
    data.setMode(static_cast<bool>(mode));

    *this >> data.getControllerConfig();
    *this >> data.getKeyboardConfig();
    return *this;
}

Packet &Packet::operator>>(GameObject &data)
{
    int type = 0;
    std::string name;
    glm::vec3 pos, scale;

    *this >> type;
    data.setType(type);
    *this >> name;
    data.setName(name);
    *this >> pos >> scale;
    data.setPos(pos);
    data.setScale(scale);
    return *this;
}
