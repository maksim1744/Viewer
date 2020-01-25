#ifndef SCENE_H
#define SCENE_H

class Group;

#include "circle.h"
#include "group.h"
#include "line.h"
#include "object.h"
#include "rectangle.h"
#include "treemodel.h"

#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QSlider>
#include <QSlider>
#include <QTimer>
#include <QTreeView>
#include <QWidget>

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

class Scene : public QWidget {
public:
    Scene(QWidget *parent);

    QPointF transformPoint(QPointF point);
    qreal transformLength(qreal length);

    int getPenWidth();
    int getTickCount();

    void setTickSlider(QSlider *tick_slider);
    void setPlayButton(QPushButton *button);
    void setTickLabel(QLabel *tick_label);
    void setObjectTree(QTreeView *object_tree);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void loadData();
    void initScene();
    Object* stringToObject(std::string s);
    void updateTickSlider();
    void updateTickLabel();
    void updateObjectTree();
    void setScale(double new_scale);
    void setTick(int new_tick);
    void onPlayPressed();

    QSlider *tick_slider = nullptr;
    QLabel *tick_label = nullptr;
    QPushButton *play_button = nullptr;
    QTreeView *object_tree = nullptr;

    QPainter *painter;

    bool is_initialized = false;

    QPointF scene_size = {100, 100};
    int pen_width = 1;

    QPointF scene_pos = {0, 0};
    QPointF prev_mouse_pos;
    double scale = 1;

    double run_speed = 1;
    bool is_running = false;
    QTimer *run_timer;

    bool y_zero_on_top = false;

    std::vector<Group *> data;
    Group *initial_data;

    int tick = 0;
};

#endif // SCENE_H
