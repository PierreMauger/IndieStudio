/*
** EPITECH PROJECT, 2022
** GameScene.cpp
** File description:
** GameScene
*/

#include "GameScene.hpp"

using namespace neo;

GameScene::GameScene()
{
    this->_objects.insert(std::make_pair(0, std::make_unique<GameObject>(0, "ressources/models/FloofFox.dae", (Vector2){1, 1})));
    this->_objects.insert(std::make_pair(1, std::make_unique<GameObject>(0, "ressources/models/FloofFox.dae", (Vector2){0, 0})));
    this->_playerSpeed.insert(std::make_pair(0, Vector2{0, 0}));
    this->_playerSpeed.insert(std::make_pair(1, Vector2{0, 0}));
}

GameScene::~GameScene()
{
    for (auto &object : this->_objects)
        object.second.reset();
}

void GameScene::update(std::shared_ptr<MessageBus> messageBus)
{
    for (auto &playerSpeed : this->_playerSpeed) {
        if (playerSpeed.second.x != 0 || playerSpeed.second.y != 0) {
            if (this->_objects.find(playerSpeed.first) == this->_objects.end())
                break;
            this->_objects[playerSpeed.first]->move(playerSpeed.second);
            Packet packet;
            packet << playerSpeed.first << this->_objects[playerSpeed.first]->getPos().x << this->_objects[playerSpeed.first]->getPos().y;
            messageBus->sendMessage(Message(packet, GraphicsCommand::MOVE, Module::GRAPHICS));
            packet.clear();
        }
    }
}

void GameScene::loadScene(std::shared_ptr<MessageBus> messageBus)
{
    Packet packet;

    for (auto &object : this->_objects)
        packet << 0 << object.first << *object.second;
    messageBus->sendMessage(Message(packet, GraphicsCommand::LOAD, Module::GRAPHICS));
}

void GameScene::handleKeyPressed(int playerNb, std::string action)
{
    if (this->_playerSpeed.find(playerNb) == this->_playerSpeed.end())
        return;
    if (action == "MoveRight")
        this->_playerSpeed[playerNb].x += 0.1f;
    else if (action == "MoveLeft")
        this->_playerSpeed[playerNb].x -= 0.1f;
    else if (action == "MoveUp")
        this->_playerSpeed[playerNb].y += 0.1f;
    else if (action == "MoveDown")
        this->_playerSpeed[playerNb].y -= 0.1f;
}

void GameScene::handleKeyRelease(int playerNb, std::string action)
{
    if (this->_playerSpeed.find(playerNb) == this->_playerSpeed.end())
        return;
    if (action == "MoveRight")
        this->_playerSpeed[playerNb].x -= 0.1f;
    else if (action == "MoveLeft")
        this->_playerSpeed[playerNb].x += 0.1f;
    else if (action == "MoveUp")
        this->_playerSpeed[playerNb].y -= 0.1f;
    else if (action == "MoveDown")
        this->_playerSpeed[playerNb].y += 0.1f;
}
