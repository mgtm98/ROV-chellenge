#ifndef JOYSTICKCLASS_H
#define JOYSTICKCLASS_H

#include <QObject>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"
#include "QDebug"
#include <QThread>
#include <QTimer>
const int JOYSTICK_DEAD_ZONE = 8000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
class joystick : public QObject
{
    Q_OBJECT
private:
    SDL_Joystick * joy;
    QTimer * timer;
    SDL_Event  e;
    bool quit = false;
    int xVal = 0;
    int yVal = 0;
public:
    explicit joystick(QObject *parent = nullptr);

signals:

public slots:
    void joystick_update();

};

#endif // JOYSTICKCLASS_H
