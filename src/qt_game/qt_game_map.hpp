#pragma once

#include <vector>
#include <QPainter>
#include "../model/game_map.hpp"

namespace biv {

class QtUIObject;

class QtGameMap : public GameMap {
public:
    QtGameMap(int height, int width);
    
    void clear() noexcept override {}
    void refresh() noexcept override {}
    void remove_objs() override {}
    void show() const noexcept override {}
    
    void add_obj(QtUIObject* obj);
    void remove_obj(QtUIObject* obj);
    
    void render(QPainter* painter, const QRect& viewport);
    
private:
    std::vector<QtUIObject*> objs;
};

}