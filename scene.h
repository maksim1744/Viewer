#ifndef SCENE_H
#define SCENE_H

#include "drawproperties.h"
#include "objects/circle.h"
#include "objects/group.h"
#include "objects/line.h"
#include "objects/object.h"
#include "objects/poly.h"
#include "objects/rectangle.h"
#include "objects/text.h"
#include "treemodel.h"

#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QListWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPlainTextEdit>
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
    double transformLength(double length);

    int getTickCount();

    void setTickSlider(QSlider *tick_slider);
    void setPlayButton(QPushButton *button);
    void setTickLabel(QLabel *tick_label);
    void setObjectTree(QTreeView *object_tree);
    void setTagsList(QListWidget *tags_list);
    void setMessageBox(QPlainTextEdit *msg_box);

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
    QListWidget *tags_list = nullptr;
    QPlainTextEdit *msg_box = nullptr;

    DrawProperties draw_properties;

    bool is_initialized = false;

    QPointF prev_mouse_pos;

    double run_speed = 1;
    bool is_running = false;
    QTimer *run_timer;

    std::vector<Group *> data;
    Group *initial_data;
    std::vector<std::string> messages;

    int tick = 0;

    QWidget *main_window;
};

#endif // SCENE_H
