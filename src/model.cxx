#include "model.hxx"
#include <iostream>
#include <ge211.hxx>
#include <algorithm>
using namespace std;

/// .cxx implementation of our constructor
Model::Model(
        std::vector<Position> wall_set,
        std::vector<Position> rock_set,
        std::vector<Position> diamond_set,
        std::vector<Position> sand_set)
        :wall_set(wall_set),
         rock_set(rock_set),
         diamond_set(diamond_set),
         sand_set(sand_set)
{
    score = 0;
    timer = 60;
    lives = 2;

    track_l = 0;
    track_r = 10;
}


/// Get index of given position in element set
int
Model::get_index(std::vector<Position> element_set, Position pos){
    int ind = 0;
    for (Position el : element_set){
        if (pos == el){
            return ind;
        }
        ind++;
    }
    return ind;
}


/// Helper
/// Check if given position is a member of element set
bool
Model::in_set(std::vector<Position> element_set, Position pos)
{
    if (std::find(element_set.begin(), element_set.end(), pos)
        != element_set.end()) {
        return true;
    } else {
        return false;
    }
}


/// Helper
/// Check if given position is a member of wall_set, rock_set, diamond_set and
/// sand_set
/// Helpers: in_set(std::vector<Position> element_set, Position pos)
bool
Model::check(Position f_pos)
{
    bool walls = in_set(wall_set,f_pos);
    bool rocks = in_set(rock_set,f_pos);
    bool diamonds = in_set(diamond_set,f_pos);
    bool sands = in_set(sand_set,f_pos);

    return (walls||rocks||diamonds||sands);
}


/// Helper
/// Check if given position is a member of rock_set and diamond_set only
/// Helpers: in_set(std::vector<Position> element_set, Position pos)
bool
Model::check_rocks_diamonds(Position f_pos)
{
    bool rocks = in_set(rock_set,f_pos);
    bool diamonds = in_set(diamond_set,f_pos);

    return (rocks||diamonds);
}

/// for Model::on_frame(double dt)
/// Make rocks and diamonds fall whenever there is space below
/// Helpers: check(Position f_pos)
void
Model::falling(std::vector<Position>& element_set)
{
    for(Position& rock: element_set){

        Position fall_pos = {rock.x,rock.y+40};
        Position ant_jim_pos = {rock.x,rock.y+80};
        /// If space or Jim not under: fall
        if(!check(fall_pos) && !(jim_.position()==fall_pos)){
            // rock = {rock.x,rock.y+10};
            rock = fall_pos;
            /// If next position below while fall is jim_pos, Jim dies
            if (ant_jim_pos == jim_.position()){
                jim_dead = true;
            }

        }
    }
}


/// for Model::on_frame(double dt)
/// Make rocks and diamonds roll whenever there is space right-down
/// Helpers: check_rocks_diamonds(Position f_pos)
void
Model::rolling(std::vector<Position>& element_set)
{
    for(Position& rock: element_set){
        Position jim_rock_support_r = {rock.x+40,rock.y};
        Position jim_rock_support_l = {rock.x-40,rock.y};

        Position roll_pos_r = {rock.x+40,rock.y+40};
        Position ant_jim_pos_r = {rock.x+40,rock.y+80};

        Position roll_pos_l = {rock.x-40,rock.y+40};
        Position ant_jim_pos_l = {rock.x-40,rock.y+80};

        Position rock_diamond_u = {rock.x,rock.y+40};

        /// If space and jim not supporting at right: roll
        if(!check(roll_pos_r) && !check(jim_rock_support_r) && !(jim_.position()
                                                                 ==roll_pos_r) && !(jim_.position() ==jim_rock_support_r) &&
           (check_rocks_diamonds(rock_diamond_u))){
            // if (!(rock == jim_rock_support_r)){
            //     rock = {rock.x+5,rock.y};
            // } else{
            //     rock = {rock.x+40,rock.y+5};
            // }
            rock = jim_rock_support_r;
            rock = roll_pos_r;
            /// If rolls on Jim: Jim dies
            if (ant_jim_pos_r == jim_.position()){
                jim_dead = true;
            }
        }

        /// If space and jim not supporting at left: roll
        if(!check(roll_pos_l) && !check(jim_rock_support_l) && !(jim_.position()
                                                                 ==roll_pos_l) && !(jim_.position() ==jim_rock_support_l) &&
           (check_rocks_diamonds(rock_diamond_u))){
            // if (!(rock == jim_rock_support_l)){
            //     rock = {rock.x-5,rock.y};
            // } else{
            //     rock = {rock.x-40,rock.y+5};
            // }
            rock = jim_rock_support_l;
            rock = roll_pos_l;
            /// If rolls on Jim: Jim dies
            if (ant_jim_pos_l == jim_.position()){
                jim_dead = true;
            }
        }
    }
}


/// Shifting elements right
void
Model::shift_r(std::vector<Position>& element_set)
{
    for (Position& element: element_set) {
        element = {element.x-40,element.y};
    }
}


/// Shifting elements left
void
Model::shift_l(std::vector<Position>& element_set)
{
    for (Position& element: element_set) {
        element = {element.x+40,element.y};
    }

}


/// Moving Board Right
/// Shifting all elements right
void
Model::move_board_r()
{
    if ((jim_.position().x == 520) && (track_r != 0)) {


        jim_.move_l();
        shift_r(wall_set);
        shift_r(sand_set);
        shift_r(rock_set);
        shift_r(diamond_set);
        track_r -= 1;
        track_l += 1;

        door_p = {door_p.x-40,door_p.y};
    }
}


/// Moving Board Left
/// Shifting all elements left
void
Model::move_board_l()
{
    if ((jim_.position().x == 440)&& (track_l != 0)) {

        jim_.move_r();
        shift_l(wall_set);
        shift_l(sand_set);
        shift_l(rock_set);
        shift_l(diamond_set);
        track_l -= 1;
        track_r += 1;

        door_p = {door_p.x+40,door_p.y};
    }
}


/// Erasing sand
/// Helpers: Model::get_index(std::vector<Position> element_set, Position pos)
void
Model::erase_sand()
{
    int ind = get_index(sand_set, jim_.position());
    sand_set.erase(sand_set.begin() + ind);
}


/// Erasing diamond
/// Helpers: Model::get_index(std::vector<Position> element_set, Position pos)

void
Model::erase_diamond()
{
    int ind = get_index(diamond_set, jim_.position());
    diamond_set.erase(diamond_set.begin() + ind);
    score++;
}


/// Restarting Game
void
Model::restart_g()
{
    game_area_.populate_map();
    wall_set = game_area_.i_wall_set();
    sand_set = game_area_.i_sand_set();
    diamond_set = game_area_.i_diamond_set();
    rock_set = game_area_.i_rock_set();
    jim_.reset();
    door_live = false;
    jim_dead = false;
    score = 0;
    timer = 60;
    track_l = 0;
    track_r = 10;
    door_p = {600, 640};
    lives--;
    if(lives == 0){
        res = false;
    }
}


/// Play Game Again after GameOver
void
Model::play_again_g()
{
    game_area_.populate_map();
    wall_set = game_area_.i_wall_set();
    sand_set = game_area_.i_sand_set();
    diamond_set = game_area_.i_diamond_set();
    rock_set = game_area_.i_rock_set();
    jim_.reset();
    door_live = false;
    jim_dead = false;
    score = 0;
    timer = 60;
    track_l = 0;
    track_r = 10;
    door_p = {600, 640};
    lives = 2;
    res = true;
}


/// Winning Game
bool
Model::win_game() const
{
    return ((jim_.position() == door_p) && door_live);

}


/// on_frame: where all the action occurs
void Model::on_frame(double dt) {

    /// Restart
    if (key_pressed_ == ge211::Key::code('r')){
        if(res){
            restart_g();
        }
    }

    /// Play Again
    if (key_pressed_ == ge211::Key::code('p')){
        play_again_g();
    }

    /// Timer Clock
    timer = timer - 0.01 ;
    if (timer <= 0){
        timer = 0;
        jim_dead = true;
        return;
    }

    else {
        if (!win_game() && !jim_dead) {


            if (score >= 5) {
                door_live = true;
            }

            falling(rock_set);
            falling(diamond_set);
            rolling(rock_set);
            rolling(diamond_set);

            /// left arrow key
            if (key_pressed_ == ge211::Key::left()) {
                /// reusing hit_wall for rock
                /// hits_rock from below
                if (jim_.hits_wall_l(rock_set)) {
                    if (check({jim_.position().x - 80, jim_.position().y})) {

                    } else {
                        jim_.move_l();
                        fall_object_.r_move_l(rock_set, jim_.position());
                        move_board_l();
                    }
                }
                    /// hits_wall from left
                else if (!jim_.hits_wall_l(wall_set) && !jim_.hits_door_l
                                                                     (door_p,door_live)) {
                    jim_.move_l();
                    /// hits_sand from left
                    if (jim_.hits_sand(sand_set)) {
                        erase_sand();
                    }
                    /// hits_diamond from left
                    if (jim_.hits_diamond(diamond_set)) {
                        erase_diamond();
                    }
                    move_board_l();
                }
            }

            /// right arrow key
            if (key_pressed_ == ge211::Key::right()) {
                /// reusing hit_wall for rock
                /// hits_rock from below
                if (jim_.hits_wall_r(rock_set)) {
                    if (check({jim_.position().x + 80, jim_.position().y})) {

                    } else {
                        jim_.move_r();
                        fall_object_.r_move_r(rock_set, jim_.position());
                        move_board_r();
                    }
                }
                    /// hits_wall from right
                else if (!jim_.hits_wall_r(wall_set) && !jim_.hits_door_r
                                                                     (door_p,door_live)) {
                    jim_.move_r();
                    /// hits_sand from right
                    if (jim_.hits_sand(sand_set)) {
                        erase_sand();
                    }
                    /// hits_diamond from right
                    if (jim_.hits_diamond(diamond_set)) {
                        erase_diamond();
                    }
                    move_board_r();
                }
            }

            /// up arrow key
            if (key_pressed_ == ge211::Key::up()) {
                /// hits_rock from top
                if (jim_.hits_rock_u(rock_set)) {
                    jim_.stop_v();
                } else if (!jim_.hits_wall_u(wall_set) && !jim_.hits_door_u
                                                                       (door_p,door_live)) {
                    /// hits_wall from top
                    jim_.move_u();
                    /// hits_sand from top
                    if (jim_.hits_sand(sand_set)) {
                        erase_sand();
                    }
                    /// hits_diamond from top
                    if (jim_.hits_diamond(diamond_set)) {
                        erase_diamond();
                    }
                }
            }

            /// down arrow key
            if (key_pressed_ == ge211::Key::down()) {
                /// reusing hit_wall for rock
                /// hits_rock from below
                if (jim_.hits_wall_d(rock_set)) {
                    jim_.stop_v();
                }
                    /// hits_wall from below
                else if (!jim_.hits_wall_d(wall_set) && !jim_.hits_door_d
                                                                     (door_p,door_live)) {
                    jim_.move_d();
                    /// hits_sand from below
                    if (jim_.hits_sand(sand_set)) {
                        erase_sand();
                    }
                    /// hits_diamond from below
                    if (jim_.hits_diamond(diamond_set)) {
                        erase_diamond();
                    }
                }
            }

            key_pressed_ = ge211::Key::code('y');

        } else {
            timer = timer + 0.01;
        }
    }
}



