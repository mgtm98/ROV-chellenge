#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include "joystick.h"
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QProcess>
#include <QGridLayout>
#include <QLineEdit>
#include "ros.h"
#include "msg.h"
#include "topic.h"
#include "player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,QRos *ros = nullptr);
    void initItems();
    void gstream();
    ~MainWindow();

private:
    QPushButton /**automationBtn,*coinsBtn,*shapeDetectionBtn,*lightOn,*lightOff,*updateDepthBtn,*/*camera1OffBtn,*camera1OnBtn,*camera2OffBtn,*camera2OnBtn;
    QLabel * coinNotxt,*coinNo,*adjustDepth,*camera1,*camera2;
    QLabel * sensorReadings,*depth,/**mode,*/*temp,*tempValue,*depthValue/*,*light,*up,*down,*/,*buttonSettings,*time,*sWatch;
   // QLineEdit *editDepth,*fix;
    QWidget *centralWidget;
    QVBoxLayout * verLeftLayout,*verRightLayout;
    QHBoxLayout * horLayout , /**lightBtnslayout, *depthLayout,*/*cameraLayout1,*cameraLayout2;
    //QGridLayout * btnLayout;
    int seconds=0,minutes=2,coins=0;
    double depthVal=0.0,tempVal=0.0;
    Joystick * my_joy;
    QTimer *timer;
    QTime *timeVal;
    QString timeText;
    QVideoWidget *videoWidget;
    QMediaPlayer *player ;
    QProcess *process ;
    bool isAuto = false,istrap = false, isMetal = false;
    QRos *ros;
    Player *m_player1, *m_player2;
private slots:
    void sWatchHandler();
    void autoBtnPressed();
    void countCoinsBtnPressed();
    void shapeDetectionBtnPressed();
    void toggleLightOn();
    void toggleLightOff();
    void updateDepth();

};

#endif // MAINWINDOW_H
