/*
** EPITECH PROJECT, 2022
** IGraphics.hpp
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP
    #define IGRAPHICS_HPP

    #include "includes.hpp"

namespace neo
{
    class IGraphics
    {
        public:
            virtual ~IGraphics() = default;

            virtual void draw() = 0;
    };
}

#endif // IGRAPHICS_HPP
