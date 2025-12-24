#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "rect.hpp"

namespace biv {
class QtUIObjectRectAdapter : virtual public Rect {
protected:
    QGraphicsRectItem* graphicsItem = nullptr;
    QGraphicsScene* scene = nullptr;
    
public:
    QtUIObjectRectAdapter() = default;
    QtUIObjectRectAdapter(const Coord& top_left, const int width, const int height, 
                         QGraphicsScene* scene, const QColor& color);
    virtual ~QtUIObjectRectAdapter();
    
    void updatePosition();
    void removeFromScene();
    
    virtual QColor getColor() const = 0;
    
protected:
    void updateColor();
};
}