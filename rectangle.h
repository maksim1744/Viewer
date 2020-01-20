#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "scene.h"

#include <QPainter>
#include <QPointF>
#include <QColor>
#include <string>

class Rectangle : public Object {
public:
    Rectangle();
    Rectangle(std::string s);

    void draw(QPainter &painter, Scene &scene) override;

    QPointF center, size;
    QColor color;
    bool fill = false;
};

#endif // RECTANGLE_H
