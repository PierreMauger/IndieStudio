/*
** EPITECH PROJECT, 2022
** Input.hpp
** File description:
** Input
*/

#ifndef INPUT_HPP
    #define INPUT_HPP

    #include "Node.hpp"
    #include "IInput.hpp"

namespace neo
{
    class Input : public virtual Node, public virtual IInput
    {
        private:
            // attributes

        public:
            Input(std::shared_ptr<MessageBus> messageBus);
            ~Input() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
    };
}

#endif // INPUT_HPP
