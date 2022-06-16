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
    this->_functionTab.push_back(std::bind(&Graphics::receiveResourceList, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveLoad, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveAdd, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveDelete, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveSetCameraPos, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveSetCameraNextPos, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveSetCameraOffset, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveMove, this, std::placeholders::_1));
    this->_functionTab.push_back(std::bind(&Graphics::receiveSelectButton, this, std::placeholders::_1));
}

Graphics::~Graphics()
{
    for (auto &object : this->_objects)
        object.second.reset();
    for (auto &button : this->_buttons)
        button.second.reset();
    for (auto &model : this->_models)
        model.second.reset();
    for (auto &animation : this->_animations)
        animation.second.reset();
    for (auto &texture : this->_textures)
        texture.second.reset();
    this->_objects.clear();
    this->_buttons.clear();
    this->_models.clear();
    this->_animations.clear();
    this->_textures.clear();
    this->_camera.reset();
}

void Graphics::run()
{
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "Neo");
    SetTargetFPS(60);
    for (int i = 0; getMapping(i); i++)
        SetGamepadMappings(getMapping(i));
    this->_camera = std::unique_ptr<Camera>(new Camera());

    while (this->_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        this->draw();
        this->_messageBus->notify(Module::GRAPHICS);
        if (WindowShouldClose())
            this->_messageBus->sendMessage(Message(Packet(), BaseCommand::QUIT, Module::BROADCAST));
    }
    CloseWindow();
}

void Graphics::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    this->_camera->getShader().use();
    this->_camera->setShader(GetTime());

    glEnable(GL_DEPTH_TEST);
    for (auto &object : this->_objects)
        if (!object.second->getStatus())
            object.second->draw(*this->_camera);
    for (auto &object : this->_objects)
        if (object.second->getStatus()) {
            glClear(GL_DEPTH_BUFFER_BIT);
            object.second->draw(*this->_camera);
        }
    glDisable(GL_DEPTH_TEST);
    for (auto &button : this->_buttons)
        button.second->draw(*this->_camera);
    EndDrawing();
}

float Graphics::getHeightOnMap()
{
    float x = 0.0f;
    float y = 0.0f;

    for (auto &object : this->_objects) {
        if (object.second->getPos().x > x)
            x = object.second->getPos().x;
        if (object.second->getPos().y > y)
            y = object.second->getPos().y;
    }
    y *= (float)GetScreenHeight() / (float)GetScreenWidth();
    return ((x > y ? x : y) + 1) / glm::tan(glm::radians(45.0f / 2.0f));
}

void Graphics::receiveResourceList(Packet data)
{
    while (data.checkSize(1)) {
        int type;
        std::string file;
        data >> type >> file;
        std::string fileName = file.substr(0, file.find_last_of("."));

        if (type == 0) {
            this->_models[fileName] = std::shared_ptr<Model>(new Model("resources/models/" + file));
        } else if (type == 1) {
            this->_models[fileName] = std::shared_ptr<Model>(new Model("resources/animations/" + file));
            this->_animations[fileName] = std::shared_ptr<Animation>(new Animation("resources/animations/" + file, *this->_models[fileName]));
        } else if (type == 2) {
            this->_textures[fileName] = std::make_shared<Texture2D>(LoadTexture(std::string("resources/textures/" + file).c_str()));
        }
    }
    this->_messageBus->sendMessage(Message(Packet(), CoreCommand::GRAPHICS_READY, Module::CORE));
}

void Graphics::receiveLoad(Packet data)
{
    this->_objects.clear();
    this->_buttons.clear();

    while (data.checkSize(1)) {
        int type = 0;
        int id = 0;
        GameObject obj;

        data >> type >> id >> obj;
        if (type == 0 && this->_models.find(obj.getName()) != this->_models.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new ModelObj(obj, this->_models[obj.getName()]));
        else if (type == 1 && this->_models.find(obj.getName()) != this->_models.end() && this->_animations.find(obj.getName()) != this->_animations.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new AnimatedModelObj(obj, this->_models[obj.getName()], this->_animations[obj.getName()]));
        else if (type == 2)
            this->_buttons[id] = std::unique_ptr<GraphicObject>(new RectangleObj(obj));
        else if (type == 3 && this->_textures.find(obj.getName()) != this->_textures.end())
            this->_buttons[id] = std::unique_ptr<GraphicObject>(new SpriteObj(obj, this->_textures[obj.getName()]));
    }
}

void Graphics::receiveAdd(Packet data)
{
    while (data.checkSize(1)) {
        int type = 0;
        int id = 0;
        GameObject obj;

        data >> type >> id >> obj;
        if (type == 0 && this->_models.find(obj.getName()) != this->_models.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new ModelObj(obj, this->_models[obj.getName()]));
        else if (type == 1 && this->_models.find(obj.getName()) != this->_models.end() && this->_animations.find(obj.getName()) != this->_animations.end())
            this->_objects[id] = std::unique_ptr<GraphicObject>(new AnimatedModelObj(obj, this->_models[obj.getName()], this->_animations[obj.getName()]));
    }
}

void Graphics::receiveDelete(Packet data)
{
    while (data.checkSize(1)) {
        int id = 0;
        data >> id;
        if (this->_objects.find(id) != this->_objects.end())
            this->_objects.erase(id);
    }
}

void Graphics::receiveSetCameraPos(Packet data)
{
    int type;
    glm::vec3 pos;

    data >> type >> pos;
    if (type == 0)
        this->_camera->setRotating(false);
    else
        this->_camera->setRotating(true);
    this->_camera->setPos(pos);
}

void Graphics::receiveSetCameraNextPos(Packet data)
{
    glm::vec3 nextPos, nextFront;
    int type;

    data >> type;
    if (type == 0) {
        data >> nextPos >> nextFront;
        this->_camera->setMovement(nextPos, nextFront);
    } else {
        this->_camera->setMovement(glm::vec3(0.0f, 0.0f, this->getHeightOnMap()), glm::vec3(0.0f));
    }
}

void Graphics::receiveSetCameraOffset(Packet data)
{
    glm::vec3 delay;

    data >> delay;
    delay.x -= (float)GetScreenWidth() / 2.0f;
    delay.y -= (float)GetScreenHeight() / 2.0f;
    delay.x /= 50.0f;
    delay.y /= 10.0f;
    this->_camera->setRotation(delay);
}

void Graphics::receiveMove(Packet data)
{
    int id;
    float x, y, z;

    data >> id >> x >> y >> z;
    if (this->_objects.find(id) == this->_objects.end())
        return;
    if (this->_objects[id]->getPos().x < x)
        this->_objects[id]->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
    else if (this->_objects[id]->getPos().x > x)
        this->_objects[id]->setRotation(glm::vec3(0.0f, 0.0f, 270.0f));
    else if (this->_objects[id]->getPos().y < y)
        this->_objects[id]->setRotation(glm::vec3(0.0f, 0.0f, 180.0f));
    else if (this->_objects[id]->getPos().y > y)
        this->_objects[id]->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    this->_objects[id]->setPos(glm::vec3(x, y, z));
}

void Graphics::receiveSelectButton(Packet data)
{
    int id;
    int status;

    data >> id >> status;
    if (this->_objects.find(id) != this->_objects.end())
        this->_objects[id]->setStatus(status);
}
