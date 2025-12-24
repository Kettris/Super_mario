#include "qt_box.hpp"

using namespace biv;

QtBox::QtBox(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : Box(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}