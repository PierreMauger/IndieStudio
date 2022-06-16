/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** main
*/

#include "includes.hpp"
#include "Neo.hpp"

using namespace neo;

int main(int argc, char **argv)
{
    Neo neo;

    std::srand(std::time(0));
    neo.run();
    return 0;
}
