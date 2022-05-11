/*
** EPITECH PROJECT, 2022
** Node.hpp
** File description:
** Node
*/

#ifndef NODE_HPP
    #define NODE_HPP

    #include "MessageBus.hpp"
    #include "Message.hpp"
    #include "includes.hpp"

namespace neo
{
    class Node
    {
    public:
        Node(std::shared_ptr<MessageBus> messageBus);
        virtual ~Node() = default;

        protected:
            std::shared_ptr<MessageBus> _messageBus;

            std::function<void (Message)> getNotify(void);
            void postMessage(Message);
            virtual void onNotify(Message) = 0;
    };
}

#endif
