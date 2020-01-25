#ifndef LINE_H
#define LINE_H

#include "object.h"
#include "scene.h"

#include <QPainter>
#include <string>

class Line : public Object {
public:
    Line();
    Line(std::string s);

    void draw(QPainter &painter, Scene &scene) override;
    void writeToTree(TreeItem *parent) override;

    QPointF start, finish;
    QColor color;
    int width = -1;
};

#endif // LINE_H
