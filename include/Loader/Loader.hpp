/*
** EPITECH PROJECT, 2022
** Loader.hpp
** File description:
** Loader
*/

#ifndef LOADER_HPP
    #define LOADER_HPP

    #include "Node.hpp"
    #include "ILoader.hpp"

    #include <regex>
    #include <filesystem>

namespace neo
{
    class Loader : public virtual Node, public virtual ILoader
    {
        private:

        public:
            Loader(std::shared_ptr<MessageBus> messageBus);
            ~Loader() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            std::vector<std::string> getFilesFromDir(std::string dir);
            std::string loadFile(std::string fileName);
            PlayerConfig loadPlayerConfig(std::string fileContent);
            std::map<std::string, int> loadConfig(std::string fileContent);
    };
}

#endif // LOADER_HPP
