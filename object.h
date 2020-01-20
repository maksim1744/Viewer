#ifndef OBJECT_H
#define OBJECT_H

class Scene;

#include <string>
#include <QPainter>
#include <QDebug>

class Object {
public:
    Object();

    virtual void draw(QPainter &painter, Scene &scene);

    static QPointF parsePoint(std::string& s, int ind);
    static QColor parseColor(std::string& s, int ind);

    std::string type = "none";
};

#endif // OBJECT_H
