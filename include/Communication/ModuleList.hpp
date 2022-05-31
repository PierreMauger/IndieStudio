/*
** EPITECH PROJECT, 2022
** ModuleList.hpp
** File description:
** ModuleList
*/

#ifndef MODULE_ENUM_HPP
    #define MODULE_ENUM_HPP

namespace neo
{
    enum class Module
    {
        AUDIO,
        CORE,
        GRAPHICS,
        INPUT,
        LOADER,

        BROADCAST = -1
    };

    class BaseCommand
    {
        public:
            enum {
                LAST
            };
    };

    class AudioCommand : public BaseCommand
    {
        public:
            enum {
                // TODO
            };
    };

    class CoreCommand : public BaseCommand
    {
        public:
            enum {
                KEY_PRESSED = BaseCommand::LAST,
                KEY_RELEASED,
                GRAPHICS_READY,
            };
    };

    class GraphicsCommand : public BaseCommand
    {
        public:
            enum {
                RESOURCE_LIST = BaseCommand::LAST,
                LOAD,
                MOVE,
                SELECT_BUTTON
            };
    };

    class InputCommand : public BaseCommand
    {
        public:
            enum {
                KEY_CONFIG = BaseCommand::LAST,
            };
    };
}

#endif // MODULE_ENUM_HPP
