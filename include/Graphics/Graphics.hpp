/*
** EPITECH PROJECT, 2022
** Graphics.hpp
** File description:
** Graphics
*/

#ifndef GRAPHICS_HPP
    #define GRAPHICS_HPP

    #include "Node.hpp"
    #include "IGraphics.hpp"
    #include "Model.hpp"

namespace neo
{
    class Graphics : public virtual Node, public virtual IGraphics
    {
        private:
            Vector2 _pos;
            neo::Shader *_shader;
            neo::Model *_model;

        public:
            Graphics(std::shared_ptr<MessageBus> messageBus);
            ~Graphics();

            // Node functions
            void onNotify(Message);

            // Interface functions
            void draw();

            void receivePos(Packet);
    };
}

#endif // GRAPHICS_HPP
