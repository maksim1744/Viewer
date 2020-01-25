#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"
#include "scene.h"

#include <QPainter>
#include <string>

class Circle : public Object {
public:
    Circle();
    Circle(std::string s);

    void draw(QPainter &painter, Scene &scene) override;
    void writeToTree(TreeItem *parent) override;

    QPointF center;
    qreal radius;
    QColor color;
    int width = -1;
    bool fill = false;
};

#endif // CIRCLE_H
