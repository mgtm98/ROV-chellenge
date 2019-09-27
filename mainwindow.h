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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initItems();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton * automationBtn,*coinsBtn,*shapeDetectionBtn;
    QLabel * sensorReadings,*depth,*mode,*temp,*tempValue,*depthValue,*light,*up,*down,*buttonSettings,*time;
    QLabel *stopWatch;
    QWidget *centralWidget;
    QVBoxLayout * verLeftLayout,*verRightLayout;
    QHBoxLayout * horLayout;
    int seconds=0,minutes=20;
    joystick * my_joy;
    QTimer *timer;
    QTime *timeVal;
    QString timeText;
private slots:
    void sWatchHandler();
};

#endif // MAINWINDOW_H
