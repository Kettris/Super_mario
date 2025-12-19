#include "second_level.hpp"
#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
    init_data();
}

bool SecondLevel::is_final() const noexcept {
    return false;
}

biv::GameLevel* SecondLevel::get_next() {
    if (!next) {
        clear_data();
        next = new biv::ThirdLevel(ui_factory);
    }
    return next;
}

void SecondLevel::init_data() {
    ui_factory->create_mario({39, 10}, 3, 3);

    ui_factory->create_ship({20, 25}, 40, 2);
    ui_factory->create_ship({60, 20}, 10, 7);
    ui_factory->create_ship({80, 25}, 20, 3);
    ui_factory->create_ship({120, 20}, 10, 7);
    ui_factory->create_ship({150, 25}, 40, 2);
    ui_factory->create_ship({140, 15}, 5, 3);

    ui_factory->create_box({60, 10}, 10, 3);
    ui_factory->create_full_box({70, 10}, 5, 3);
    ui_factory->create_box({75, 10}, 15, 3);
   
    ui_factory->create_full_box({25, 15}, 5, 3);
    ui_factory->create_full_box({180, 15}, 5, 3);

    ui_factory->create_enemy({25, 5}, 3, 2);
    ui_factory->create_enemy({65, 15}, 3, 2);
    ui_factory->create_enemy({125, 15}, 3, 2);
    ui_factory->create_enemy({160, 5}, 3, 2);
   
    ui_factory->create_flying_enemy({30, 15}, 3, 2);
    ui_factory->create_flying_enemy({170, 14}, 3, 2);
   
    ui_factory->create_ship({195, 20}, 15, 7);
}