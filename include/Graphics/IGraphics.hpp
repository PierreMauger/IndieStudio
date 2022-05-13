/*
** EPITECH PROJECT, 2022
** Graphics.hpp
** File description:
** Graphics
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
