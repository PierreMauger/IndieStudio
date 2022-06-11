/*
** EPITECH PROJECT, 2022
** PowerUp.hpp
** File description:
** PowerUp
*/

#ifndef PowerUp_HPP
    #define PowerUp_HPP

    #include "GameObject.hpp"

namespace neo
{
    class PowerUp : public virtual GameObject
    {
        public:
            PowerUp(std::string name, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.0f));
    };
}

#endif // PowerUp_HPP