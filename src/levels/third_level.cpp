#include "third_level.hpp"
#include "first_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
    init_data();
}

bool ThirdLevel::is_final() const noexcept {
    return false;
}

biv::GameLevel* ThirdLevel::get_next() {
    if (!next) {
        clear_data();
        next = new biv::FirstLevel(ui_factory);
    }
    return next;
}

void ThirdLevel::init_data() {
    ui_factory->create_mario({39, 10}, 3, 3);

    ui_factory->create_ship({20, 25}, 30, 2);
    ui_factory->create_ship({50, 20}, 15, 7);
    ui_factory->create_ship({70, 25}, 65, 2);
    ui_factory->create_ship({150, 20}, 15, 7);
    ui_factory->create_ship({180, 25}, 40, 2);

    ui_factory->create_box({40, 14}, 8, 3);
    ui_factory->create_full_box({55, 8}, 5, 3);
    ui_factory->create_box({85, 15}, 10, 3);
    ui_factory->create_full_box({110, 10}, 5, 3);
    ui_factory->create_box({140, 12}, 8, 3);
    ui_factory->create_full_box({165, 8}, 5, 3);
    ui_factory->create_box({200, 15}, 10, 3);

    ui_factory->create_enemy({25, 5}, 3, 2);
    ui_factory->create_enemy({75, 15}, 3, 2);
    ui_factory->create_enemy({130, 5}, 3, 2);
    ui_factory->create_enemy({190, 15}, 3, 2);
   
    ui_factory->create_jumping_enemy({100, 5}, 3, 2);
   
    ui_factory->create_flying_enemy({90, 13}, 3, 2);
    ui_factory->create_flying_enemy({120, 23}, 3, 2);
    ui_factory->create_flying_enemy({200, 13}, 3, 2);
   
    ui_factory->create_ship({225, 20}, 15, 7);
}