#include "qt_game_map.hpp"
#include <algorithm>

namespace biv {

QtGameMap::QtGameMap(int height, int width) : GameMap(height, width) {}

void QtGameMap::add_obj(QtUIObject* obj) {
    objs.push_back(obj);
}

void QtGameMap::remove_obj(QtUIObject* obj) {
    objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::render(QPainter* painter, const QRect& viewport) {
    painter->save();
    
    painter->setBrush(QColor(101, 67, 33));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, height - 30, width, 30);
    
    for (auto obj : objs) {
        if (obj) {
            obj->render(painter);
        }
    }
    
    painter->restore();
}

}