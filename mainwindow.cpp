#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    splitter1 = new QSplitter();
    scene = new Scene(this);
    splitter1->setOrientation(Qt::Horizontal);
    btn = new QPushButton();
    splitter1->addWidget(scene);
//    splitter1->addWidget(btn);
    splitter1->setSizes(QList<int>() << 1600);
    this->setCentralWidget(splitter1);
}

MainWindow::~MainWindow() {
    delete ui;
}
