#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "money.hpp"

namespace biv {
class QtMoney : public Money, public QtUIObjectRectAdapter {
public:
    QtMoney(const Coord& top_left, const int width, const int height, QGraphicsScene* scene);
    QColor getColor() const override { return QColor(255, 255, 0); }
};
}