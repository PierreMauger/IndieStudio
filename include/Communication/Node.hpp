/*
** EPITECH PROJECT, 2022
** Node.hpp
** File description:
** Node
*/

#ifndef NODE_HPP
    #define NODE_HPP

    #include "includes.hpp"
    #include "Message.hpp"
    #include "MessageBus.hpp"
    #include "Packet.hpp"

namespace neo
{
    class Node
    {
        protected:
            std::shared_ptr<MessageBus> _messageBus;
            std::vector<std::function<void(Packet)>> _functionTab;
            bool _running;

            std::function<void(Message)> getNotify();
            void postMessage(Message);
            void onNotify(Message);
            virtual void run() = 0;

        public:
            Node(std::shared_ptr<MessageBus> messageBus);
            virtual ~Node() = default;
    };
}

#endif // NODE_HPP
