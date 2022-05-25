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
    #include "Camera.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class Graphics : public virtual Node, public virtual IGraphics
    {
        private:
            Vector2 _pos;
            std::unique_ptr<neo::Camera> _camera;
            neo::Model *_model;
            Animation *_animation;
            Animator *_animator;

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
