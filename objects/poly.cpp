#include "poly.h"

Poly::Poly() {
    type = "poly";
}

Poly::Poly(std::string s) {
    type = "poly";

    color = QColor(Qt::black);
    size_t ind = 0;
    while (ind < s.size()) {
        if (s.substr(ind, 4) == "col=") {
            color = parseColor(s, ind + 4);
        } else if (s.substr(ind, 2) == "f=") {
            fill = strtol(&s[ind + 2], nullptr, 10);
        } else if (s.substr(ind, 2) == "w=") {
            width = strtol(&s[ind + 2], nullptr, 10);
        } else if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        } else if (s.substr(ind, 2) == "p=") {
            points.push_back(parsePoint(s, ind + 2));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Poly::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    if (width == -1) width = draw_properties.pen_width;
    QPolygonF poly;
    for (auto point : points) {
        poly.append(draw_properties.transformPoint(point));
    }
    draw_properties.painter.setPen(QPen(color, width));
    if (fill) {
        auto b = draw_properties.painter.brush();
        draw_properties.painter.setBrush(QBrush(color));
        draw_properties.painter.drawPolygon(poly);
        draw_properties.painter.setBrush(b);
    } else {
        draw_properties.painter.drawPolyline(poly);
    }
}

void Poly::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"poly", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    tree_item->appendChild(new TreeItem({"col", toString(color)}, tree_item));
    tree_item->appendChild(new TreeItem({"f", toString(fill)}, tree_item));
    tree_item->appendChild(new TreeItem({"w", toString(width)}, tree_item));
    tree_item->appendChild(new TreeItem({"points", ""}, tree_item));
    tree_item = tree_item->child(tree_item->childCount() - 1);
    for (int i = 0; i < points.size(); ++i) {
        tree_item->appendChild(new TreeItem({("p" + std::to_string(i)).c_str(), toString(points[i])}, tree_item));
    }
}
