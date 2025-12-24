#include "qt_money.hpp"

using namespace biv;

QtMoney::QtMoney(const Coord& top_left, const int width, const int height, QGraphicsScene* scene)
    : Money(top_left, width, height),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}