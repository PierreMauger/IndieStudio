/*
** EPITECH PROJECT, 2022
** Loader.hpp
** File description:
** Loader
*/

#ifndef ILOADER_HPP
    #define ILOADER_HPP

    #include "includes.hpp"

namespace neo
{
    class ILoader
    {
        public:
            virtual ~ILoader() = default;

            virtual std::string loadFile(std::string fileName) = 0;
            virtual std::map<std::string, int> loadConfig(std::string fileContent) = 0;
    };
}

#endif // ILOADER_HPP
