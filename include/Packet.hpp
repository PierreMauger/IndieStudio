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
            Packet &operator<<(const std::string &str);
            Packet &operator>>(std::string &str);
    };
}

#endif // PACKET_HPP
