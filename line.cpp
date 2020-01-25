#include "line.h"

Line::Line() {
    type = "line";
}

Line::Line(std::string s) {
    type = "line";

    color = QColor(Qt::black);
    size_t ind = 0;
    while (ind < s.size()) {
        if (s.substr(ind, 2) == "s=") {
            start = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 2) == "f=") {
            finish = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 4) == "col=") {
            color = parseColor(s, ind + 4);
        } else if (s.substr(ind, 2) == "w=") {
            width = strtol(&s[ind + 2], nullptr, 10);
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Line::draw(QPainter &painter, Scene &scene) {
    if (width <= 0) width = scene.getPenWidth();
    painter.setPen(QPen(color, width));
    painter.drawLine(scene.transformPoint(start), scene.transformPoint(finish));
}

void Line::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"line", ""}, parent));
    parent = parent->child(parent->childCount() - 1);
    parent->appendChild(new TreeItem({"s", toString(start)}, parent));
    parent->appendChild(new TreeItem({"f", toString(finish)}, parent));
    parent->appendChild(new TreeItem({"col", toString(color)}, parent));
    parent->appendChild(new TreeItem({"w", toString(width)}, parent));
}
