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
        } else if (s.substr(ind, 2) == "w=") {
            width = strtol(&s[ind + 2], nullptr, 10);
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Circle::draw(QPainter &painter, Scene &scene) {
    auto c = scene.transformPoint(center);
    auto r = scene.transformLength(radius);
    if (width == -1) width = scene.getPenWidth();
    painter.setPen(QPen(color, width));
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

void Circle::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"circle", ""}, parent));
    parent = parent->child(parent->childCount() - 1);
    parent->appendChild(new TreeItem({"c", toString(center)}, parent));
    parent->appendChild(new TreeItem({"r", toString(radius)}, parent));
    parent->appendChild(new TreeItem({"col", toString(color)}, parent));
    parent->appendChild(new TreeItem({"f", toString(fill)}, parent));
    parent->appendChild(new TreeItem({"w", toString(width)}, parent));
}
