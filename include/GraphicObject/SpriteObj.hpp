/*
** EPITECH PROJECT, 2022
** SpriteObj.hpp
** File description:
** SpriteObj
*/

#ifndef SPRITE_OBJ_HPP
    #define SPRITE_OBJ_HPP

    #include "includes.hpp"
    #include "GraphicObject.hpp"

namespace neo
{
    class SpriteObj : public GraphicObject
    {
        private:
            std::shared_ptr<Texture2D> _texture;
            glm::vec2 _coords;

        public:
            SpriteObj(GameObject obj, std::shared_ptr<Texture2D> texture);
            ~SpriteObj() = default;

            void draw(Camera &camera);
            Rectangle getBox() const;
    };
}

#endif // SPRITE_OBJ_HPP
