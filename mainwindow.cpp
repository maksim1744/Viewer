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
    scene->setSlider(tick_slider);
    grid->addWidget(tick_slider, 1, 0);

    QWidget *widget = new QWidget();
    widget->setLayout(grid);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow() {
    delete ui;
}
