#include "qt_ship.hpp"

using namespace biv;

QtShip::QtShip(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : Ship(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}