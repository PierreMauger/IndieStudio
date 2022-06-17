/*
** EPITECH PROJECT, 2022
** MapGenerator.hpp
** File description:
** MapGenerator
*/

#ifndef MAPGENERATOR_HPP
	#define MAPGENERATOR_HPP

    #include "includes.hpp"

namespace neo
{
    class MapGenerator
    {
        private:
            std::vector<std::string> generateCornerMap(std::size_t x, std::size_t y);
            std::vector<std::string> copySymmetrical(std::size_t nb_player, std::vector<std::string>);
            void forcePathX(std::vector<std::string> &map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            void forcePathY(std::vector<std::string> &map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            bool findPathX(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            bool findPathY(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x);
            std::string multiplier_str(std::string chr, std::size_t size);

            size_t _width;
            size_t _height;
        public:
            std::vector<std::string> generateProceduralMap(std::size_t nb_player, std::size_t x, std::size_t y);
            const size_t getWidth(void) const;
            const size_t getHeight(void) const;
    };
}

#endif // MAPGENERATOR_HPP
