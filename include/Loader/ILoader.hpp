/*
** EPITECH PROJECT, 2022
** ILoader.hpp
** File description:
** ILoader
*/

#ifndef ILOADER_HPP
    #define ILOADER_HPP

    #include "includes.hpp"
    #include "PlayerConfig.hpp"

namespace neo
{
    class ILoader
    {
        public:
            virtual ~ILoader() = default;

            virtual std::vector<std::string> getFilesFromDir(std::string dir) = 0;
            virtual std::string loadFile(std::string fileName) = 0;
            virtual PlayerConfig loadPlayerConfig(std::string fileContent) = 0;
            virtual std::map<std::string, int> loadConfig(std::string fileContent) = 0;
    };
}

#endif // ILOADER_HPP
