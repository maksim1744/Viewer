#ifndef TEXT_H
#define TEXT_H

#include "object.h"
#include "treeitem.h"

#include <QFont>
#include <QPainter>
#include <QPointF>

#include <string>

class Text : public Object {
public:
    Text();
    Text(std::string s);

    void draw(DrawProperties &draw_properties) override;
    void writeToTree(TreeItem *parent) override;

    QPointF center;
    QColor color;
    double size = -1;
    std::string text;
};

#endif // TEXT_H
