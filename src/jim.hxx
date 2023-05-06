#include <ge211.hxx>
#include <iostream>
// #pragma once

using Position = ge211::Posn<int>;

class Jim
{
public:
    Position const position() const {
        return j_pos;
    }

    /// Headers for move_r, move_l, move_u, move_d in jim.cxx
    void move_r();
    void move_l();
    void move_u();
    void move_d();

    /// Header for stop_v in jim.cxx
    void stop_v();

    /// Header for reset
    void reset();

    /// Headers for hits_wall_r, hits_wall_l, hits_wall_u, hits_wall_d in jim
    /// .cxx
    bool hits_wall_r(std::vector<Position>& wall_set) const;
    bool hits_wall_l(std::vector<Position>& wall_set) const;
    bool hits_wall_u(std::vector<Position>& wall_set) const;
    bool hits_wall_d(std::vector<Position>& wall_set) const;

    /// Headers for hits_rock_u, hits_wall_d jim.cxx
    bool hits_rock_u(std::vector<Position>& rock_set) const;


    /// Header for hits_sand and destroy_sand
    bool hits_sand(std::vector<Position>& sand_set) const;
    bool hits_diamond(std::vector<Position>& sand_set) const;
    //void destroy_sand(std::vector<Position>& sand_set) const;

    /// Door hitting
    bool hits_door_u(Position door_pos, bool door_live) const;
    bool hits_door_d(Position door_pos, bool door_live) const;
    bool hits_door_r(Position door_pos, bool door_live) const;
    bool hits_door_l(Position door_pos, bool door_live) const;

    Position j_pos{40, 40};

private:

};
