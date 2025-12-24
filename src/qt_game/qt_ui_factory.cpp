#include "qt_ui_factory.hpp"

using namespace biv;

QtUIFactory::QtUIFactory(Game* game, QGraphicsScene* scene) 
    : UIFactory(game), scene(scene) {}

QtUIFactory::~QtUIFactory() {
    clear_data();
}

void QtUIFactory::clear_data() {
    if (!game) return;
    
    game->remove_objs();
    
    for (auto box : boxes) delete box;
    for (auto fullBox : fullBoxes) delete fullBox;
    for (auto ship : ships) delete ship;
    for (auto enemy : enemies) delete enemy;
    for (auto jumpingEnemy : jumpingEnemies) delete jumpingEnemy;
    for (auto flyingEnemy : flyingEnemies) delete flyingEnemy;
    for (auto money : moneys) delete money;
    
    boxes.clear();
    fullBoxes.clear();
    ships.clear();
    enemies.clear();
    jumpingEnemies.clear();
    flyingEnemies.clear();
    moneys.clear();
    
    delete mario;
    mario = nullptr;
}

void QtUIFactory::create_box(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtBox* box = new QtBox(top_left, width, height, scene);
    boxes.push_back(box);
    if (game) {
        game->add_map_movable(box);
        game->add_static_obj(box);
    }
}

void QtUIFactory::create_enemy(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtEnemy* enemy = new QtEnemy(top_left, width, height, scene);
    enemies.push_back(enemy);
    if (game) {
        game->add_map_movable(enemy);
        game->add_movable(enemy);
        game->add_collisionable(enemy);
    }
}

void QtUIFactory::create_jumping_enemy(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtJumpingEnemy* enemy = new QtJumpingEnemy(top_left, width, height, scene);
    jumpingEnemies.push_back(enemy);
    if (game) {
        game->add_map_movable(enemy);
        game->add_movable(enemy);
        game->add_collisionable(enemy);
    }
}

void QtUIFactory::create_flying_enemy(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtFlyingEnemy* enemy = new QtFlyingEnemy(top_left, width, height, scene);
    flyingEnemies.push_back(enemy);
    if (game) {
        game->add_map_movable(enemy);
        game->add_movable(enemy);
        game->add_collisionable(enemy);
    }
}

void QtUIFactory::create_full_box(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtFullBox* fullBox = new QtFullBox(top_left, width, height, this, scene);
    fullBoxes.push_back(fullBox);
    if (game) {
        game->add_collisionable(fullBox);
        game->add_map_movable(fullBox);
        game->add_static_obj(fullBox);
    }
}

void QtUIFactory::create_mario(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    if (game) {
        game->remove_collisionable(mario);
        game->remove_movable(mario);
        game->remove_mario();
    }
    
    delete mario;
    
    mario = new QtMario(top_left, width, height, scene);
    if (game) {
        game->add_collisionable(mario);
        game->add_movable(mario);
        game->add_mario(mario);
    }
}

void QtUIFactory::create_money(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtMoney* money = new QtMoney(top_left, width, height, scene);
    moneys.push_back(money);
    if (game) {
        game->add_map_movable(money);
        game->add_movable(money);
        game->add_collisionable(money);
        game->get_scores().add_coin_collect();
    }
}

void QtUIFactory::create_ship(const Coord& top_left, const int width, const int height) {
    if (!scene) return;
    
    QtShip* ship = new QtShip(top_left, width, height, scene);
    ships.push_back(ship);
    if (game) {
        game->add_map_movable(ship);
        game->add_static_obj(ship);
    }
}

Mario* QtUIFactory::get_mario() {
    return mario;
}

void QtUIFactory::update_enemies(float delta_time) {
    for (auto enemy : jumpingEnemies) {
        if (enemy->is_active()) {
            enemy->update(delta_time);
        }
    }
}

void QtUIFactory::refresh() {
    for (auto box : boxes) box->updatePosition();
    for (auto fullBox : fullBoxes) fullBox->updatePosition();
    for (auto ship : ships) ship->updatePosition();
    for (auto enemy : enemies) enemy->updatePosition();
    for (auto jumpingEnemy : jumpingEnemies) jumpingEnemy->updatePosition();
    for (auto flyingEnemy : flyingEnemies) flyingEnemy->updatePosition();
    for (auto money : moneys) money->updatePosition();
    if (mario) mario->updatePosition();
}