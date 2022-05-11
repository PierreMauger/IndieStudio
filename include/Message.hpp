/*
** EPITECH PROJECT, 2022
** Message.hpp
** File description:
** Message
*/

#ifndef MESSAGE_HPP
    #define MESSAGE_HPP

    #include "includes.hpp"

namespace neo
{
    class Message
    {
        private:
            std::vector<std::byte> _data;
            int _target;

        public:
            Message(std::vector<std::byte> data, int target = -1);
            ~Message() = default;

            std::vector<std::byte> getData() const;
            int getTarget() const;
    };
}

#endif // MESSAGE_HPP
