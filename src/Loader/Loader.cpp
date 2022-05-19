/*
** EPITECH PROJECT, 2022
** Loader.cpp
** File description:
** Loader
*/

#include "Loader.hpp"

using namespace neo;

Loader::Loader(std::shared_ptr<MessageBus> messageBus) : Node(messageBus)
{
    std::cout << "Loader module created" << std::endl;
    Packet packet;

    std::map<std::string, int> config = this->loadConfig(this->loadFile("ressources/input.conf"));
    packet << config;
    this->postMessage(Message(packet, 0, 3));
}

void Loader::onNotify(Message message)
{
    Packet data = message.getData();
}

std::string Loader::loadFile(std::string fileName)
{
    std::ifstream fileBuffer;
    std::string buffer;

    fileBuffer.open(fileName);
    if (fileBuffer.is_open()) {
        std::getline(fileBuffer, buffer, '\0');
        fileBuffer.close();
    }
    return buffer;
}

std::map<std::string, int> Loader::loadConfig(std::string fileContent)
{
    std::map<std::string, int> config;
    std::stringstream buffer(fileContent);
    std::string line;

    while (std::getline(buffer, line)) {
        std::stringstream lineBuffer(line);
        std::string key;
        std::string action;

        std::getline(lineBuffer, action, ':');
        std::getline(lineBuffer, key);
        config[action] = std::stoi(key);
    }
    return config;
}
