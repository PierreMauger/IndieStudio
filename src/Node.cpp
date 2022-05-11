/*
** EPITECH PROJECT, 2022
** Node.hpp
** File description:
** Node
*/

#include "Node.hpp"

using namespace neo;

Node::Node(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_messageBus->addReceiver(this->getNotify());
}

std::function<void(Message)> Node::getNotify()
{
    auto messageListener = [=](Message message) -> void {
        this->onNotify(message);
    };
    return messageListener;
}

void Node::postMessage(Message message)
{
    this->_messageBus->sendMessage(message);
}
