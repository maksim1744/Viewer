#ifndef OBJECT_H
#define OBJECT_H

#include "drawproperties.h"
#include "treeitem.h"

#include <QDebug>
#include <QPainter>
#include <QPointF>
#include <QString>

#include <iomanip>
#include <set>
#include <sstream>
#include <string>

class Object {
public:
    Object();

    virtual void draw(DrawProperties &draw_properties);
    virtual void writeToTree(TreeItem *parent);

    bool needToDraw(DrawProperties &draw_properties);

    static QPointF parsePoint(std::string& s, int ind);
    static QColor parseColor(std::string& s, int ind);
    static std::string parseTag(std::string& s, size_t &ind);

    static QString toString(QPointF &point);
    static QString toString(QColor &color);
    static QString toString(bool b);
    static QString toString(int k);
    static QString toString(double d);

    std::string type = "none";
    std::vector<std::string> tags;

    TreeItem *tree_item = nullptr;
};

#endif // OBJECT_H
