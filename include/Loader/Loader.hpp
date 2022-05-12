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
            // attributes

        public:
            Loader(std::shared_ptr<MessageBus> messageBus);
            ~Loader() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
    };
}

#endif // LOADER_HPP
