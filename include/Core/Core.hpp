/*
** EPITECH PROJECT, 2022
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP
    #define CORE_HPP

    #include "ICore.hpp"
    #include "Node.hpp"
    #include "ModuleList.hpp"

    #include "IScene.hpp"

namespace neo
{
    class Core : public virtual Node, public virtual ICore
    {
        private:
            std::vector<std::unique_ptr<IScene>> _scenes;
            int _currentScene;

        public:
            Core(std::shared_ptr<MessageBus> messageBus);
            ~Core() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void update();

            void receiveKeyPressed(Packet);
            void receiveKeyReleased(Packet);
            void receiveGraphicsReady(Packet);
    };
}

#endif // CORE_HPP
