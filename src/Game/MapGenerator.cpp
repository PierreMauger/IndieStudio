/*
** EPITECH PROJECT, 2022
** MapGenerator.cpp
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"

using namespace neo;

std::string MapGenerator::multiplier_str(std::string chr, std::size_t size)
{
    std::string str = chr;

    for (size_t i = 1; i != size; i++)
        str += chr;
    return str;
}

std::vector<std::string> MapGenerator::copySymmetrical(std::size_t nbPlayers, std::vector<std::string> map)
{
    std::size_t max_y = map.size();

    for (auto &m : map)
        m += std::string(m.rbegin(), m.rend());
    for (std::size_t i = max_y - 1; i != -1; i--)
        map.push_back(map[i]);
    return map;
}

bool MapGenerator::findPathX(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x)
{
    if (curr.first == x - 1 && map[curr.second][curr.first] == 'W')
        return true;
    if (map[curr.second][curr.first] == '#' || map[curr.second][curr.first] == 't')
        return false;
    map[curr.second][curr.first] = 't';
    if (curr.first != x - 1)
        if (findPathX(map, {curr.first + 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != y - 1)
        if (findPathX(map, {curr.first, curr.second + 1}, y, x) == 1)
            return true;
    if (curr.first != 0)
        if (findPathX(map, {curr.first - 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != 0)
        if (findPathX(map, {curr.first, curr.second - 1}, y, x) == 1)
            return true;
    return false;
}

bool MapGenerator::findPathY(std::vector<std::string> map, std::pair<int, int> curr, std::size_t y, std::size_t x)
{
    if (curr.second == y - 1 && map[curr.second][curr.first] == 'W')
        return true;
    if (map[curr.second][curr.first] == '#' || map[curr.second][curr.first] == 't')
        return false;
    map[curr.second][curr.first] = 't';
    if (curr.first != x - 1)
        if (findPathY(map, {curr.first + 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != y - 1)
        if (findPathY(map, {curr.first, curr.second + 1}, y, x) == 1)
            return true;
    if (curr.first != 0)
        if (findPathY(map, {curr.first - 1, curr.second}, y, x) == 1)
            return true;
    if (curr.second != 0)
        if (findPathY(map, {curr.first, curr.second - 1}, y, x) == 1)
            return true;
    return false;
}

std::vector<std::string> MapGenerator::generateCornerMap(std::size_t x, std::size_t y)
{
    std::vector<std::string> new_walls;
    std::srand(std::time(0));

    new_walls.resize(x);
    for (size_t i = 0; i != x; i++) {
        new_walls[i].resize(y);
        for (size_t n = 0; n != y; n++) {
            if (std::rand() % 10 <= 6)
                new_walls[i][n] = 'W';
            else
                new_walls[i][n] = '#';
        }
        new_walls[i][y] = '\0';
    }
    new_walls[0][0] = 'W';
    new_walls[0][1] = 'W';
    new_walls[1][0] = 'W';
    if (!findPathY(new_walls, {0, 0}, y, x))
        return (generateCornerMap(x, y));
    if (!findPathX(new_walls, {0, 0}, y, x))
        return (generateCornerMap(x, y));
    new_walls[0][0] = ' ';
    new_walls[0][1] = ' ';
    new_walls[1][0] = ' ';
    return new_walls;
}

std::vector<std::string> MapGenerator::generateProceduralMap(std::size_t nbPlayers, std::size_t x, std::size_t y)
{
    std::vector<std::string> map = generateCornerMap(x / 2 - 1, y / 2 - 1);

    this->_width = x;
    this->_height = y;
    map = copySymmetrical(nbPlayers, map);
    for (auto &m : map) {
        m.insert(m.begin(), '#');
        m.push_back('#');
    }
    map.insert(map.begin(), multiplier_str(std::string("#"), x));
    map.push_back(multiplier_str(std::string("#"), x));
    // map[1][1] = nbPlayers > 0 ? 'P' : 'B';
    // map[x - 2][1] = nbPlayers > 1 ? 'P' : 'B';
    // map[1][y - 2] = nbPlayers > 2 ? 'P' : 'B';
    // for ai testing only
    map[x - 2][y - 3] = nbPlayers > 0 ? 'P' : 'B';
    map[x - 2][1] = nbPlayers > 1 ? 'P' : 'B';
    map[x - 3][y - 2] = nbPlayers > 2 ? 'P' : 'B';
    map[x - 2][y - 2] = nbPlayers > 3 ? 'P' : 'B';
    return map;
}

const size_t MapGenerator::getWidth(void) const
{
    return this->_width;
}

const size_t MapGenerator::getHeight(void) const
{
    return this->_height;
}