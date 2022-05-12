/*
** EPITECH PROJECT, 2022
** MessageBus.hpp
** File description:
** MessageBus
*/

#include "MessageBus.hpp"

using namespace neo;

void MessageBus::addReceiver(std::function<void(Message)> messageReceiver)
{
    this->_functionList.push_back(messageReceiver);
}

void MessageBus::sendMessage(Message message)
{
    this->_messageQueue.push(message);
}

void MessageBus::notify()
{
    while (!this->_messageQueue.empty()) {
        int target = this->_messageQueue.front().getTarget();
        // Broadcast message, else send to target
        if (target == -1) {
            for (auto &function : this->_functionList)
                function(this->_messageQueue.front());
        } else {
            if (target < this->_functionList.size())
                this->_functionList[target](this->_messageQueue.front());
        }
        this->_messageQueue.pop();
    }
}
