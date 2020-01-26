#include "text.h"

Text::Text() {
    type = "text";
}

Text::Text(std::string s) {
    type = "text";

    color = QColor(Qt::black);
    size_t ind = 0;
    while (ind < s.size()) {
        if (s.substr(ind, 2) == "c=") {
            center = parsePoint(s, ind + 2);
        } else if (s.substr(ind, 4) == "col=") {
            color = parseColor(s, ind + 4);
        } else if (s.substr(ind, 2) == "s=") {
            size = std::strtod(&s[ind + 2], nullptr);
        } else if (s.substr(ind, 2) == "m=") {
            ind += 2;
            char up_to = ' ';
            if (ind < s.size() && s[ind] == '"') {
                up_to = '"';
                ++ind;
            }
            text.clear();
            while (ind < s.size() && s[ind] != up_to)
                text.push_back(s[ind++]);
            std::replace(text.begin(), text.end(), ';', '\n');
        } else  if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Text::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    if (size <= 0) size = draw_properties.font_size;
    QFont font = draw_properties.painter.font();
    int current_size = draw_properties.transformLength(size);
    if (current_size <= 0 || current_size >= 32000) return;
    font.setPixelSize(current_size);
    draw_properties.painter.setFont(font);
    draw_properties.painter.setPen(color);
    auto center = draw_properties.transformPoint(this->center);
    draw_properties.painter.drawText(QRectF(center - QPointF(1e7, 1e7), center + QPointF(1e7, 1e7)), Qt::AlignCenter, text.c_str());
}

void Text::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({"text", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    tree_item->appendChild(new TreeItem({"c", toString(center)}, tree_item));
    tree_item->appendChild(new TreeItem({"col", toString(color)}, tree_item));
    tree_item->appendChild(new TreeItem({"t", text.c_str()}, tree_item));
}
