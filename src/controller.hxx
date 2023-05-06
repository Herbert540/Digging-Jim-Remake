#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(std::vector<Position> wall_set,
               std::vector<Position> rock_set,
               std::vector<Position> diamond_set,
               std::vector<Position> sand_set);
    void on_frame(double dt) override;
    ge211::Dims<int> initial_window_dimensions() const override;

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;

private:
    Model model_;
    View view_;
};
