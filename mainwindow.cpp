#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent,QRos *ros) :
    QMainWindow(parent)
{
    this->ros = ros;
    m_player1 =new Player(nullptr,"udpsrc port=1234 ! application/x-rtp,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! autovideosink");

    initItems();
    //my_joy = new Joystick(0,100,nullptr,ros,m_player1,m_player2);
    //connect(automationBtn,SIGNAL(clicked()),this,SLOT(autoBtnPressed()));
    //connect(coinsBtn,SIGNAL(clicked()),this,SLOT(countCoinsBtnPressed()));
    //connect(shapeDetectionBtn,SIGNAL(clicked()),this,SLOT(shapeDetectionBtnPressed()));
    //connect(lightOn,SIGNAL(clicked()),this,SLOT(toggleLightOn()));
    //connect(lightOff,SIGNAL(clicked()),this,SLOT(toggleLightOff()));
    //connect(updateDepthBtn,SIGNAL(clicked()),this,SLOT(updateDepth()));
    connect(camera1OnBtn,SIGNAL(clicked()),this,SLOT(cameraOnPressed(1)));
    connect(camera2OnBtn,SIGNAL(clicked()),this,SLOT(cameraOnPressed(2)));
    connect(camera1OffBtn,SIGNAL(clicked()),this,SLOT(cameraOnPressed(1)));
    connect(camera2OffBtn,SIGNAL(clicked()),this,SLOT(cameraOnPressed(2)));

    connect(timer,SIGNAL(timeout()),this,SLOT(sWatchHandler()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
}
void MainWindow::initItems()
{
    QFont f1("Arial",25);
    QFont f2("Arial",12);
    QFont f3("Arial",15);
    m_player2 =new Player(this,"");
    m_player1->setFixedHeight(500);
    m_player2->setFixedHeight(500);

    timer = new QTimer();
    centralWidget = new QWidget(this);
    horLayout = new QHBoxLayout();
    verLeftLayout = new QVBoxLayout();
    verRightLayout = new QVBoxLayout();
    //lightBtnslayout = new QHBoxLayout();
   // depthLayout = new QHBoxLayout();
    //btnLayout = new QGridLayout();
    cameraLayout1 = new QHBoxLayout();
    cameraLayout2 = new QHBoxLayout();
    //fix  =new QLineEdit();
   // automationBtn = new QPushButton("Automation");
    //automationBtn->setStyleSheet("QPushButton { background-color:blue; color : white; }");
    //coinsBtn = new QPushButton("Count Coins");
    //coinsBtn->setStyleSheet("QPushButton { background-color:blue; color : white; }");
    /*shapeDetectionBtn = new QPushButton("Detect Shapes");
    shapeDetectionBtn->setStyleSheet("QPushButton { background-color:blue; color : white; }");
    updateDepthBtn = new QPushButton("Update");
    updateDepthBtn->setStyleSheet("QPushButton { background-color:green; color : white; }");
    lightOn = new QPushButton("On");
    lightOn->setStyleSheet("QPushButton { background-color:green; color : white; }");
    lightOff = new QPushButton("Off");
    lightOff->setStyleSheet("QPushButton {   background-color:red; color : white; }");*/
    camera1OnBtn = new QPushButton("On");
    camera1OnBtn->setStyleSheet("QPushButton {   background-color:green; color : white; }");
    camera1OffBtn = new QPushButton("Pause");
    camera1OffBtn->setStyleSheet("QPushButton {   background-color:red; color : white; }");
    camera2OnBtn = new QPushButton("On");
    camera2OffBtn = new QPushButton("Pause");
    camera2OnBtn->setStyleSheet("QPushButton {   background-color:green; color : white; }");
    camera2OffBtn->setStyleSheet("QPushButton {   background-color:red; color : white; }");
    coinNotxt = new QLabel("Number of coins ");
    coinNotxt->setStyleSheet("QLabel {  color : blue; }");
    coinNotxt->setFont(f2);
    coinNo = new QLabel(QString::number(coins));
    coinNo->setStyleSheet("QLabel {  color : green; }");
    coinNo->setFont(f1);
    camera1 = new QLabel("Camera 1");
    camera2 = new QLabel("Camera 2");
    camera1->setStyleSheet("QLabel {  color : blue; }");
    camera2->setStyleSheet("QLabel {  color : blue; }");

    camera1->setFont(f2);
    camera2->setFont(f2);
   /* adjustDepth = new QLabel("Update depth");
    adjustDepth->setFont(f2);
    adjustDepth->setStyleSheet("QLabel {  color : blue; }");

    editDepth = new QLineEdit();*/
    time = new QLabel("");
    time->setFont(f1);
  /*  up = new QLabel("Up");
    up->setStyleSheet("QLabel {  color : blue; }");
    down = new QLabel("Down");
    down->setStyleSheet("QLabel {  color : blue; }");

    light = new QLabel("Light");
    light->setStyleSheet("QLabel {  color : blue; }");
    light->setFont(f2);*/

    depth = new QLabel("Depth");
    depth->setStyleSheet("QLabel {  color : blue; }");

    sWatch = new QLabel("Countdown");
    sWatch->setStyleSheet("QLabel {  color : blue; }");

    depth->setFont(f2);
    temp = new QLabel("Temperature");
    temp->setStyleSheet("QLabel {  color : blue; }");

    temp->setFont(f2);
    depthValue = new QLabel(QString::number(depthVal) + "m");
    depthValue->setFont(f1);
    tempValue = new QLabel(QString::number(tempVal) + ".c");
    tempValue->setFont(f1);
    /*mode = new QLabel("Mode");
    mode->setFont(f2);
    mode->setStyleSheet("QLabel {  color : blue; }");
    btnLayout->addWidget(automationBtn,0,0);
    btnLayout->addWidget(coinsBtn,0,1);
    btnLayout->addWidget(shapeDetectionBtn,0,3);*/
    buttonSettings = new QLabel("Settings");
    buttonSettings->setFont(f3);
    sensorReadings = new QLabel("Sensor Readings");
    sensorReadings->setFont(f3);
    /*updateDepthBtn->setFixedWidth(200);
    depthLayout->addWidget(adjustDepth);
    depthLayout->addWidget(editDepth);
    depthLayout->addWidget(updateDepthBtn);
    depthLayout->setContentsMargins(0,0,300,0);
    lightBtnslayout ->addWidget(light);
    lightBtnslayout->addWidget(lightOn);
    lightBtnslayout->addWidget(lightOff);
    lightBtnslayout->setContentsMargins(0,0,300,0);*/
    cameraLayout1->addWidget(camera1);
    cameraLayout1->addWidget(camera1OnBtn);
    cameraLayout1->addWidget(camera1OffBtn);
    cameraLayout1->setContentsMargins(0,0,300,0);
    cameraLayout2->addWidget(camera2);
    cameraLayout2->addWidget(camera2OnBtn);
    cameraLayout2->addWidget(camera2OffBtn);
    cameraLayout2->setContentsMargins(0,0,300,0);
    verLeftLayout->addWidget(m_player1);
    verLeftLayout ->addLayout(cameraLayout1);
    verLeftLayout->addWidget(sWatch);

    verLeftLayout ->addWidget(time,0,Qt::AlignCenter);

   // verLeftLayout ->addLayout(lightBtnslayout);
    verLeftLayout ->addWidget(coinNotxt);
    verLeftLayout->addWidget(coinNo,0,Qt::AlignCenter);
    /*verLeftLayout ->addLayout(depthLayout);
    verLeftLayout ->addWidget(up);
    verLeftLayout ->addWidget(down);*/
    verRightLayout->addWidget(m_player2);
    verRightLayout ->addLayout(cameraLayout2);

    verRightLayout->addWidget(sensorReadings);
    verRightLayout->addWidget(depth);
    verRightLayout->addWidget(depthValue,0,Qt::AlignCenter);
    verRightLayout->addWidget(temp);
    verRightLayout->addWidget(tempValue,0,Qt::AlignCenter);
    //verRightLayout->addWidget(mode);
    //verRightLayout->addLayout(btnLayout);
    //verRightLayout->addWidget(fix);
    //verRightLayout->addWidget(buttonSettings);
    horLayout->addLayout(verLeftLayout);
    horLayout->addLayout(verRightLayout);
    centralWidget->setLayout(horLayout);
    timeVal = new QTime(0,minutes,seconds);
    timeText = timeVal->toString("mm : ss");
    time->setText(timeText);
    this->setCentralWidget(centralWidget);
    this->setGeometry(0,0,QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height());
    this->setStyleSheet("QWidget {  background-color : white; }");

}
void MainWindow::sWatchHandler()
{
    if(seconds == 0){
        seconds = 60;
        minutes --;
    }
    if(minutes <= 2)
    {
        time->setStyleSheet("QLabel {  color : red; }");
    }
    seconds --;
    timeVal = new QTime(0,minutes,seconds);
    timeText = timeVal->toString("mm : ss");
    time->setText(timeText);
    if(seconds == 0 && minutes ==0)
    {
        time->setText("Time is Up");
    }
}
void MainWindow::cameraOnPressed(int player)
{
    if(player == 1)
    {
        this->m_player1->play();

    }
    else
    {
        this->m_player2->play();

    }
}
void MainWindow::cameraOffPressed(int player)
{
    if(player == 1)
    {
        this->m_player1->pause();

    }
    else
    {
        this->m_player2->pause();

    }
}
/*void MainWindow::autoBtnPressed()
{
    m_player1->takeSnapshot();
    isAuto = true;
    Topic motors ("Auto", new std_String("T"));
    this->ros->publish(motors);

}
void MainWindow::countCoinsBtnPressed()
{

}
void MainWindow::shapeDetectionBtnPressed()
{

}
void MainWindow::toggleLightOn()
{
    //lightOn->setEnabled(false);
    //lightOff->setEnabled(true);


}
void MainWindow::toggleLightOff()
{
    //lightOff->setEnabled(false);
    //lightOn->setEnabled(true);

}
void MainWindow::updateDepth()
{

}
*/
