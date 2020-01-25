#include "object.h"

Object::Object() {
}

void Object::draw(QPainter &painter, Scene &scene) {}
void Object::writeToTree(TreeItem *parent) {}

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

QString Object::toString(QPointF &point) {
    std::stringstream ss;
    ss << std::setprecision(5);
    ss << '(' << point.x() << ", " << point.y() << ')';
    return QString(ss.str().c_str());
}

QString Object::toString(QColor &color) {
    std::stringstream ss;
    ss << '(' << color.red() << ", " << color.green() << ", " << color.blue() << ", " << color.alpha() << ')';
    return QString(ss.str().c_str());
}

QString Object::toString(bool b) {
    return QString(b ? "true" : "false");
}

QString Object::toString(int k) {
    return QString(std::to_string(k).c_str());
}

QString Object::toString(double d) {
    std::stringstream ss;
    ss << std::setprecision(5);
    ss << d;
    return QString(ss.str().c_str());
}
