#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "treeitem.h"

#include <QColor>
#include <QPainter>
#include <QPointF>

#include <string>

class Rectangle : public Object {
public:
    Rectangle();
    Rectangle(std::string s);

    void draw(DrawProperties &draw_properties) override;
    void writeToTree(TreeItem *parent) override;

    QPointF center, size;
    QColor color;
    int width = -1;
    bool fill = false;
};

#endif // RECTANGLE_H
