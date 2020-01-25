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
        } else  if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Circle::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    auto c = draw_properties.transformPoint(center);
    auto r = draw_properties.transformLength(radius);
    if (width == -1) width = draw_properties.pen_width;
    draw_properties.painter.setPen(QPen(color, width));
    if (fill) {
        auto b = draw_properties.painter.brush();
        draw_properties.painter.setBrush(QBrush(color));
        draw_properties.painter.drawEllipse(c, r, r);
        draw_properties.painter.setBrush(b);
    } else {
        QRectF rect(c - QPointF(r, r), c + QPointF(r, r));
        draw_properties.painter.drawArc(rect, 0, 360 * 16);
    }
}

void Circle::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"circle", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    tree_item->appendChild(new TreeItem({"c", toString(center)}, tree_item));
    tree_item->appendChild(new TreeItem({"r", toString(radius)}, tree_item));
    tree_item->appendChild(new TreeItem({"col", toString(color)}, tree_item));
    tree_item->appendChild(new TreeItem({"f", toString(fill)}, tree_item));
    tree_item->appendChild(new TreeItem({"w", toString(width)}, tree_item));
}
