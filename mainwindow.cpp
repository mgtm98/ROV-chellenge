#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initItems();
    my_joy = new joystick();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initItems()
{
    centralWidget = new QWidget(this);
    horLayout = new QHBoxLayout();
    timerLayout = new QHBoxLayout();
    verLeftLayout = new QVBoxLayout();
    verRightLayout = new QVBoxLayout();
    automationBtn = new QPushButton("Automation");
    coinsBtn = new QPushButton("Count Coins");
    shapeDetectionBtn = new QPushButton("Detect Shapes");
    time = new QLabel("Time");
    up = new QLabel("Up");
    down = new QLabel("Down");
    light = new QLabel("Light");
    depth = new QLabel("Depth");
    temp = new QLabel("Temperature");
    depthValue = new QLabel("0 m");
    tempValue = new QLabel("0 c");
    mode = new QLabel("Mode");
    buttonSettings = new QLabel("Settings");
    sensorReadings = new QLabel("Sensor Readings");
    sec1 = new QLabel("0");
    sec2 = new QLabel("0");
    min1 = new QLabel("0");
    min2 = new QLabel("0");
    separator = new QLabel(":");
    timerLayout->setContentsMargins(200,0,200,0);
    timerLayout->addWidget(min1,0);
    timerLayout->addWidget(min2,0);
    timerLayout->addWidget(separator);
    timerLayout->addWidget(sec1,0);
    timerLayout->addWidget(sec2,0);




    verLeftLayout ->addWidget(buttonSettings);
    verLeftLayout ->addWidget(light);
    verLeftLayout ->addWidget(up);
    verLeftLayout ->addWidget(down);
    verRightLayout->addWidget(sensorReadings);
    verRightLayout->addWidget(depth);
    verRightLayout->addWidget(depthValue,0,Qt::AlignCenter);
    verRightLayout->addWidget(temp);
    verRightLayout->addWidget(tempValue,0,Qt::AlignCenter);
    verRightLayout->addWidget(mode);
    verRightLayout->addWidget(time);
    verRightLayout->addLayout(timerLayout);

    horLayout->addLayout(verLeftLayout);
    horLayout->addLayout(verRightLayout);
    centralWidget->setLayout(horLayout);
    this->setCentralWidget(centralWidget);
    this->setGeometry(0,0,QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height());
}
