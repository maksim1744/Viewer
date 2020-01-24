#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"

#include <QDebug>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QSlider>
#include <QSplitter>

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
