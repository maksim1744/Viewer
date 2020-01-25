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
        } else  if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Line::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    if (width <= 0) width = draw_properties.pen_width;
    draw_properties.painter.setPen(QPen(color, width));
    draw_properties.painter.drawLine(draw_properties.transformPoint(start), draw_properties.transformPoint(finish));
}

void Line::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"line", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    tree_item->appendChild(new TreeItem({"s", toString(start)}, tree_item));
    tree_item->appendChild(new TreeItem({"f", toString(finish)}, tree_item));
    tree_item->appendChild(new TreeItem({"col", toString(color)}, tree_item));
    tree_item->appendChild(new TreeItem({"w", toString(width)}, tree_item));
}
