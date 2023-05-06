#include "model.hxx"
#include <catch.hxx>

TEST_CASE("preliminary_test")
{
    Game_Area game_area_;
    game_area_.populate_map();


    Model model1(game_area_.i_wall_set(),
            game_area_.i_rock_set(),
            game_area_.i_diamond_set(),
            game_area_.i_sand_set());

    /// score, timer, lives
    CHECK(model1.score == 0);
    CHECK(model1.timer == 60);
    CHECK(model1.lives == 2);

    /// changing
    model1.score = 5;
    /// Door live
    CHECK(!model1.door_live);
    CHECK(model1.score == 5);
    model1.on_frame(30);
    CHECK(model1.door_live);
    /// changing timer
    model1.timer = 0;
    CHECK(!model1.jim_dead);
    model1.on_frame(30);
    CHECK(model1.jim_dead);
    /// changing lives
    model1.jim_dead = false;
    model1.timer = 60;
    model1.lives = 1;
    CHECK(!model1.jim_dead);
    model1.lives = 0;




    Position jim_pos = {40,40};

    /// Player position
    CHECK(model1.jim().j_pos == jim_pos);

}


//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//

TEST_CASE("jim dies")
{
    std::vector<Position> wall_set = {};
    std::vector<Position> sand_set = {{200,120}};
    std::vector<Position> rock_set = { {80,40}, {200, 40},
                                                {200, 80}};
    std::vector<Position> diamond_set = {{120,40}};

    /// on timer == 0
    Model model2(wall_set, rock_set, diamond_set, sand_set);
    model2.timer = 0;
    model2.on_frame(30);
    CHECK(model2.jim_dead);

    /// when jim intersects rock
    model2.set_key(ge211::Key::right());
    model2.on_frame(30);
    CHECK(model2.jim_dead);

    /// when jim intersects rock
    model2.jim_dead = false;
    model2.set_key(ge211::Key::right());
    model2.on_frame(30);
    CHECK(model2.jim_dead);

    /// when rock or diamond falls on Jim
    model2.jim_dead = false;
    /// beneath
    model2.jim_.j_pos = {80,80};
    CHECK(!model2.jim_dead);

    /// space fall
    model2.set_key(ge211::Key::down());
    model2.on_frame(30);
    CHECK(model2.jim_dead);

    /// rock roll
    model2.jim_dead = false;
    model2.jim_.j_pos = {160,120};
    model2.on_frame(30);
    CHECK(model2.jim_dead);
}


TEST_CASE("jim_motion")
{
    std::vector<Position> wall_set = {};
    std::vector<Position> sand_set = {};
    std::vector<Position> rock_set = {};
    std::vector<Position> diamond_set = {};

    Model model3(wall_set, rock_set, diamond_set, sand_set);

    ///right
    model3.jim_.j_pos = {40,40};
    model3.jim_.move_r();
    Position jim_pos_r = {80,40};
    CHECK(model3.jim().j_pos == jim_pos_r);

    ///left
    model3.jim_.j_pos = {40,40};
    model3.jim_.move_l();
    Position jim_pos_l = {0,40};
    CHECK(model3.jim().j_pos == jim_pos_l);

    ///up
    model3.jim_.j_pos = {40,40};
    model3.jim_.move_u();
    Position jim_pos_u = {40,0};
    CHECK(model3.jim().j_pos == jim_pos_u);

    ///down
    model3.jim_.j_pos = {40,40};
    model3.jim_.move_d();
    Position jim_pos_d = {40,80};
    CHECK(model3.jim().j_pos == jim_pos_d);

    ///stop
    model3.jim_.j_pos = {40,40};
    model3.jim_.stop_v();
    Position jim_pos_s = {40,40};
    CHECK(model3.jim().j_pos == jim_pos_s);

    // new model with walls
    std::vector<Position> wall_set2 = {{80,40}};
    Model model4(wall_set2, rock_set, diamond_set, sand_set);

    // right movement on a wall is impeded
    model4.jim_.j_pos = {40,40};
    model4.jim_.move_r();
    Position jim_pos = {40,40};
    CHECK(model3.jim().j_pos == jim_pos);

}


TEST_CASE("sand_destroy")
{
    std::vector<Position> wall_set = {};
    std::vector<Position>
            sand_set =
            {{80,  40},
             {120, 40},
             {40,  80},
             {80,  80},
             {120, 80}};
    std::vector<Position> rock_set = {};
    std::vector<Position> diamond_set = {};

    Model model4(wall_set, rock_set, diamond_set, sand_set);

    model4.jim_.j_pos = {40, 40};
    model4.set_key(ge211::Key::right());
    model4.on_frame(30);
    Position check_pos_1 = {80, 40};
    CHECK(!model4.in_set(model4.sand_set, check_pos_1));

    model4.set_key(ge211::Key::right());
    model4.on_frame(30);
    Position check_pos_2 = {120, 40};
    CHECK(!model4.in_set(model4.sand_set, check_pos_2));

    model4.set_key(ge211::Key::down());
    model4.on_frame(30);

    for (int i=0; i<2;i++){
        model4.set_key(ge211::Key::left());
        model4.on_frame(30);
    }

    std::vector<Position> new_sand_set = {};

    CHECK(model4.sand_set == new_sand_set);

}



TEST_CASE("score increment on diamond")
{
    std::vector<Position> wall_set = {};
    std::vector<Position> diamond_set = {{80,40},{120,40}};
    std::vector<Position> sand_set = {{80,80}, {120,80}};
    std::vector<Position> rock_set = {};

    Model model5(wall_set, rock_set, diamond_set, sand_set);
    CHECK(model5.score == 0);

    model5.jim_.j_pos = {40,40};

    for (int i = 0; i < 2; i++) {
        model5.set_key(ge211::Key::right());
        model5.on_frame(30);
    }

    Position jim_pos_s = {120,40};
    CHECK(model5.jim().j_pos == jim_pos_s);
    CHECK(model5.score == 2);

}



TEST_CASE("object motion")
{
    std::vector<Position> wall_set = {};
    std::vector<Position> sand_set = {{80,80},{120,80},{160,80}, {240, 240},
                                      {320, 240}};
    std::vector<Position> diamond_set = {{320, 40}};
    std::vector<Position> rock_set = {{120,40}, {240, 40}};

    Model model5(wall_set, rock_set, diamond_set, sand_set);

    /// jim moves twice
    for (int i = 0; i < 2; i++) {
        model5.set_key(ge211::Key::right());
        model5.on_frame(30);
    }

    /// check jim position
    Position jim_pos_s = {120,40};
    CHECK(model5.jim().j_pos == jim_pos_s);

    /// check rock position
    std::vector<Position> rock_set2 = { {160, 40}, {240, 120} };
    CHECK(model5.rock_set == rock_set2);

    /// check rock falls under gravity
    CHECK(!model5.in_set(model5.rock_set, {240,40}));
    CHECK(model5.in_set(model5.rock_set, {240,120}));

    /// check diamond falls under gravity
    CHECK(!model5.in_set(model5.diamond_set, {320,40}));
    CHECK(model5.in_set(model5.diamond_set, {320,120}));

    /// check rock rolls onto another




}
