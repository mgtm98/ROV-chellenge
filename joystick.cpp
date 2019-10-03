#include "joystick.h"

Joystick::Joystick(QObject *parent):Joystick(0,100,parent){
}

Joystick::Joystick(int id, QObject *parent):Joystick(id,100,parent){
}

Joystick::Joystick(int id, int update_interval, QObject *parent,QRos *ros ,Player *m_player1,Player *m_player2):QObject(parent),id(id){
    this->ros = ros;
    this->m_player1 = m_player1;
    this->m_player2 = m_player2;
    SDL_Init(SDL_INIT_JOYSTICK);
    timer = new QTimer();
    event = new SDL_Event();
    joy = SDL_JoystickOpen(id);
    if(joy == nullptr){
        connected = false;
    }else{
        emit(joyStick_connected());
    }
    connect(timer, SIGNAL(timeout()),this,SLOT(update()));
    timer->setInterval(update_interval);
    timer->start();

    axis_values = new double[4]{0,0,0,0};
}

void Joystick::startListening(){
    timer->start();
}

void Joystick::update(){
    Axis ax = Axis::x_axis;

    while(SDL_PollEvent(event)){
        /*if(event->type == SDL_JOYAXISMOTION){
            if(event->jaxis.axis == x_Axis_id){
                ax = Axis::x_axis;
                axis_values[0] = abs(event->jaxis.value) > DEAD_ZONE ? event->jaxis.value/32768.0 : 0;
            }else if(event->jaxis.axis == y_Axis_id){
                ax = Axis::y_axis;
                axis_values[1] = abs(event->jaxis.value) > DEAD_ZONE ? event->jaxis.value/32768.0 : 0;
            }else if(event->jaxis.axis == z_Axis_id){
                ax = Axis::z_axis;
                axis_values[2] = abs(event->jaxis.value) > DEAD_ZONE ? event->jaxis.value/32768.0 : 0;
            }else if(event->jaxis.axis == r_Axis_id){
                ax = Axis::r_axis;
                axis_values[3] = abs(event->jaxis.value) > DEAD_ZONE ? event->jaxis.value/32768.0 : 0;
            }
            if(ax == Axis::x_axis || ax == Axis::y_axis){
                 axis_Handeler(ax,axis_values[0],axis_values[1]);
            }else{
                 axis_Handeler(ax,axis_values[2],axis_values[3]);
            }
        }else */if(event->type == SDL_JOYBUTTONDOWN){
            qDebug() << "button event";
             button_handeler(event->jbutton.button,true);
        }else if(event->type == SDL_JOYBUTTONUP){
            qDebug() << "button event";
             button_handeler(event->jbutton.button,false);
        }else if(event->type == SDL_JOYDEVICEREMOVED){
            qDebug() << "Disconnected";
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
            emit(joyStick_disconnected());
        }else if(event->type == SDL_JOYDEVICEADDED){
            SDL_InitSubSystem(SDL_INIT_JOYSTICK);
            joy = SDL_JoystickOpen(id);
            if(joy == nullptr){
                connected = false;
            }else{
                emit(joyStick_connected());
                connected = true;
            }
        }
    }
}

bool Joystick::isConnected(){
    return connected;
}
void Joystick::axis_Handeler(Axis ax, double value1, double value2){
}
void Joystick::button_handeler(int button, bool value){
    if(button == shapesBtn)
    {
        this->m_player2->takeSnapshot();

    }
    else if(button == autoBtn)
    {
        this->m_player1->takeSnapshot();
    }
    else if(button == classifierBtn)
    {
        this->m_player2->takeSnapshot();
    }
    else if(button == lightBtn)
    {
    }
}
