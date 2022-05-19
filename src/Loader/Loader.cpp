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

    this->loadConfig(this->loadFile("ressources/input.conf"));
}

void Loader::onNotify(Message message)
{
    Packet data = message.getData();

    // from data, load ressources
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

std::map<int, std::string> Loader::loadConfig(std::string fileContent)
{
    std::map<int, std::string> config;
    std::stringstream buffer(fileContent);
    std::string line;

    while (std::getline(buffer, line)) {
        std::stringstream lineBuffer(line);
        std::string key;
        std::string value;

        std::getline(lineBuffer, key, ':');
        std::getline(lineBuffer, value);
        config[std::stoi(key)] = value;
    }
    for (auto &it : config)
        std::cout << it.first << ": " << it.second << std::endl;
    return config;
}
