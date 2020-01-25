#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"
#include "treeitem.h"

#include <QPainter>

#include <string>

class Circle : public Object {
public:
    Circle();
    Circle(std::string s);

    void draw(DrawProperties &draw_properties) override;
    void writeToTree(TreeItem *parent) override;

    QPointF center;
    qreal radius;
    QColor color;
    int width = -1;
    bool fill = false;
};

#endif // CIRCLE_H
