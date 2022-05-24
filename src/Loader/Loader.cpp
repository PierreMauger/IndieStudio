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
    Packet packet;

    PlayerConfig conf = this->loadPlayerConfig(this->loadFile("ressources/config/player1.conf"));
    conf.setMode(true);
    packet << conf;
    this->postMessage(Message(packet, 0, 3));
}

void Loader::onNotify(Message message)
{
    Packet data = message.getData();
}

std::vector<std::string> Loader::getFilesFromDir(std::string dir)
{
    std::vector<std::string> files;

    for (auto &file : std::filesystem::directory_iterator(dir))
        files.push_back(file.path());
    return files;
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

PlayerConfig Loader::loadPlayerConfig(std::string fileContent)
{
    PlayerConfig playerConfig;
    std::regex regex("(.Keyboard:\n|.Controller:\n)([^.]*)");
    std::smatch match;

    while (std::regex_search(fileContent, match, regex)) {
        if (match[1] == ".Keyboard:\n") {
            playerConfig.setKeyboardConfig(this->loadConfig(match[2]));
        } else if (match[1] == ".Controller:\n") {
            playerConfig.setControllerConfig(this->loadConfig(match[2]));
        }
        fileContent = match.suffix().str();
    }
    return playerConfig;
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
