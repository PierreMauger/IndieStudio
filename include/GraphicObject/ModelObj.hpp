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
            std::shared_ptr<neo::Model> _model;

        public:
            ModelObj(GameObject obj, std::shared_ptr<neo::Model> model);
            ~ModelObj() = default;

            void draw(neo::Camera &camera);
    };
}

#endif // MODEL_OBJ_HPP
