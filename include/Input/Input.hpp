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
            PlayerConfig _config;

        public:
            Input(std::shared_ptr<MessageBus> messageBus);
            ~Input() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void update();
            void checkInputStatus(int key, std::string action, int playerNb);
            void checkKeyStatus(int key, std::string action);
            void checkButtonStatus(int key, std::string action);
            void checkJoystickStatus(int key, std::string action, int playerNb);
            void editConfig(int key, std::string action);

            void receiveKeyConfig(Packet);
    };
}

#endif // INPUT_HPP
