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

    #include "ModelObj.hpp"
    #include "AnimatedModelObj.hpp"
    #include "RectangleObj.hpp"
    #include "SpriteObj.hpp"
    #include "Camera.hpp"
    #include "mappings.hpp"
    #include "macros.hpp"

namespace neo
{
    class Graphics : public virtual Node, public virtual IGraphics
    {
        private:
            std::unique_ptr<Camera> _camera;
            std::map<int, std::unique_ptr<GraphicObject>> _objects;
            std::map<int, std::unique_ptr<GraphicObject>> _buttons;
            std::map<std::string, std::shared_ptr<Model>> _models;
            std::map<std::string, std::shared_ptr<Animation>> _animations;
            std::map<std::string, std::shared_ptr<Texture2D>> _textures;

        public:
            Graphics(std::shared_ptr<MessageBus> messageBus);
            ~Graphics();

            // Node functions
            void run();

            // Interface functions
            void update();
            void draw();
            float getHeightOnMap();

            void receiveResourceList(Packet);
            void receiveLoad(Packet);
            void receiveAdd(Packet);
            void receiveDelete(Packet);
            void receiveSetCameraPos(Packet);
            void receiveSetCameraNextPos(Packet);
            void receiveSetCameraOffset(Packet);
            void receiveMove(Packet);
            void receiveSelectButton(Packet);
    };
}

#endif // GRAPHICS_HPP
