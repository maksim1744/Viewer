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
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Line::draw(QPainter &painter, Scene &scene) {
    painter.setPen(QPen(color, scene.getPenWidth()));
    painter.drawLine(scene.transformPoint(start), scene.transformPoint(finish));
}
