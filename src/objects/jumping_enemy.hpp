#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
class JumpingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
private:
    float jump_timer = 0;
    bool is_jumping = false;
    int jump_counter = 0;
    float wait_counter = 0;
    bool is_waiting = false;
    bool can_safely_jump = true;

public:
    JumpingEnemy(const Coord& top_left, const int width, const int height);

    Rect get_rect() const noexcept override;
    Speed get_speed() const noexcept override;

    void process_horizontal_static_collision(Rect* obj) noexcept override;
    void process_mario_collision(Collisionable* mario) noexcept override;
    void process_vertical_static_collision(Rect* obj) noexcept override;
    
    void update(float delta_time) noexcept;

private:
    void try_jump() noexcept;
    void check_jump_safety() noexcept;
    bool can_jump_safely() const noexcept;
};
}