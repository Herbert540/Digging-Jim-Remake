#include <ge211.hxx>
#include <iostream>
// #pragma once

using Position = ge211::Posn<int>;

class Fall_Object
{
public:

    /// Headers for r_move_r, r_move_l in fall_object.cxx
    void r_move_r(std::vector<Position>& rock_set, Position jim_pos) const;
    void r_move_l(std::vector<Position>& rock_set, Position jim_pos) const;


};
