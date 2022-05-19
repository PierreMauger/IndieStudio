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
            std::vector<bool> _axisInputs;
            std::map<std::string, int> _config;

        public:
            Input(std::shared_ptr<MessageBus> messageBus);
            ~Input() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void update();
            void checkKeyStatus(int key);
            void editConfig(int key, std::string action);

            void receiveKeyConfig(Packet);
    };
}

#endif // INPUT_HPP
