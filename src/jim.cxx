#include "jim.hxx"
#include <ge211.hxx>
// #pragma once

/// Move right
void
Jim::move_r(){
    j_pos.x += 40;
}

/// Move left
void
Jim::move_l(){
    j_pos.x -= 40;
}

/// Move up
void
Jim::move_u(){
    j_pos.y -= 40;
}

/// Move down
void
Jim::move_d(){
    j_pos.y += 40;
}

/// Stop vertical
void
Jim::stop_v(){
    j_pos.y += 0;
}

/// Reset
void
Jim::reset()
{
    j_pos.x = 40;
    j_pos.y = 40;
}



/// Wall Hitting
/// Hitting wall from the right
bool
Jim::hits_wall_r(std::vector<Position>& wall_set) const{
    for (Position wall: wall_set) {
        if((j_pos.x+20 == wall.x-20) && (j_pos.y == wall.y)){
            return true;
        }
    }
    return false;
}


/// Hitting wall from the left
bool
Jim::hits_wall_l(std::vector<Position>& wall_set) const{
    for (Position wall: wall_set) {
        if((j_pos.x-20 == wall.x+20) && (j_pos.y == wall.y)){
            return true;
        }
    }
    return false;
}


/// Hitting wall from the top
bool
Jim::hits_wall_u(std::vector<Position>& wall_set) const{
    for (Position wall: wall_set) {
        if((j_pos.x == wall.x) && (j_pos.y-20 == wall.y+20)){
            return true;
        }
    }
    return false;
}


/// Hitting wall from the bottom
bool
Jim::hits_wall_d(std::vector<Position>& wall_set) const{
    for (Position wall: wall_set) {
        if((j_pos.x == wall.x) && (j_pos.y+20 == wall.y-20)){
            return true;
        }
    }
    return false;
}


/// Rock Hitting
/// Hitting rock from the top
bool
Jim::hits_rock_u(std::vector<Position>& rock_set) const{
    for (Position rock: rock_set) {
        if((j_pos.x == rock.x) && (j_pos.y-20 == rock.y+20)){
            return true;
        }
    }
    return false;
}


/// Sand Intersection
/// True if positions are equal
bool
Jim::hits_sand(std::vector<Position>& sand_set) const {
    for (Position sand: sand_set) {
        if(j_pos == sand){
            return true;
        }
    }
    return false;
}


/// Diamond Intersection
/// True if positions are equal
bool
Jim::hits_diamond(std::vector<Position>& diamond_set) const {
    for (Position diamond: diamond_set) {
        if(j_pos == diamond){
            return true;
        }
    }
    return false;
}


/// Hitting door from the top
bool
Jim::hits_door_u(Position door_pos, bool door_live) const
{
    if(!door_live && ((j_pos.x== door_pos.x) && (j_pos.y-20 == door_pos.y+20))){
        return true;
    }
    return false;
}


/// Hitting door from the bottom
bool
Jim::hits_door_d(Position door_pos, bool door_live) const
{
    if(!door_live && ((j_pos.x== door_pos.x) && (j_pos.y+20 == door_pos.y-20))){
        return true;
    }
    return false;
}


/// Hitting door from right
bool
Jim::hits_door_r(Position door_pos, bool door_live) const
{
    if(!door_live && ((j_pos.x+20== door_pos.x-20) && (j_pos.y == door_pos.y))){
        return true;
    }
    return false;
}


/// Hitting door from left
bool
Jim::hits_door_l(Position door_pos, bool door_live) const
{
    if(!door_live && ((j_pos.x-20== door_pos.x+20) && (j_pos.y == door_pos.y))){
        return true;
    }
    return false;
}

