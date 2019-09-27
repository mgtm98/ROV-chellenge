#include "joystick.h"
joystick::joystick(QObject *parent) : QObject(parent)
{
    SDL_Init(SDL_INIT_JOYSTICK);


    //Scene textures
    joy  = SDL_JoystickOpen(0);
    if(joy == NULL)
    {
        qDebug() <<"Joy Stick Not connected";
        exit(1);
    }
    qDebug()<<SDL_JoystickNumAxes(joy);
    /*while(1){
        SDL_JoystickUpdate();
        qDebug()<<SDL_JoystickGetAxis(joy,0);
        QThread::sleep(1);

    }*/
    timer = new QTimer();
    timer->setInterval(100);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(joystick_update()));
    // e = new SDL_Event();
    //Clear screen

    //Calculate angle


}
void joystick::joystick_update()
{
    //SDL_JoystickUpdate();
    //qDebug()<< "X= " << SDL_JoystickGetAxis(joy,0);
    /* while(SDL_PollEvent(event))
    {
        if(event->type == SDL_JOYAXISMOTION)
        {
            qDebug()<<"Axis" << event->jaxis.axis << "value= " <<event->jaxis.value;
        }
        else if(event->type == SDL_JOYBUTTONDOWN)
        {
            qDebug()<<"Button" << event->jbutton.button << "presed" ;

        }
    }*/
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        else if( e.type == SDL_JOYAXISMOTION )
        {
            //Motion on controller 0
            if( e.jaxis.which == 0 )
            {
                //X axis motion
                if( e.jaxis.axis == 0 )
                {
                    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE  || e.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        xVal = e.jaxis.value;
                    }
                    else
                    {
                        xVal = 0;
                    }
                }
                else if( e.jaxis.axis == 1 )
                {
                    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE || e.jaxis.value > JOYSTICK_DEAD_ZONE )
                    {
                        yVal = e.jaxis.value;
                    }

                    else
                    {
                        yVal = 0;
                    }
                }
            }
        }
    }
    double joystickAngle = atan2( (double)yVal, (double)xVal ) * ( 180.0 / M_PI );
    qDebug()<<joystickAngle<<endl;
    //Correct angle
    if( xVal == 0 && yVal == 0 )
    {
        joystickAngle = 0;
    }
}
