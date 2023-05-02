#include "Size.h"

Size::Size() : x_(0), y_(0) {}

Size::Size(int x, int y) : x_(x), y_(y) {}

int Size::getX() const {
    return x_;
}

int Size::getY() const {
    return y_;
}

void Size::setX(int x) {
    x_ = x;
}

void Size::setY(int y) {
    y_ = y;
}
