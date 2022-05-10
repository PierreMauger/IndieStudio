/*
** EPITECH PROJECT, 2022
** Message.hpp
** File description:
** Message
*/

#ifndef MESSAGE_HPP
    #define MESSAGE_HPP

    #include "Message.hpp"
    #include "includes.hpp"

namespace neo
{
    class Message
    {
        private:
            std::vector<std::byte> data;
            int target;
        public:
            std::vector<std::byte> getData(void);
            int getTarget(void);
    };
}

#endif
