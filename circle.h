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

    QPointF center;
    qreal radius;
    QColor color;
    bool fill = false;
};

#endif // CIRCLE_H
