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

namespace neo
{
    class Graphics : public virtual Node, public virtual IGraphics
    {
        private:
            // attributes

        public:
            Graphics(std::shared_ptr<MessageBus> messageBus);
            ~Graphics();

            // Node functions
            void onNotify(Message);

            // Interface functions
            void draw();
    };
}

#endif // GRAPHICS_HPP
