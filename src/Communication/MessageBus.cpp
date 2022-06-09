/*
** EPITECH PROJECT, 2022
** MessageBus.cpp
** File description:
** MessageBus
*/

#include "MessageBus.hpp"

using namespace neo;

void MessageBus::addReceiver(std::function<void(Message)> messageReceiver)
{
    this->_functionList.push_back(messageReceiver);
    this->_queue.push_back(SafeQueue());
}

void MessageBus::sendMessage(Message message)
{
    if (message.getTarget() == (int)Module::BROADCAST) {
        for (auto &queue : this->_queue)
            queue.push(message);
    } else {
        this->_queue[message.getTarget()].push(message);
    }
}

void MessageBus::notify(Module module)
{
    SafeQueue &queue = this->_queue[(int)module];
    auto &function = this->_functionList[(int)module];

    while (queue.size() != 0) {
        int target = queue.front().getTarget();
        // Broadcast message, else send to target
        if (target == -1) {
            function(queue.front());
            queue.pop();
        } else {
            function(queue.front());
            queue.pop();
        }
    }
}
