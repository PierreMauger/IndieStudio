/*
** EPITECH PROJECT, 2022
** Graphics.hpp
** File description:
** Graphics
*/

#ifndef GRAPHICS_HPP
    #define GRAPHICS_HPP

    #include "IGraphics.hpp"
    #include "Node.hpp"
    #include "ModuleList.hpp"

    #include "GraphicObject.hpp"
    #include "Camera.hpp"
    #include "mappings.hpp"

namespace neo
{
    class Graphics : public virtual Node, public virtual IGraphics
    {
        private:
            std::unique_ptr<neo::Camera> _camera;
            std::map<int, std::unique_ptr<GraphicObject>> _objects;
            std::map<int, std::unique_ptr<GraphicObject>> _buttons;

        public:
            Graphics(std::shared_ptr<MessageBus> messageBus);
            ~Graphics();

            // Node functions
            void onNotify(Message);

            // Interface functions
            void draw();

            void receiveLoadModel(Packet);
            void receiveLoadButton(Packet);
            void receiveMove(Packet);
    };
}

#endif // GRAPHICS_HPP
