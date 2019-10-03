#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QTimer>
#include <exception>
#include <QDebug>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"

#define x_Axis_id 0
#define y_Axis_id 1
#define z_Axis_id 2
#define r_Axis_id 3
#define DEAD_ZONE 100

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
    explicit Joystick(int id, int update_interval, QObject *parent = nullptr);
    void startListening();
    bool isConnected();

private:
    SDL_Joystick    *joy;
    SDL_Event       *event;
    QTimer          *timer;
    int              id;
    bool             connected;
    double             *axis_values;

signals:
//    void axis_Handeler(Axis ax,int value);
    void axis_Handeler(Axis ax, double value1, double value2);
    void button_handeler(int buuton, bool value);
    void joyStick_connected();
    void joyStick_disconnected();

private slots:
    void update();
};


#endif // JOYSTICK_H
