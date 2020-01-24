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
    scene->setTickSlider(tick_slider);

    auto play_btn = new QPushButton();
    play_btn->setText("Play");
    play_btn->setFixedSize(120, 60);
    scene->setPlayButton(play_btn);

    auto slider_grid = new QGridLayout();
    slider_grid->addWidget(tick_slider, 0, 0);
    slider_grid->addWidget(play_btn, 0, 1);

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
