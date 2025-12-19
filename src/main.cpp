#include <iostream>
#include <thread>
#include <chrono>

#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "third_level.hpp"
#include "ui_factory.hpp"
#include "user_input.hpp"

int main() {
    using namespace std::chrono;
    
    system("mode con: cols=200 lines=35");
    
    biv::os::init_settings();

    biv::Game game;
    biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
    biv::GameMap* game_map = ui_factory->get_game_map();
    biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
    biv::Mario* mario = ui_factory->get_mario();

    auto last_time = steady_clock::now();
    bool was_on_third_level = false;
    
    do {
        auto current_time = steady_clock::now();
        float delta_time = duration_cast<milliseconds>(current_time - last_time).count() / 1000.0f;
        last_time = current_time;

        biv::os::UserInput user_input = biv::os::get_user_input();
        
        switch (user_input) {
            case biv::os::UserInput::MAP_LEFT:
                mario->move_map_left();
                if (!game.check_static_collisions(mario)) {
                    game.move_map_left();
                }
                mario->move_map_right();
                break;
            case biv::os::UserInput::MAP_RIGHT:
                mario->move_map_right();
                if (!game.check_static_collisions(mario)) {
                    game.move_map_right();
                }
                mario->move_map_left();
                break;
            case biv::os::UserInput::MARIO_JUMP:
                mario->jump();
                break;
            case biv::os::UserInput::EXIT:
                game.finish();
                break;
        }

        ui_factory->update_enemies(delta_time);
        
        game.move_objs_horizontally();
        game.check_horizontally_static_collisions();

        game.move_objs_vertically();
        game.check_mario_collision();
        game.check_vertically_static_collisions();

        if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
            game.get_scores().reset();
            game_level->restart();
            mario = ui_factory->get_mario();
            std::this_thread::sleep_for(1000ms);
        }

        if (game.is_level_end()) {
            biv::ThirdLevel* current_third = dynamic_cast<biv::ThirdLevel*>(game_level);
            if (current_third) {
                was_on_third_level = true;
            } else {
                was_on_third_level = false;
            }
            
            game_level = game_level->get_next();
            mario = ui_factory->get_mario();
            
            biv::ThirdLevel* next_third = dynamic_cast<biv::ThirdLevel*>(game_level);
            if (was_on_third_level && !next_third) {
                game.get_scores().reset();
            }
            
            std::this_thread::sleep_for(1000ms);
            game.start_level();
        }

        game_map->refresh();
        biv::os::set_cursor_start_position();
        
        std::cout << "Score: " << game.get_scores().get_score();
        std::cout << "\n";
        game_map->show();
        
        std::this_thread::sleep_for(10ms);
    } while (!game.is_finished());

    return 0;
}
