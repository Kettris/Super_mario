#include "qt_ui_obj_rect_adapter.hpp"
#include <QBrush>
#include <QPen>
#include <cmath>

using namespace biv;

QtUIObjectRectAdapter::QtUIObjectRectAdapter(const Coord& top_left, const int width, 
                                           const int height, QGraphicsScene* scene, 
                                           const QColor& color)
    : scene(scene) {
    this->top_left = top_left;
    this->width = width;
    this->height = height;
    
    if (scene) {
        int scaledWidth = width * 10;
        int scaledHeight = height * 10;
        graphicsItem = new QGraphicsRectItem(0, 0, scaledWidth, scaledHeight);
        graphicsItem->setBrush(QBrush(color));
        graphicsItem->setPen(QPen(Qt::NoPen));
        scene->addItem(graphicsItem);
        updatePosition();
    }
}

QtUIObjectRectAdapter::~QtUIObjectRectAdapter() {
    removeFromScene();
}

void QtUIObjectRectAdapter::updatePosition() {
    if (graphicsItem) {
        graphicsItem->setPos(std::round(top_left.x * 10), std::round(top_left.y * 10));
    }
}

void QtUIObjectRectAdapter::updateColor() {
    if (graphicsItem) {
        graphicsItem->setBrush(QBrush(getColor()));
    }
}

void QtUIObjectRectAdapter::removeFromScene() {
    if (graphicsItem && scene) {
        scene->removeItem(graphicsItem);
        delete graphicsItem;
        graphicsItem = nullptr;
    }
}