/*
** EPITECH PROJECT, 2022
** Game.hpp
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

    #include "Node.hpp"
    #include "IGame.hpp"

namespace neo
{
    class Game : public virtual Node, public virtual IGame
    {
        private:
            // attributes

        public:
            Game(std::shared_ptr<MessageBus> messageBus);
            ~Game() = default;

            // Node functions
            void onNotify(Message);

            // Interface functions
            void update();
    };
}

#endif // GAME_HPP
