/*
** EPITECH PROJECT, 2022
** ICore.hpp
** File description:
** ICore
*/

#ifndef ICORE_HPP
    #define ICORE_HPP

    #include "includes.hpp"

namespace neo
{
    class ICore
    {
        public:
            virtual ~ICore() = default;

            virtual void update() = 0;
    };
}

#endif // ICORE_HPP
