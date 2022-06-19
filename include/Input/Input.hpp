/*
** EPITECH PROJECT, 2022
** Input.hpp
** File description:
** Input
*/

#ifndef INPUT_HPP
    #define INPUT_HPP

    #include "IInput.hpp"
    #include "Node.hpp"
    #include "ModuleList.hpp"

namespace neo
{
    class Input : public virtual Node, public virtual IInput
    {
        private:
            std::vector<PlayerConfig> _configs;
            std::map<int, PlayerConfig> _usedConfigs;

        public:
            Input(std::shared_ptr<MessageBus> messageBus);
            ~Input() = default;

            // Node functions
            void run();

            // Interface functions
            void update();
            void editConfig(int key, std::string action);
            float checkAxisStatus(int gamepad, int key, std::string action);
            void checkInputStatus(int key, std::string action, int playerNb);
            void checkKeyStatus(int key, std::string action, int playerNb);
            void checkButtonStatus(int key, std::string action, int playerNb);
            void checkJoystickStatus(int key, std::string action, int playerNb);

            void receiveKeyConfig(Packet);
            void receiveChangeConfig(Packet);
    };
}

#endif // INPUT_HPP
