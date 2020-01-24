#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"

#include <QMainWindow>
#include <QLayout>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QSplitter>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QFrame>

// QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Scene *scene;

    int last_tick = -1;
    int tick = 0;
};
#endif // MAINWINDOW_H
