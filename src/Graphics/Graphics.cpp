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
    std::cout << "Graphics module created" << std::endl;
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(600, 600, "Neo");
    SetTargetFPS(60);
    glEnable(GL_DEPTH_TEST);
    this->_pos = {0};
    this->_functionTab = {
        std::bind(&Graphics::receivePos, this, std::placeholders::_1),
    };

    this->_shader = new neo::Shader("ressources/camera.vs", "ressources/camera.fs");
    this->_model = new neo::Model("ressources/FloofFox_model.dae");
}

Graphics::~Graphics()
{
    CloseWindow();
    delete this->_shader;
    delete this->_model;
}

void Graphics::onNotify(Message message)
{
    Packet data = message.getData();
    int status = message.getStatus();

    if (status >= 0 && status < this->_functionTab.size())
        this->_functionTab[status](data);
    // from data, draw elements on screen
}

void Graphics::draw()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("neo genesis evangelion 3.0 + 1.0", 100, 100, 20, LIGHTGRAY);
        DrawCircleV(this->_pos, 20, GREEN);

        this->_shader->use();
        glm::vec3 pos = glm::vec3(this->_pos.x, this->_pos.y, 0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        this->_shader->setMat4("projection", glm::perspective(glm::radians(45.0f), 600.f / 600.f, 0.1f, 100.0f));
        this->_shader->setMat4("view", view);
        this->_shader->setMat4("model", model);

        this->_shader->setVec3("viewPos", 1.0f, 0.0f, 0.0f);
        this->_shader->setVec3("lightPos", 1.0f, 0.0f, 0.0f);

        for (std::size_t i = 0; i < 100; i++)
            this->_shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", glm::mat4(1.0f));

        this->_model->draw(*this->_shader);

    EndDrawing();
}

void Graphics::receivePos(Packet data)
{
    data >> this->_pos.x >> this->_pos.y;
}
