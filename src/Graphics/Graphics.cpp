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
    this->_pos = {0};
    this->_camera = std::unique_ptr<Camera>(new Camera());

    this->_functionTab = {
        std::bind(&Graphics::receivePos, this, std::placeholders::_1),
    };
    this->_model = new neo::Model("ressources/FloofFox_model.dae");
}

Graphics::~Graphics()
{
    CloseWindow();
    delete this->_model;
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

    glm::vec3 pos = glm::vec3(this->_pos.x / 5.f, -this->_pos.y / 5.f, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);

    this->_camera->getShader().setMat4("model", model);
    for (std::size_t i = 0; i < 100; i++)
        this->_camera->getShader().setMat4("finalBonesMatrices[" + std::to_string(i) + "]", glm::mat4(1.0f));

    this->_model->draw(this->_camera->getShader());
    EndDrawing();
}

void Graphics::receivePos(Packet data)
{
    data >> this->_pos.x >> this->_pos.y;
}
