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
    #include "SafeQueue.hpp"

namespace neo
{
    class MessageBus
    {
        private:
            std::vector<std::function<void(Message)>> _functionList;
            std::vector<SafeQueue> _queue;

        public:
            void addReceiver(std::function<void(Message)>);
            void notify(Module module);
            void sendMessage(Message);
    };
}

#endif // MESSAGE_BUS_HPP
