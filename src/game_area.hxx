#include <ge211.hxx>
#include <iostream>
// #pragma once

using Position = ge211::Posn<int>;

class Game_Area
{
public:

    /// Get wall_positions
    std::vector<Position> i_wall_set() const {
        return wall_positions;
    }
    /// Get sand_positions
    std::vector<Position> i_sand_set() const {
        return sand_positions;
    }
    /// Get rock_positions
    std::vector<Position> i_rock_set() const {
        return rock_postions;
    }
    /// Get diamond_positions
    std::vector<Position> i_diamond_set() const {
        return diamond_positions;
    }

    /// Header for Game_Area::populate_map()
    void populate_map();




private:
    /// Vectors to store positions of walls, rocks, diamonds and sand objects
    /// in their respective sets
    std::vector<Position> wall_positions;
    std::vector<Position> sand_positions;
    std::vector<Position> rock_postions;
    std::vector<Position> diamond_positions;

    /// Header for Game_Area::create_map()
    void create_map();
};
