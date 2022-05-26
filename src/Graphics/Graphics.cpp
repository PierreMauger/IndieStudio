/*
** EPITECH PROJECT, 2022
** Graphics.cpp
** File description:
** Graphics
*/

#include "Graphics.hpp"

using namespace neo;

Graphics::Graphics(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(600, 600, "Neo");
    SetTargetFPS(60);
    glEnable(GL_DEPTH_TEST);
    for (int i = 0; getMapping(i); i++)
        SetGamepadMappings(getMapping(i));
    this->_camera = std::unique_ptr<Camera>(new Camera());

    this->_functionTab = {
        std::bind(&Graphics::receiveLoad, this, std::placeholders::_1),
    };
}

Graphics::~Graphics()
{
    CloseWindow();
    for (auto &object : this->_objects)
        object.second.reset();
    this->_camera.reset();
}

void Graphics::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
}

void Graphics::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    this->_camera->getShader().use();
    this->_camera->setPos(glm::vec3(0.0f, 0.0f, 10.0f));
    this->_camera->setShader(0.0f);

    for (auto &object : this->_objects) {
        this->_camera->setOnModel(object.second->getPosition());
        object.second->draw(this->_camera->getShader());
    }
    EndDrawing();
}

void Graphics::receiveLoad(Packet data)
{
    this->_objects.clear();

    while (data.checkSize(1)) {
        int id;
        float x, y;
        std::string name;

        data >> id >> x >> y >> name;
        this->_objects[id] = std::unique_ptr<GraphicObject>(new GraphicObject(name, glm::vec3(x, y, 0)));
    }
}
