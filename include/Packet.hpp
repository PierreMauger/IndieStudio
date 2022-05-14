/*
** EPITECH PROJECT, 2022
** Packet.hpp
** File description:
** Packet
*/

#ifndef PACKET_HPP
    #define PACKET_HPP

    #include "includes.hpp"

namespace neo
{
    class Packet
    {
        private:
            std::vector<std::byte> _data;

        public:
            Packet() = default;
            ~Packet() = default;

            std::vector<std::byte> getData() const;

            bool checkSize(size_t size) const;
            void clear();

            Packet &operator<<(int data);
            Packet &operator<<(float data);
            Packet &operator<<(const std::string &data);

            Packet &operator>>(int &data);
            Packet &operator>>(float &data);
            Packet &operator>>(std::string &data);
    };
}

#endif // PACKET_HPP
