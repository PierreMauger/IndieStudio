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
            std::shared_ptr<Model> _model;

        public:
            ModelObj(GameObject obj, std::shared_ptr<Model> model);
            ~ModelObj() = default;

            void draw(Camera &camera);
            Rectangle getBox() const;
    };
}

#endif // MODEL_OBJ_HPP
