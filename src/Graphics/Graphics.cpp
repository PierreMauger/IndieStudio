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
        std::bind(&Graphics::receiveRessourceList, this, std::placeholders::_1),
        std::bind(&Graphics::receiveLoad, this, std::placeholders::_1),
        std::bind(&Graphics::receiveMove, this, std::placeholders::_1),
        std::bind(&Graphics::receiveSelectButton, this, std::placeholders::_1),
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

    this->_camera->getShader().use();
    this->_camera->setPos(glm::vec3(0.0f, 0.0f, 10.0f));
    // this->_camera->setShader(0.0f);
    this->_camera->setShader(GetTime() * 100);

    for (auto &object : this->_objects)
        object.second->draw(*this->_camera);
    for (auto &button : this->_buttons)
        button.second->draw(*this->_camera);
    EndDrawing();
}

void Graphics::receiveRessourceList(Packet data)
{
    while (data.checkSize(1)) {
        std::string file;
        int type;
        data >> type >> file;
        std::string fileName = file.substr(0, file.find_last_of("."));

        if (type == 0)
            this->_models[fileName] = std::shared_ptr<neo::Model>(new Model("ressources/models/" + file));
        else if (type == 1) {
            this->_models[fileName] = std::shared_ptr<neo::Model>(new Model("ressources/animations/" + file));
            this->_animations[fileName] = std::shared_ptr<neo::Animation>(new Animation("ressources/animations/" + file, this->_models[fileName].get()));
        }
    }
    Packet packet;
    this->_messageBus->sendMessage(Message(packet, CoreCommand::GRAPHICS_READY, Module::CORE));
}

void Graphics::receiveLoad(Packet data)
{
    this->_objects.clear();

    while (data.checkSize(1)) {
        int id = 0;
        int type = 0;
        GameObject obj;

        data >> type >> id >> obj;
        if (type == 0 && this->_models.find(obj.getName()) != this->_models.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new ModelObj(obj, this->_models[obj.getName()]));
        else if (type == 1 && this->_models.find(obj.getName()) != this->_models.end() && this->_animations.find(obj.getName()) != this->_animations.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new AnimatedModelObj(obj, this->_models[obj.getName()], this->_animations[obj.getName()]));
        else if (type == 2)
            this->_buttons[id] = std::unique_ptr<GraphicObject>(new RectangleObj(obj));
        else if (type == 3)
            this->_buttons[id] = std::unique_ptr<GraphicObject>(new SpriteObj(obj));
    }
}

void Graphics::receiveMove(Packet data)
{
    int id;
    float x, y;

    data >> id >> x >> y;
    this->_objects[id]->setPos(CAST(Vector2, x, y));
}

void Graphics::receiveSelectButton(Packet data)
{
    int id;
    int status;

    data >> id >> status;
    if (this->_buttons.find(id) != this->_buttons.end())
        this->_buttons[id]->setStatus(status);
}
