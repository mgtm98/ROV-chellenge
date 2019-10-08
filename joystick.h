#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QTimer>
#include <exception>
#include <QDebug>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"
#include "ros.h"
#include "player.h"
#include <QLabel>
#include <QProcess>
#include <QApplication>
#include <QMessageBox>
#include <QFile>

#define x_Axis_id 0
#define y_Axis_id 1
#define z_Axis_id 2
#define r_Axis_id 3
#define DEAD_ZONE 4000

enum Axis{
    x_axis,
    y_axis,
    z_axis,
    r_axis
};

class Joystick:public QObject{
    Q_OBJECT

public:
    explicit Joystick(QObject *parent = nullptr);
    explicit Joystick(int id, QObject *parent = nullptr);
    explicit Joystick(int id, int update_interval,QObject *parent = nullptr,QRos *ros = nullptr,
                      Player *m_player1= nullptr,Player *m_player2= nullptr, QLabel * coins = nullptr, QLabel * isTrap = nullptr);
    void startListening();
    bool isConnected();
    void axis_Handeler(Axis ax, double value1, double value2);
    void button_handeler(int button, bool value);
    QString runProcess(QStringList params);
    int              *btns;//0 auto 1 shapes 2 clasifier 3 light 4 openbox 5 openlock 6 cam
private:
    SDL_Joystick    *joy;
    SDL_Event       *event;
    QTimer          *timer;
    int              id;
    bool             connected;
    bool             lightFlag = false;
    bool             camFlag = false;
    double           *axis_values;
    int              shapesBtn = 1;
    int              autoBtn = 0;
    int              classifierBtn = 2;
    int              lightBtn = 3;
    int              openBoxBtn = 4;
    int              openlockBtn = 5;
    int              camBtn = 6;
    QRos             *ros;
    Player           *m_player1, *m_player2;
    QLabel           *isTrap, *coins;



private slots:
    void update();
};


#endif // JOYSTICK_H
