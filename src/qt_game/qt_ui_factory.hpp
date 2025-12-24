#pragma once

#include <QGraphicsScene>
#include <vector>
#include "ui_factory.hpp"
#include "qt_box.hpp"
#include "qt_enemy.hpp"
#include "qt_flying_enemy.hpp"
#include "qt_full_box.hpp"
#include "qt_jumping_enemy.hpp"
#include "qt_mario.hpp"
#include "qt_money.hpp"
#include "qt_ship.hpp"

namespace biv {
class QtUIFactory : public UIFactory {
private:
    QGraphicsScene* scene = nullptr;
    QtMario* mario = nullptr;
    std::vector<QtBox*> boxes;
    std::vector<QtFullBox*> fullBoxes;
    std::vector<QtShip*> ships;
    std::vector<QtEnemy*> enemies;
    std::vector<QtJumpingEnemy*> jumpingEnemies;
    std::vector<QtFlyingEnemy*> flyingEnemies;
    std::vector<QtMoney*> moneys;
    
    const int WATER_LEVEL = 650;
    const int SCALE_FACTOR = 20;
    
public:
    QtUIFactory(Game* game, QGraphicsScene* scene);
    ~QtUIFactory();
    
    void clear_data() override;
    void create_box(const Coord& top_left, const int width, const int height) override;
    void create_enemy(const Coord& top_left, const int width, const int height) override;
    void create_jumping_enemy(const Coord& top_left, const int width, const int height) override;
    void create_flying_enemy(const Coord& top_left, const int width, const int height) override;
    void create_full_box(const Coord& top_left, const int width, const int height) override;
    void create_mario(const Coord& top_left, const int width, const int height) override;
    void create_money(const Coord& top_left, const int width, const int height) override;
    void create_ship(const Coord& top_left, const int width, const int height) override;
    
    GameMap* get_game_map() override { return nullptr; }
    Mario* get_mario() override;
    
    void update_enemies(float delta_time) override;
    void refresh();
    
    int getWaterLevel() const { return WATER_LEVEL; }
    int getScaleFactor() const { return SCALE_FACTOR; }
    
private:
    void create_game_map() override {}
};
}