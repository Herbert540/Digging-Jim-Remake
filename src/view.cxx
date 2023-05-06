#include "view.hxx"

/// Sprite colors
static ge211::Color const jim_c {255, 255, 51};
static ge211::Color const wall_c {174, 71, 0};
static ge211::Color const sand_c {205, 92, 92};
static ge211::Color const diamond_c {166, 231, 255};
static ge211::Color const rock_c {165, 156, 148};
static ge211::Color const c_door_c {255, 0, 0};
static ge211::Color const o_door_c {0, 255, 0};


// View::View(Model const& model)
//         : model_(model),
//           jim(20,jim_c),
//           wall({40,40},wall_c),
//           sand({40,40},sand_c),
//           diamond(20, diamond_c),
//           rock(20, rock_c),
//           c_door({40,40}, c_door_c),
//           o_door({40,40}, o_door_c)
// { }

View::View(Model const& model)
        : model_(model),
        // jim(20,jim_c),
          jim("jim.png"),
          wall("wall.png"),
          sand("sand.png"),
          diamond("diamond.png"),
          rock("rock.jpg"),
          c_door("closeddoor.jpg"),
          o_door("opendoor.png")
{ }


/// Drawing GameArea
void
View::draw(ge211::Sprite_set& set)
{

    /// To display the score
    ge211::Text_sprite::Builder score_dis(sans30);
    score_dis << "Score: " << std::to_string(model_.score) << "/5";
    score_s.reconfigure(score_dis);
    set.add_sprite(score_s, {160, 0}, 40);

    /// To display the lives
    ge211::Text_sprite::Builder lives_dis(sans30);
    lives_dis << "Extra Lives: " << std::to_string(model_.lives) ;
    lives_s.reconfigure(lives_dis);
    set.add_sprite(lives_s, {480, 0}, 40);

    /// To display the timer
    ge211::Text_sprite::Builder time_dis(sans30);
    time_dis << "Timer: " << std::to_string(int(round(model_.timer)));
    timer_s.reconfigure(time_dis);
    set.add_sprite(timer_s, {320, 0}, 40);

    /// Checking if it's game over then draw the game over sprite
    if (model_.timer <= 0){

        ge211::Text_sprite::Builder game_o_dis(sans30);
        if (model_.lives != 0){game_o_dis<< "Time ran out! Try again!"
                                            "('r'-key)";}
        else{game_o_dis<< "Time ran out! Game Over! Play Again('p'-key) ";}
        game_o_s.reconfigure(game_o_dis);
        set.add_sprite(game_o_s, {320, 320}, 40);
    }

    /// If win game print winning message
    if (model_.win_game()){

        ge211::Text_sprite::Builder game_w_dis(sans30);
        game_w_dis<< "Well done! You won! Play Again('p'-key) ";
        game_w_s.reconfigure(game_w_dis);
        set.add_sprite(game_w_s, {320, 320}, 40);
    }

    /// If jim dies we display jim_dead message
    if (model_.jim_dead){

        ge211::Text_sprite::Builder jim_d_dis(sans30);
        if (model_.lives != 0){jim_d_dis<< "Jim died! Restart('r'-key)! ";}
        else{jim_d_dis<< "Jim died! Game Over! Play Again('p'-key) ";}
        jim_dead_s.reconfigure(jim_d_dis);
        set.add_sprite(jim_dead_s, {320, 320}, 40);
    }

    /// Draw walls
    for (Position wall_p: model_.wall_set) {
        set.add_sprite(wall,wall_p);
    }

    /// Draw sand
    for (Position sand_p: model_.sand_set) {
        set.add_sprite(sand,sand_p);
    }

    /// Draw rocks
    for (Position rock_p: model_.rock_set) {
        set.add_sprite(rock, rock_p);
    }

    /// Draw diamonds
    for (Position diamond_p: model_.diamond_set) {
        set.add_sprite(diamond, diamond_p);
    }

    /// Draw Jim
    set.add_sprite(jim,model_.jim().position());


    ge211::Transform my_transform =
            ge211::Transform{}
                    .scale(0.5);

    /// Draw closed door
    set.add_sprite(c_door, model_.door_p, 3);

    /// If Door is door_live, draw open door
    if (model_.door_live){
        set.add_sprite(o_door, model_.door_p, 5, my_transform);
    }
}


/// Initial window dimensions for view
ge211::Dims<int>
View::initial_window_dimensions() const
{
    return {1000,760};
}
