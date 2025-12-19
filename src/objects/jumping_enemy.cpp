#include "jumping_enemy.hpp"
#include "map_movable.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
: RectMapMovableAdapter(top_left, width, height) {
    vspeed = 0;
    hspeed = 0.3;
    jump_counter = 0;
    wait_counter = 0;
    is_waiting = false;
    jump_timer = 0;
    is_jumping = false;
    can_safely_jump = true;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
    hspeed = -hspeed;
    move_horizontally();
    check_jump_safety();
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->get_speed().v > 0) {
        kill();
    } else {
        mario->kill();
    }
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    top_left.x += hspeed;
    if (!has_collision(obj)) {
        process_horizontal_static_collision(obj);
    } else {
        top_left.x -= hspeed;
    }

    if (vspeed > 0) {
        top_left.y -= vspeed;
        vspeed = 0;
        is_jumping = false;
        jump_counter++;
        
        if (jump_counter >= 3) {
            is_waiting = true;
            jump_counter = 0;
        }
    }
}

void JumpingEnemy::update(float delta_time) noexcept {
    check_jump_safety();
    
    if (is_waiting) {
        wait_counter += delta_time;
        if (wait_counter >= 0.5f) {
            is_waiting = false;
            wait_counter = 0;
        }
        return;
    }
    
    jump_timer += delta_time;
    
    if (jump_timer >= 1.0f && !is_jumping && vspeed == 0 && !is_waiting && can_jump_safely()) {
        try_jump();
        jump_timer = 0;
    }
}

void JumpingEnemy::try_jump() noexcept {
    if (vspeed == 0 && can_safely_jump) {
        vspeed = JUMP_SPEED * 0.7f;
        is_jumping = true;
    }
}

void JumpingEnemy::check_jump_safety() noexcept {
    float test_x = top_left.x + hspeed * 5.0f;
    float test_y = top_left.y + 10.0f;
    
    can_safely_jump = (test_y < 40.0f);
}

bool JumpingEnemy::can_jump_safely() const noexcept {
    return can_safely_jump;
}