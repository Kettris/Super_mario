#include "flying_enemy.hpp"
#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height)
    : RectMapMovableAdapter(top_left, width, height) {
    vspeed = 0;
    hspeed = 0.5;
    flying_height = top_left.y;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
    hspeed = -hspeed;
    move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->get_speed().v > 0) {
        kill();
        vspeed = 0.5;
        hspeed = 0;
    } else {
        mario->kill();
    }
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    top_left.x += hspeed;
    if (!has_collision(obj)) {
        process_horizontal_static_collision(obj);
    } else {
        top_left.x -= hspeed;
    }

    if (vspeed > 0) {
        top_left.y -= vspeed;
        vspeed = 0;
    }
}

void FlyingEnemy::move_horizontally() noexcept {
    if (is_active_) {
        top_left.x += hspeed;
        top_left.y = flying_height;
    } else {
        top_left.x += hspeed;
    }
}

void FlyingEnemy::move_vertically() noexcept {
    if (!is_active_) {
        if (vspeed < MAX_V_SPEED) {
            vspeed += V_ACCELERATION;
        }
        top_left.y += vspeed;
    }
}