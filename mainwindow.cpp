#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initItems();
    //my_joy = new joystick();
    connect(timer,SIGNAL(timeout()),this,SLOT(sWatchHandler()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initItems()
{
    QFont f1("Arial",25);
    QFont f2("Arial",12);
    QFont f3("Arial",15);
    timer = new QTimer();
    centralWidget = new QWidget(this);
    horLayout = new QHBoxLayout();
    verLeftLayout = new QVBoxLayout();
    verRightLayout = new QVBoxLayout();
    automationBtn = new QPushButton("Automation");
    coinsBtn = new QPushButton("Count Coins");
    shapeDetectionBtn = new QPushButton("Detect Shapes");
    time = new QLabel("Time");
    time->setFont(f1);
    up = new QLabel("Up");
    down = new QLabel("Down");
    light = new QLabel("Light");
    depth = new QLabel("Depth");
    depth->setFont(f2);
    temp = new QLabel("Temperature");
    temp->setFont(f2);
    depthValue = new QLabel("0 m");   
    depthValue->setFont(f1);
    tempValue = new QLabel("0 c");
    tempValue->setFont(f1);
    mode = new QLabel("Mode");
    mode->setFont(f2);
    buttonSettings = new QLabel("Settings");
    sensorReadings = new QLabel("Sensor Readings");
    sensorReadings->setFont(f3);
    stopWatch = new QLabel("");
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
    verRightLayout->addWidget(time,0,Qt::AlignCenter);
    horLayout->addLayout(verLeftLayout);
    horLayout->addLayout(verRightLayout);
    centralWidget->setLayout(horLayout);
    timeVal = new QTime(0,minutes,seconds);
    timeText = timeVal->toString("mm : ss");
    time->setText(timeText);
    this->setCentralWidget(centralWidget);
    this->setGeometry(0,0,QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height());
}
void MainWindow::sWatchHandler()
{
    seconds ++;
    timeVal = new QTime(0,minutes,seconds);
    timeText = timeVal->toString("mm : ss");
    time->setText(timeText);

}
