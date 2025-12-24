#include "qt_mario.hpp"

using namespace biv;

QtMario::QtMario(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : Mario(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}