/*
** EPITECH PROJECT, 2022
** MessageBus.hpp
** File description:
** MessageBus
*/

#ifndef MESSAGE_BUS_HPP
    #define MESSAGE_BUS_HPP

    #include "includes.hpp"
    #include "Message.hpp"

namespace neo
{
    class MessageBus
    {
        private:
            std::vector<std::function<void ()>> functionList;
            std::queue<Message> messageQueue;
        public:
            void addReceiver(std::function<void (Message)>);
            void notify(void);
            void sendMessage(Message);
    };
}

#endif
