#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <string>
#include <iostream>
#include <vector>

class Scene : public QWidget {
public:
    Scene(QWidget *parent);

    QPointF transformPoint(QPointF point);
    qreal transformLength(qreal length);

    int getPenWidth();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void loadData();
    void initScene();
    Object* stringToObject(std::string s);

    QPainter *painter;

    bool is_initialized = false;

    QPointF scene_size = {100, 100};
    int pen_width = 1;

    QPointF scene_pos = {0, 0};
    QPointF prev_mouse_pos;
    double scale = 1;

    std::vector<std::vector<Object*>> data;

    int tick = 0;
};

#endif // SCENE_H
