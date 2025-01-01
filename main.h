#pragma once

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <limits>

struct Shot_coord
{

    int64_t x;
    int64_t y;

    Shot_coord(int64_t shot_x, int64_t shot_y) 
        : x(shot_x), y(shot_y){}

};

struct Parsing
{

    struct Params
    {

        std::string ping = "ping";
        std::string exit = "exit";
        std::string start = "start";
        std::string stop = "stop";

        std::string create = "create";
        std::string get = "get";

        std::string set = "set";
    };

    std::string dump_path; 
    std::string load_path; 

    int64_t width = 0;
    int64_t height = 0;
    std::string type_ship;
    int64_t count_ship_1 = 0;
    int64_t count_ship_2 = 0;
    int64_t count_ship_3 = 0;
    int64_t count_ship_4 = 0;

    std::string mode;
    std::string strategy = "custom";
    std::string result;

    int64_t x_for_ordered = 0;
    int64_t y_for_ordered = 0;

    std::vector<Shot_coord> last_hits;
    std::vector<Shot_coord> hits;

    int64_t last_x_hit;
    int64_t last_y_hit;
    bool not_random_shot = false;

    char orient_hit_ship = 's';

    int64_t counter_kill_ship_comp = 0;
    int64_t counter_kill_ship_opp = 0;

    bool f_start = false;
    bool f_exit = false;
};

struct Ship
{
    int16_t len_ship = 0;
    int64_t x;
    int64_t y;
    char orient;
    std::vector<Shot_coord> Coordinates;

    int16_t count_shot = len_ship;

    Ship(int len, int64_t x_start, int64_t y_start, char orientation)
        : len_ship(len), x(x_start), y(y_start), orient(orientation) {}

    void setCoordinates()
    {
        Coordinates.clear();

        for (int i = 0; i < len_ship; ++i)
        {
            if (orient == 'v')
            {
                Coordinates.push_back(Shot_coord(x, y + i));
            }
            else if (orient == 'h')
            {
                Coordinates.push_back(Shot_coord(x + i, y));
            }
        }
    }
};

std::vector<Ship> ships;

std::vector<Shot_coord> history_shot;

void Game();

void Placement(int64_t width, int64_t height, int64_t count_ship_1, int64_t count_ship_2, int64_t count_ship_3, int64_t count_ship_4);

void Shot(int64_t shot_x, int64_t shot_y, std::vector<Ship> &ships, int64_t &counter_kill_ship_comp, int64_t count_ship, bool &flag);

void Ordered_shot(int64_t width, int64_t height, int64_t &x_for_ordered, int64_t &y_for_ordered);

void Random_comp_shot(int64_t width, int64_t height, std::vector<Shot_coord> &history_shot);

void NOT_Random_comp_shot(int64_t width, int64_t height, int64_t last_x_hit, int64_t last_y_hit, std::vector<Shot_coord> &history_shot);

void NOT_Random_comp_shot_with_orient(int64_t width, int64_t height, int64_t last_x_hit, int64_t last_y_hit, std::vector<Shot_coord> &history_shot, char orient);

void Merge_vectors(std::vector<Shot_coord> &history_shot, std::vector<Shot_coord> &hits);