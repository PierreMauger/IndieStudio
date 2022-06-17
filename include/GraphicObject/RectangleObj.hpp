/*
** EPITECH PROJECT, 2022
** RectangleObj.hpp
** File description:
** RectangleObj
*/

#ifndef RECTANGLE_OBJ_HPP
    #define RECTANGLE_OBJ_HPP

    #include "includes.hpp"
    #include "GraphicObject.hpp"

namespace neo
{
    class RectangleObj : public GraphicObject
    {
        private:
        public:
            RectangleObj(GameObject obj);
            ~RectangleObj() = default;

            void draw(Camera &camera);
    };
}

#endif // RECTANGLE_OBJ_HPP
