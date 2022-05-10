/*
** EPITECH PROJECT, 2022
** Loader.hpp
** File description:
** Loader
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
        protected:
            std::shared_ptr<MessageBus> messageBus;
            std::function<void (Message)> getNotify(void);
            void postMessage(Message);
            virtual void onNotify(Message) = 0;
    };
}

#endif
