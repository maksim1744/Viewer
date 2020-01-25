#ifndef DRAWPROPERTIES_H
#define DRAWPROPERTIES_H

#include <QPainter>
#include <QPointF>
#include <QSize>

#include <set>
#include <string>
#include <vector>

class DrawProperties {
public:
    DrawProperties();

    QPointF transformPoint(QPointF point);
    double transformLength(double length);

    QPainter painter;

    QSize window_size;
    QPointF scene_size = {100, 100};
    QPointF scene_pos = {0, 0};
    double scale = 1;
    bool y_zero_on_top = false;

    int pen_width = 1;

    std::set<std::string> active_tags;
};

#endif // DRAWPROPERTIES_H
