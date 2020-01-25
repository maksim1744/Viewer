#include "drawproperties.h"

DrawProperties::DrawProperties() {}

QPointF DrawProperties::transformPoint(QPointF point) {
    point -= scene_pos;
    point *= scale;
    if (!y_zero_on_top)
        point.ry() = window_size.height() - point.ry();
    return point;
}

double DrawProperties::transformLength(double length) {
    return length * scale;
}
