//
// Created by Herbert Botwe on 11/27/22.
//

#include "fall_object.hxx"
#include <ge211.hxx>
// #pragma once

/// for Model::on_frame(double dt)
/// Move rock right
void
Fall_Object::r_move_r(std::vector<Position>& rock_set, Position jim_pos) const
{
    for(Position& rock: rock_set){
        if(rock == jim_pos){
            rock = {jim_pos.x+40, jim_pos.y};
        }
    }
}


/// for Model::on_frame(double dt)
/// Move rock left
void
Fall_Object::r_move_l(std::vector<Position>& rock_set, Position jim_pos) const
{
    for(Position& rock: rock_set){
        if(rock == jim_pos){
            rock = {jim_pos.x-40, jim_pos.y};
        }
    }
}

