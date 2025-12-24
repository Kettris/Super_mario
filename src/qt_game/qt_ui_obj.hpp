#pragma once

#include <QPainter>

namespace biv {
class QtUIObject {
public:
    virtual ~QtUIObject() = default;
    virtual void render(QPainter* painter) const = 0;
    virtual int get_left() const = 0;
    virtual int get_top() const = 0;
    virtual int get_right() const = 0;
    virtual int get_bottom() const = 0;
};
}