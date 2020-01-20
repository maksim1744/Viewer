#include "circle.h"

Circle::Circle() {
    type = "circle";
}

Circle::Circle(std::string s) {
    type = "circle";

    color = QColor(Qt::black);
    size_t ind = 0;
    while (ind < s.size()) {
        if (s.substr(ind, 2) == "c=") {
            center = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 2) == "r=") {
            radius = strtod(&s[ind + 2], nullptr);
        } else if (s.substr(ind, 4) == "col=") {
            color = parseColor(s, ind + 4);
        } else if (s.substr(ind, 2) == "f=") {
            fill = strtol(&s[ind + 2], nullptr, 10);
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Circle::draw(QPainter &painter, Scene &scene) {
    auto c = scene.transformPoint(center);
    auto r = scene.transformLength(radius);
    painter.setPen(QPen(color, scene.getPenWidth()));
    if (fill) {
        auto b = painter.brush();
        painter.setBrush(QBrush(color));
        painter.drawEllipse(c, r, r);
        painter.setBrush(b);
    } else {
        QRectF rect(c - QPointF(r, r), c + QPointF(r, r));
        painter.drawArc(rect, 0, 360 * 16);
    }
}
