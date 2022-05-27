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
        std::bind(&Graphics::receiveLoadModel, this, std::placeholders::_1),
        std::bind(&Graphics::receiveLoadButton, this, std::placeholders::_1),
        std::bind(&Graphics::receiveMove, this, std::placeholders::_1),
    };
}

Graphics::~Graphics()
{
    CloseWindow();
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
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

    for (auto &button : this->_buttons)
        DrawRectangle(button.second->getPos().x, button.second->getPos().y, button.second->getSize().x, button.second->getSize().y, RED);

    this->_camera->getShader().use();
    this->_camera->setPos(glm::vec3(0.0f, 0.0f, 10.0f));
    this->_camera->setShader(0.0f);

    for (auto &object : this->_objects) {
        this->_camera->setOnModel(object.second->getPos());
        object.second->draw(this->_camera->getShader());
    }
    EndDrawing();
}

void Graphics::receiveLoadModel(Packet data)
{
    this->_objects.clear();

    while (data.checkSize(1)) {
        int id;
        float x, y;
        std::string name;

        data >> id >> x >> y >> name;
        this->_objects[id] = std::unique_ptr<GraphicObject>(new ModelObj(name, glm::vec3(x, y, 0)));
    }
}

void Graphics::receiveLoadButton(Packet data)
{
    int id;
    float x, y, w, h;
    std::string name;

    data >> id >> x >> y >> w >> h >> name;
    this->_buttons[id] = std::unique_ptr<GraphicObject>(new RectangleObj(name, glm::vec3(x, y, 0), glm::vec3(w, h, 0)));
}

void Graphics::receiveMove(Packet data)
{
    int id;
    float x, y;

    data >> id >> x >> y;
    this->_objects[id]->setPos(glm::vec3(x, y, 0));
}
