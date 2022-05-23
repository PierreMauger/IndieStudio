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

    std::map<std::string, int> config = this->loadConfig(this->loadFile("ressources/input/player1.conf"));
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
    std::regex regex("(\\S+):(\\d+)");
    std::smatch match;

    while (std::regex_search(fileContent, match, regex)) {
        config[match[1]] = std::stoi(match[2]);
        fileContent = match.suffix().str();
    }
    return config;
}
