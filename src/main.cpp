/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** main
*/

#include "includes.hpp"
#include "Neo.hpp"

#define BOMB_CD 0.0
#define BOMB_TIMER 3.0
#define BOMB_ROWS 2

typedef struct {
    Vector2 pos;
    double timer;
} bomb_t;

typedef struct {
    Vector2 pos;
    double timer;
    bool isDead;
} player_t;

std::vector<std::string> map{
    "###########",
    "#1 WWWWWWW#",
    "#  WWWWWWW#",
    "#WWWWWWWWW#",
    "#WWWWWWWWW#",
    "#WWWWWWWWW#",
    "#WWWWWWWWW#",
    "#WWWWWWWWW#",
    "#WWWWWWW  #",
    "#WWWWWWW 2#",
    "###########"
};

const float screenWidth = 1280;
const float screenHeight = 720;
const Vector2 recSize = { screenWidth / map[0].size(), screenHeight / map.size() };

void checkKey(std::vector<player_t>& players, std::vector<bomb_t>& bombs)
{
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].isDead)
            continue;
        if (IsKeyPressed(!i ? KEY_W : KEY_UP) && map[players[i].pos.x - 1][players[i].pos.y] != '#'
            && map[players[i].pos.x - 1][players[i].pos.y] != 'W')
            players[i].pos.x--;
        if (IsKeyPressed(!i ? KEY_A : KEY_LEFT) && map[players[i].pos.x][players[i].pos.y - 1] != '#'
            && map[players[i].pos.x][players[i].pos.y - 1] != 'W')
            players[i].pos.y--;
        if (IsKeyPressed(!i ? KEY_S : KEY_DOWN) && map[players[i].pos.x + 1][players[i].pos.y] != '#'
            && map[players[i].pos.x + 1][players[i].pos.y] != 'W')
            players[i].pos.x++;
        if (IsKeyPressed(!i ? KEY_D : KEY_RIGHT) && map[players[i].pos.x][players[i].pos.y + 1] != '#'
            && map[players[i].pos.x][players[i].pos.y + 1] != 'W')
            players[i].pos.y++;
        if (IsKeyPressed(!i ? KEY_SPACE : KEY_ENTER) && GetTime() - players[i].timer > BOMB_CD) {
            bombs.push_back(CAST(bomb_t, CAST(Vector2, players[i].pos.x, players[i].pos.y), GetTime()));
            players[i].timer = GetTime();
        }
    }
}

void blowUp(size_t k, std::vector<player_t> &players, std::vector<bomb_t> &bombs)
{
    for (size_t i = 0; i <= BOMB_ROWS; i++) {
        if (bombs[k].pos.x - i >= 0) {
            if (map[bombs[k].pos.x - i][bombs[k].pos.y] == 'W')
                map[bombs[k].pos.x - i][bombs[k].pos.y] = ' ';
            else if (map[bombs[k].pos.x][bombs[k].pos.y + i] != '#')
                for (size_t j = 0; j < players.size(); j++)
                    if (bombs[k].pos.x - i == players[j].pos.x && bombs[k].pos.y == players[j].pos.y)
                        players[j].isDead = true;
        }
        if (bombs[k].pos.y - i >= 0) {
            if (map[bombs[k].pos.x][bombs[k].pos.y - i] == 'W')
                map[bombs[k].pos.x][bombs[k].pos.y - i] = ' ';
            else if (map[bombs[k].pos.x][bombs[k].pos.y + i] != '#')
                for (size_t j = 0; j < players.size(); j++)
                    if (bombs[k].pos.x == players[j].pos.x && bombs[k].pos.y - 1 == players[j].pos.y)
                        players[j].isDead = true;
        }
        if (bombs[k].pos.x + i < map.size()) {
            if (map[bombs[k].pos.x + i][bombs[k].pos.y] == 'W')
                map[bombs[k].pos.x + i][bombs[k].pos.y] = ' ';
            else if (map[bombs[k].pos.x][bombs[k].pos.y + i] != '#')
                for (size_t j = 0; j < players.size(); j++)
                    if (bombs[k].pos.x + i == players[j].pos.x && bombs[k].pos.y == players[j].pos.y)
                        players[j].isDead = true;
        }
        if (bombs[k].pos.y + i < map[0].size()) {
            if (map[bombs[k].pos.x][bombs[k].pos.y + i] == 'W')
                map[bombs[k].pos.x][bombs[k].pos.y + i] = ' ';
            else if (map[bombs[k].pos.x][bombs[k].pos.y + i] != '#')
                for (size_t j = 0; j < players.size(); j++)
                    if (bombs[k].pos.x == players[j].pos.x && bombs[k].pos.y + i == players[j].pos.y)
                        players[j].isDead = true;
        }
    }
}

void checkEntities(size_t i, size_t j, Vector2 pos, std::vector<player_t> &players, std::vector<bomb_t> &bombs)
{
    for (size_t k = 0; k < bombs.size(); k++) {
        if (i == bombs[k].pos.x && j == bombs[k].pos.y)
            DrawRectangleV(pos, recSize, YELLOW);
        if (GetTime() - bombs[k].timer > BOMB_TIMER) {
            blowUp(k, players, bombs);
            bombs.erase(bombs.begin() + k);
        }
    }
    for (size_t k = 0; k < players.size(); k++)
        if (!players[k].isDead && i == players[k].pos.x && j == players[k].pos.y)
            DrawRectangleV(pos, recSize, !k ? RED : BLUE);
}

void getPlayers(std::vector<player_t> &players)
{
    for (size_t i = 0, id = '1'; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == id) {
                players.push_back(CAST(player_t, CAST(Vector2, (float)i, (float)j), -BOMB_CD, false));
                id++;
                map[i][j] = ' ';
            }
        }
    }
}

void draw(std::vector<player_t> &players, std::vector<bomb_t> &bombs)
{
    Vector2 pos = { 0, 0 };
    
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            checkEntities(i, j, pos, players, bombs);
            if (map[i][j] != ' ')
                DrawRectangleV(pos, recSize, map[i][j] == '#' ? BLACK : BROWN);
            pos.x += screenWidth / map[0].size();
        }
        pos.x = 0;
        pos.y += screenHeight / map.size();
    }
}

bool checkEnd(std::vector<player_t>& players)
{
    size_t nbDeads = 0;

    for (size_t i = 0; i < players.size(); i++)
        if (players[i].isDead)
            nbDeads++;
    if (nbDeads >= players.size() - 1)
        return true;
    return false;
}

void test()
{
    std::vector<player_t> players;

    InitWindow(screenWidth, screenHeight, "test");
    getPlayers(players);
    SetTargetFPS(60);
    for (std::vector<bomb_t> bombs; !WindowShouldClose();) {
        checkKey(players, bombs);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw(players, bombs);
        EndDrawing();
        if (checkEnd(players))
            break;
    }
    CloseWindow();
}

int main(int argc, char **argv)
{
    neo::Neo neo;

    neo.run();
    //test();
    return 0;
}
