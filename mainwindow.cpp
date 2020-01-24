#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto grid = new QGridLayout();

    auto splitter1 = new QSplitter();
    scene = new Scene(this);
    splitter1->setOrientation(Qt::Horizontal);
    splitter1->addWidget(scene);
    splitter1->setSizes(QList<int>() << 1600);
    grid->addWidget(splitter1, 0, 0);

    auto tick_slider = new QSlider();
    tick_slider->setOrientation(Qt::Horizontal);
    tick_slider->setMinimumHeight(35);
    tick_slider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,"
        "        stop: 0 #66e, stop: 1 #bbf);"
        "    background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,"
        "        stop: 0 #bbf, stop: 1 #55f);"
        "    border: 1px solid #777;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::add-page:horizontal {"
        "    background: #fff;"
        "    border: 1px solid #777;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #eee, stop:1 #ccc);"
        "    border: 1px solid #777;"
        "    width: 30px;"
        "    margin-top: -2px;"
        "    margin-bottom: -2px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #fff, stop:1 #ddd);"
        "    border: 1px solid #444;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal:disabled {"
        "    background: #bbb;"
        "    border-color: #999;"
        "}"
        "QSlider::add-page:horizontal:disabled {"
        "    background: #eee;"
        "    border-color: #999;"
        "}"
        "QSlider::handle:horizontal:disabled {"
        "    background: #eee;"
        "    border: 1px solid #aaa;"
        "    border-radius: 4px;"
        "}"
    );
    scene->setTickSlider(tick_slider);

    auto play_btn = new QPushButton();
    play_btn->setText("Play");
    play_btn->setFixedSize(120, 60);
    scene->setPlayButton(play_btn);

    auto slider_grid = new QGridLayout();
    slider_grid->addWidget(tick_slider, 0, 0);
    slider_grid->addWidget(play_btn, 0, 1);
    slider_grid->setSpacing(20);

    QWidget *widget1 = new QWidget();
    widget1->setLayout(slider_grid);
    widget1->setMaximumHeight(80);
    grid->addWidget(widget1, 1, 0);

    QWidget *widget2 = new QWidget();
    widget2->setLayout(grid);
    this->setCentralWidget(widget2);
}

MainWindow::~MainWindow() {
    delete ui;
}
