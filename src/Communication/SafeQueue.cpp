/*
** EPITECH PROJECT, 2022
** SafeQueue.cpp
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"

using namespace neo;

std::size_t SafeQueue::size() const
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    return this->_queue.size();
}

void SafeQueue::push(Message message)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_queue.push(message);
}

void SafeQueue::pop()
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    Message message = this->_queue.front();
    this->_queue.pop();
}

Message SafeQueue::front()
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    return this->_queue.front();
}
