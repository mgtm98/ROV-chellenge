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

    gstream();

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

void MainWindow::gstream()
{
    videoWidget = new QVideoWidget;
    player = new QMediaPlayer;
    process = new QProcess;
    verLeftLayout ->addWidget(videoWidget);
    QString program = "gst-launch-1.0";
    QStringList arguments;
    // QMediaPlayer expects encoded data
    arguments << "-v" << "videotestsrc" << "!" << "video/x-raw,width=1280,height=720"
              << "!" << "decodebin" << "!" << "x264enc" << "!" << "filesink" << "location=/dev/stderr";

   // arguments << "-v" << "tcpclientsrc" << "host=192.168.1.1" << "port=9999" << "!" << "gdpdepay" << "!" << "rtpht264depay"
             // << "!" << "ffdec_h264" << "!" << "ffmpegcolorspace" << "!" << "autovideosink" << "sync=false";

    process->setReadChannel(QProcess::StandardError);
    process->start(program, arguments);
    process->waitForReadyRead();

    player->setMedia(QMediaContent(), process);
    player->play();
    player->setVideoOutput(videoWidget);
}

