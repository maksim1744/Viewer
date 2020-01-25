#include "object.h"

Object::Object() {
}

void Object::draw(DrawProperties &draw_properties) {}
void Object::writeToTree(TreeItem *parent) {}

bool Object::needToDraw(DrawProperties &draw_properties) {
    if (tree_item != nullptr && !tree_item->isChecked()) return false;
    if (tags.empty()) return true;
    for (auto &tag : tags)
        if (draw_properties.active_tags.find(tag) != draw_properties.active_tags.end())
            return true;
    return false;
}

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

std::string Object::parseTag(std::string &s, size_t &ind) {
    std::string tag;
    while (ind < s.size() && s[ind] != ' ') {
        tag.push_back(s[ind]);
        ++ind;
    }
    return tag;
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
