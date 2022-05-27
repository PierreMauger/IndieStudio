/*
** EPITECH PROJECT, 2022
** ModelObj.hpp
** File description:
** ModelObj
*/

#ifndef MODEL_OBJ_HPP
    #define MODEL_OBJ_HPP

    #include "includes.hpp"
    #include "GraphicObject.hpp"
    #include "Model.hpp"

namespace neo
{
    class ModelObj : public GraphicObject
    {
        private:
            std::unique_ptr<neo::Model> _model;

        public:
            ModelObj(std::string name, Vector2 pos);
            ModelObj(std::string name, Vector2 pos, Vector2 size);
            ~ModelObj() = default;

            void draw(neo::Shader &shader);
    };
}

#endif // MODEL_OBJ_HPP
