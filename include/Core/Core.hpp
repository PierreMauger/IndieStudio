/*
** EPITECH PROJECT, 2022
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP
    #define CORE_HPP

    #include "Node.hpp"
    #include "ICore.hpp"
    #include "IScene.hpp"

namespace neo
{
    class Core : public virtual Node, public virtual ICore
    {
        private:
            std::vector<std::shared_ptr<IScene>> _scenes;
            int _currentScene;
            // Vector2 _pos;
            // Vector2 _speed;

        public:
            Core(std::shared_ptr<MessageBus> messageBus);
            ~Core() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void update();

            void receiveKeyPressed(Packet);
            void receiveKeyReleased(Packet);
    };
}

#endif // CORE_HPP
