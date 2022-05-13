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
    InitWindow(600, 600, "Neo");
    SetTargetFPS(60);
}

Graphics::~Graphics()
{
    CloseWindow();
}

void Graphics::onNotify(Message message)
{
    std::vector<std::byte> data = message.getData();

    // from data, draw elements on screen
}

void Graphics::draw()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("dorian dans le .gitignore", 100, 100, 20, LIGHTGRAY);
    EndDrawing();
}
