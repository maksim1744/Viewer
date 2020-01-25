#ifndef OBJECT_H
#define OBJECT_H

class Scene;
class TreeItem;

#include <QDebug>
#include <QPainter>
#include <QPointF>
#include <QString>

#include <iomanip>
#include <sstream>
#include <string>

class Object {
public:
    Object();

    virtual void draw(QPainter &painter, Scene &scene);
    virtual void writeToTree(TreeItem *parent);

    static QPointF parsePoint(std::string& s, int ind);
    static QColor parseColor(std::string& s, int ind);

    static QString toString(QPointF &point);
    static QString toString(QColor &color);
    static QString toString(bool b);
    static QString toString(int k);
    static QString toString(double d);

    std::string type = "none";

    bool hidden = false;
};

#endif // OBJECT_H
