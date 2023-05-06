#pragma once

#include "model.hxx"

class View
{
public:
    /// View Constructor
    explicit View(Model const& model);

    /// Returns the size of the game window
    ge211::Dims<int> initial_window_dimensions() const;

    /// Renders all the game entities to the screen.
    void draw(ge211::Sprite_set& set);

private:
    /// Reference to the model.
    Model const& model_;

    /// Jim, wall, sand, diamond and rock image sprites
    /// Initialized in constructor
    ge211::sprites::Image_sprite jim;
    ge211::sprites::Image_sprite wall;
    ge211::sprites::Image_sprite sand;
    ge211::sprites::Image_sprite diamond;
    ge211::sprites::Image_sprite rock;

    /// open door and closed door sprites
    ge211::sprites::Image_sprite c_door;
    ge211::sprites::Image_sprite o_door;

    // /// Jim, wall, sand, diamond and rock sprites
    // /// Initialized in constructor
    // ge211::Circle_sprite const jim;
    // ge211::Rectangle_sprite const wall;
    // ge211::Rectangle_sprite const sand;
    // ge211::Circle_sprite const diamond;
    // ge211::Circle_sprite const rock;
    //
    // /// open door and closed door sprites
    // ge211::Rectangle_sprite const c_door;
    // ge211::Rectangle_sprite const o_door;

    /// Text sprites
    ge211::Font sans30{"sans.ttf", 30};
    ge211::Text_sprite score_s;
    ge211::Text_sprite timer_s;
    ge211::Text_sprite game_o_s;
    ge211::Text_sprite game_w_s;
    ge211::Text_sprite jim_dead_s;
    ge211::Text_sprite lives_s;




};

