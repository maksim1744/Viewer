#include "rectangle.h"

Rectangle::Rectangle() {
    type = "rectangle";
}

Rectangle::Rectangle(std::string s) {
    type = "rectangle";

    color = QColor(Qt::black);
    size_t ind = 0;
    while (ind < s.size()) {
        if (s.substr(ind, 2) == "c=") {
            center = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 2) == "s=") {
            size = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 4) == "col=") {
            color = parseColor(s, ind + 4);
        } else if (s.substr(ind, 2) == "f=") {
            fill = strtol(&s[ind + 2], nullptr, 10);
        }  else if (s.substr(ind, 2) == "w=") {
            width = strtol(&s[ind + 2], nullptr, 10);
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Rectangle::draw(QPainter &painter, Scene &scene) {
    if (width == -1) width = scene.getPenWidth();
    QRectF rect = QRectF(scene.transformPoint(center - size / 2), scene.transformPoint(center + size / 2));
    if (fill) {
        painter.fillRect(rect, QBrush(color));
    } else {
        painter.setPen(QPen(color, width));
        painter.drawRect(rect);
    }
}
