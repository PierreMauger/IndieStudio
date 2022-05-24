/*
** EPITECH PROJECT, 2022
** PlayerConfig.hpp
** File description:
** PlayerConfig
*/

#ifndef PLAYERCONFIG_HPP
    #define PLAYERCONFIG_HPP

    #include "includes.hpp"

namespace neo
{
    class PlayerConfig
    {
        private:
            bool _mode;
            std::map<std::string, int> _keyboardConfig;
            std::map<std::string, int> _controllerConfig;
            std::vector<bool> _axisInputs;

        public:
            PlayerConfig();
            ~PlayerConfig() = default;

            std::map<std::string, int> &getActConfig();
            std::map<std::string, int> &getKeyboardConfig();
            std::map<std::string, int> &getControllerConfig();
            std::vector<bool> &getAxisInputs();
            bool getMode() const;

            void setKeyboardConfig(std::map<std::string, int> config);
            void setControllerConfig(std::map<std::string, int> config);
            void setMode(bool mode);
            void setKey(bool mode, std::string action, int key);
    };
}

#endif // PLAYERCONFIG_HPP
