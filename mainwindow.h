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

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initItems();
    void gstream();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton * automationBtn,*coinsBtn,*shapeDetectionBtn;
    QLabel * sensorReadings,*depth,*mode,*temp,*tempValue,*depthValue,*light,*up,*down,*buttonSettings,*time;
    QLabel *min2,*sec1,*sec2,*min1,*separator;
    QWidget *centralWidget;
    QVBoxLayout * verLeftLayout,*verRightLayout;
    QHBoxLayout * horLayout,*timerLayout;
    unsigned int seconds=0,minutes=0;
    joystick * my_joy;

    QVideoWidget *videoWidget;
    QMediaPlayer *player ;
    QProcess *process ;

};

#endif // MAINWINDOW_H
