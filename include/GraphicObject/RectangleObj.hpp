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
    #include "Model.hpp"
    #include "Animation.hpp"
    #include "Animator.hpp"

namespace neo
{
    class RectangleObj : public GraphicObject
    {
        private:
        public:
            RectangleObj(std::string name, glm::vec3 pos);
            RectangleObj(std::string name, glm::vec3 pos, glm::vec3 size);
            ~RectangleObj() = default;

            void draw(neo::Shader &shader);
    };
}

#endif // RECTANGLE_OBJ_HPP
