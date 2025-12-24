#include "qt_enemy.hpp"

using namespace biv;

QtEnemy::QtEnemy(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : Enemy(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}