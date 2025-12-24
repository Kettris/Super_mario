#include "qt_full_box.hpp"
#include <QBrush>

using namespace biv;

QtFullBox::QtFullBox(const Coord& top_left, const int width, const int height, UIFactory* ui_factory, QGraphicsScene* scene)
    : FullBox(top_left, width, height, ui_factory),
      QtUIObjectRectAdapter(top_left, width, height, scene, getColor()) {}

QColor QtFullBox::getColor() const {
    if (is_active_) {
        return QColor(255, 255, 0);
    } else {
        return QColor(255, 255, 255);
    }
}

void QtFullBox::updatePosition() {
    if (graphicsItem) {
        graphicsItem->setPos(std::round(top_left.x * 10), std::round(top_left.y * 10));
        graphicsItem->setBrush(QBrush(getColor()));
    }
}