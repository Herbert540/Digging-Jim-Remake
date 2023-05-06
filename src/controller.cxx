#include "controller.hxx"
#include <ge211.hxx>

Controller::Controller(std::vector<Position> wall_set,
                       std::vector<Position> rock_set,
                       std::vector<Position> diamond_set,
                       std::vector<Position> sand_set)
        : model_(wall_set,rock_set,diamond_set,sand_set), view_(model_)
{ }

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    if (key == ge211::Key::code('p')) {
        model_.set_key(ge211::Key::code('p'));
    }

    if (key == ge211::Key::code('r')) {
        model_.set_key(ge211::Key::code('r'));
    }

    if (key == ge211::Key::left()) {
        model_.set_key(ge211::Key::left());
    }

    if (key == ge211::Key::up()) {
        model_.set_key(ge211::Key::up());
    }

    if (key == ge211::Key::down()) {
        model_.set_key(ge211::Key::down());
    }

    if (key == ge211::Key::right()) {
        model_.set_key(ge211::Key::right());

    }

}


void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);

}

void Controller::on_frame(double dt) {
    model_.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}