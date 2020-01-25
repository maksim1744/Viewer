#ifndef POLY_H
#define POLY_H

#include "object.h"
#include "treeitem.h"

#include <QPainter>
#include <QPointF>
#include <QPolygonF>

#include <string>
#include <vector>

class Poly : public Object {
public:
    Poly();
    Poly(std::string s);

    void draw(DrawProperties &draw_properties) override;
    void writeToTree(TreeItem *parent) override;

    std::vector<QPointF> points;
    QColor color;
    int width = -1;
    bool fill = true;
};

#endif // POLY_H
