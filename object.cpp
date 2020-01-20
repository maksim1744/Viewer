#include "object.h"

Object::Object() {
}

void Object::draw(QPainter &painter, Scene &scene) {}

QPointF Object::parsePoint(std::string &s, int ind) {
    auto end = &s[ind + 1];
    QPointF result(0, 0);
    result.rx() = std::strtod(end, &end);
    ++end;
    result.ry() = std::strtod(end, &end);
    return result;
}

QColor Object::parseColor(std::string &s, int ind) {
    auto end = &s[ind + 1];
    QColor result;
    result.setRed(std::strtol(end, &end, 10));
    ++end;
    result.setGreen(std::strtol(end, &end, 10));
    ++end;
    result.setBlue(std::strtol(end, &end, 10));
    if (*end == ',') {
        ++end;
        result.setAlpha(std::strtol(end, &end, 10));
    }
    return result;
}
