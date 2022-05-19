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
            std::string loadFile(std::string fileName);
            std::map<int, std::string> loadConfig(std::string fileContent);
    };
}

#endif // LOADER_HPP
