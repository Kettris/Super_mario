#include "qt_flying_enemy.hpp"

using namespace biv;

QtFlyingEnemy::QtFlyingEnemy(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : FlyingEnemy(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}