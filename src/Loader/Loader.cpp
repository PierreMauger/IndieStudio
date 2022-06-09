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
    this->sendPlayerConfig();
    this->sendResourceList();
}

void Loader::run()
{
    while (this->_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        this->_messageBus->notify(Module::LOADER);
    }
}

void Loader::sendPlayerConfig()
{
    std::vector<std::string> files = this->getFilesFromDir("resources/config/");
    Packet packet;

    for (auto &file : files) {
        PlayerConfig conf = this->loadPlayerConfig(this->loadFile(file));
        conf.setMode(false);
        packet << conf;
    }
    this->postMessage(Message(packet, InputCommand::KEY_CONFIG, Module::INPUT));
}

void Loader::sendResourceList(void)
{
    std::vector<std::string> modelFiles = this->getFilesFromDir("resources/models/");
    std::vector<std::string> animationFiles = this->getFilesFromDir("resources/animations/");
    std::vector<std::string> soundsFiles = this->getFilesFromDir("resources/audio/sounds/");
    std::vector<std::string> musicsFiles = this->getFilesFromDir("resources/audio/musics/");
    Packet packet;

    for (auto &file : modelFiles) {
        std::filesystem::path path(file);
        packet << 0 << path.filename().string();
    }
    for (auto &file : animationFiles) {
        std::filesystem::path path(file);
        packet << 1 << path.filename().string();
    }
    this->postMessage(Message(packet, GraphicsCommand::RESOURCE_LIST, Module::GRAPHICS));
    // packet.clear();
    // for (auto &file : soundsFiles) {
    //     std::filesystem::path path(file);
    //     packet << path.filename().string();
    // }
    // this->postMessage(Message(packet, AudioCommand::LOAD_SOUNDS, Module::AUDIO));
    // packet.clear();
    // for (auto &file : musicsFiles) {
    //     std::filesystem::path path(file);
    //     packet << path.filename().string();
    // }
    // this->postMessage(Message(packet, AudioCommand::LOAD_MUSICS, Module::AUDIO));
}

std::vector<std::string> Loader::getFilesFromDir(std::string dir)
{
    std::vector<std::string> files;

    for (auto &file : std::filesystem::directory_iterator(dir))
        files.push_back(file.path().string());
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
