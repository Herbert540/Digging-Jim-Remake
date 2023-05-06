#pragma once
#include "jim.hxx"
#include "fall_object.hxx"
#include <ge211.hxx>
#include "game_area.hxx"

class Model
{
public:

    /// Constructs a model by specifying the initial positions of sand, blocks,
    /// rocks, diamonds and jim, through vector and position inputs
    Model(std::vector<Position> wall_set,
          std::vector<Position> rock_set,
          std::vector<Position> diamond_set,
          std::vector<Position> sand_set);

    /// Getting jim for view
    Jim const& jim() const {
        return jim_;
    }

    /// Getting fall object for view
    Fall_Object const& fall_object() const {
        return fall_object_;
    }

    /// Helpers
    int get_index(std::vector<Position> element_set, Position pos);
    bool check(Position f_pos);
    bool check_rocks_diamonds(Position f_pos);
    bool in_set(std::vector<Position> element_set, Position pos);

    /// Falling and Rolling for Model::on_frame(double dt)
    void falling(std::vector<Position>& element_set);
    void rolling(std::vector<Position>& element_set);

    void on_frame(double dt);

    /// Getting key from controller
    void set_key(ge211::Key key) {
        key_pressed_ = key;
    }

    /// Restart game
    void restart_g();

    /// Check if Jim wins the game
    bool win_game() const;

    /// Play again
    void play_again_g();

    /// Moving Board Right
    void move_board_r();

    /// Moving Board Left
    void move_board_l();

    /// Shifting elements right
    void shift_r(std::vector<Position>& element_set);

    /// Shifting elements left
    void shift_l(std::vector<Position>& element_set);

    ///Erasing elements
    void erase_sand();
    void erase_diamond();

    /// Vectors to store positions of walls, rocks, diamonds and sand objects
    /// in their respective sets
    std::vector<Position> wall_set;
    std::vector<Position> rock_set;
    std::vector<Position> diamond_set;
    std::vector<Position> sand_set;

    /// Testing
    // std::vector<Position> wall_set = {{200,200}, {400,400}};
    // std::vector<Position> rock_set = {{40, 40}, {240, 240}};
    // std::vector<Position> diamond_set = {{80,80}, {120, 120}};
    // std::vector<Position> sand_set = {{160,160}, {480,480}};

    /// Keep track of our score, timer and lives
    int score;
    float timer;
    int lives;

    /// Keep track of board shifts
    int track_r;
    int track_l;

    /// door check
    bool door_live = false;

    /// restart check
    bool res = true;

    /// jim dead check
    bool jim_dead = false;

    /// Initial door position
    Position door_p = {600, 640};


    /// Model_test_test
    Jim jim_;


private:
    ge211::Key key_pressed_;

    Fall_Object fall_object_;
    Game_Area game_area_;
};

