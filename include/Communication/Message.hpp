/*
** EPITECH PROJECT, 2022
** Message.hpp
** File description:
** Message
*/

#ifndef MESSAGE_HPP
    #define MESSAGE_HPP

    #include "includes.hpp"
    #include "Packet.hpp"

namespace neo
{
    class Message
    {
        private:
            Packet _data;
            int _target;
            int _status;

        public:
            Message(Packet data, int status, int target = -1);
            ~Message() = default;

            Packet getData() const;
            int getTarget() const;
            int getStatus() const;
    };
}

#endif // MESSAGE_HPP
