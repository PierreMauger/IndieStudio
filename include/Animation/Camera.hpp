/*
** EPITECH PROJECT, 2022
** Camera.hpp
** File description:
** Camera
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP

    #include "includes.hpp"
    #include "Shader.hpp"
    #include "Animator.hpp"

    #include <GL/glew.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>

namespace neo
{
    class Camera
    {
        private:
            glm::mat4 _view;
            glm::vec3 _pos;
            glm::vec3 _front;
            glm::vec3 _up;
            glm::mat4 _projection;
            glm::mat4 _model;
            neo::Shader _shader;

        public:
            Camera();
            ~Camera() = default;
            neo::Shader &getShader();
            void lookAt(glm::vec3 const &pos, glm::vec3 const &front, glm::vec3 const &up);
            void move(glm::vec3 const &dir);
            void setPos(glm::vec3 const &pos);
            void centerOn(glm::vec3 const &pos);
            void setShader(float time);
            void setOnModel(glm::vec3 pos, glm::vec3 scale);
            void setOnAnimatedModel(glm::vec3 pos, glm::vec3 scale, Animator &animator);
    };
}

#endif // CAMERA_HPP
