#include "rectangle.h"

Rectangle::Rectangle() {
    type = "rect";
}

Rectangle::Rectangle(std::string s) {
    type = "rect";

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
        } else  if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Rectangle::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    if (width == -1) width = draw_properties.pen_width;
    QRectF rect = QRectF(draw_properties.transformPoint(center - size / 2),
                         draw_properties.transformPoint(center + size / 2));
    if (fill) {
        draw_properties.painter.fillRect(rect, QBrush(color));
    } else {
        draw_properties.painter.setPen(QPen(color, width));
        draw_properties.painter.drawRect(rect);
    }
}

void Rectangle::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"rect", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    tree_item->appendChild(new TreeItem({"c", toString(center)}, tree_item));
    tree_item->appendChild(new TreeItem({"s", toString(size)}, tree_item));
    tree_item->appendChild(new TreeItem({"col", toString(color)}, tree_item));
    tree_item->appendChild(new TreeItem({"f", toString(fill)}, tree_item));
    tree_item->appendChild(new TreeItem({"w", toString(width)}, tree_item));
}
