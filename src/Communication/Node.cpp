/*
** EPITECH PROJECT, 2022
** Node.cpp
** File description:
** Node
*/

#include "Node.hpp"

using namespace neo;

Node::Node(std::shared_ptr<MessageBus> messageBus)
{
    this->_messageBus = messageBus;
    this->_messageBus->addReceiver(this->getNotify());
    this->_running = true;
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

void Node::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}
