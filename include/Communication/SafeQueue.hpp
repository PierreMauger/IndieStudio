/*
** EPITECH PROJECT, 2022
** SafeQueue.hpp
** File description:
** SafeQueue
*/

#ifndef SAFE_QUEUE_HPP
    #define SAFE_QUEUE_HPP

    #include "includes.hpp"
    #include "Message.hpp"

namespace neo
{
    class SafeQueue
    {
        private:
            std::queue<Message> _queue;
            mutable std::mutex _mutex;

        public:
            SafeQueue() = default;
            SafeQueue(const SafeQueue &) = delete;
            SafeQueue(SafeQueue &&) noexcept {};
            std::size_t size() const;
            void push(Message message);
            void pop();
            Message front();
    };
}

#endif // SAFE_QUEUE_HPP
