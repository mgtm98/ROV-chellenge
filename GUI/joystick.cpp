#include "joystick.h"

Joystick::Joystick(QObject *parent):Joystick(0,100,parent){
}

Joystick::Joystick(int id, QObject *parent):Joystick(id,100,parent){
}

Joystick::Joystick(int id, int update_interval, QObject *parent,QRos *ros ,
                   Player *m_player1,Player *m_player2, QLabel *coins,QLabel *isTrap):QObject(parent),id(id){
    this->ros = ros;
    this->coins = coins;
    this->isTrap = isTrap;
    this->m_player1 = m_player1;
    this->m_player2 = m_player2;
    SDL_Init(SDL_INIT_JOYSTICK);
    timer = new QTimer();
    event = new SDL_Event();
    joy = SDL_JoystickOpen(id);
    if(joy == nullptr){
        connected = false;
    }
    connect(timer, SIGNAL(timeout()),this,SLOT(update()));
    timer->setInterval(update_interval);
    timer->start();

    axis_values = new double[4]{0,0,0,0};
    btns = new int[12]{0,1,2,3,4,5,6};
}

void Joystick::startListening(){
    timer->start();
}

void Joystick::update(){
    Axis ax = Axis::x_axis;

    while(SDL_PollEvent(event)){
        if(event->type == SDL_JOYAXISMOTION){
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
        }else if(event->type == SDL_JOYBUTTONDOWN){
            qDebug() << "button event";
             button_handeler(event->jbutton.button,true);
        }else if(event->type == SDL_JOYBUTTONUP){
            qDebug() << "button event";
             button_handeler(event->jbutton.button,false);
        }else if(event->type == SDL_JOYDEVICEREMOVED){
            qDebug() << "Disconnected";
            QMessageBox msgBox;
            msgBox.setText("Joystick Disconnected!");
            msgBox.exec();
        }else if(event->type == SDL_JOYDEVICEADDED){
            SDL_InitSubSystem(SDL_INIT_JOYSTICK);
            joy = SDL_JoystickOpen(id);
        }
    }
}

bool Joystick::isConnected(){
    return connected;
}
void Joystick::axis_Handeler(Axis ax, double value1, double value2){
       if((ax == Axis::x_axis || ax == Axis::y_axis) && !camFlag)
       {
           Topic t ("control", new pln_motion(value1,value2));
           this->ros->publish(t);
       }
       else if (ax == Axis::z_axis && !camFlag)
       {
           Topic t ("altitude", new z_motion(value1));
           this->ros->publish(t);
       }
       else if((ax == Axis::x_axis || ax == Axis::y_axis) && camFlag)
       {
           Topic t ("camera", new camera_msg(0,"move",(int)value1,(int)value2));
           this->ros->publish(t);
       }
       else if ((ax == Axis::z_axis || ax == Axis::r_axis) && camFlag)
       {
           Topic t ("camera", new camera_msg(1,"move",(int)value1,(int)value2));
           this->ros->publish(t);
       }

}
void Joystick::button_handeler(int button, bool value){
    if(button == btns[1])//shape
    {
        this->m_player1->takeSnapshot("shapes.jpeg");
        QStringList params = { "img.py", "--image",  "test.jpeg","--line", "0", "--triangle", "1", "--square", "3", "--circle", "1"  };
        QString out = runProcess(params);
        this->isTrap->setText(out);
    }
    else if(button == btns[0]) //auto
    {
    }
    else if(button == btns[2]) //classifier
    {
        this->m_player2->takeSnapshot("classifier.jpeg");
    }
    else if(button == btns[3]) //light
    {   if(lightFlag)
        {
            Topic t ("lights", new std_String("off"));
            this->ros->publish(t);
        }
        else
        {
            Topic t ("lights", new std_String("on"));
            this->ros->publish(t);
        }
        lightFlag = !lightFlag;

    }
    else if(button == btns[6] && value) //cam
    {
        camFlag = true;
    }
    else if(button == btns[6] && !value)
    {
        camFlag = false;
    }

}
QString Joystick::runProcess(QStringList params)
{
    QString output;
    QString path = QCoreApplication::applicationDirPath();
    QProcess *proc = new QProcess();
    proc->startDetached("python3", params,path);
    proc->waitForFinished(-1);
    QFile inputFile("out.txt");
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while(!in.atEnd())
        {
             output = in.readLine();
        }
    }
    inputFile.close();

    return  output;
}
