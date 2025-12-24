#include "qt_jumping_enemy.hpp"

using namespace biv;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : JumpingEnemy(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}