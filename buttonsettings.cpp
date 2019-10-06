#include "buttonsettings.h"
#include "ui_buttonsettings.h"

ButtonSettings::ButtonSettings(QWidget *parent, int btns[12]) :
    QDialog(parent),
    ui(new Ui::ButtonSettings)
{
    this->btns = btns;
    ui->setupUi(this);
    connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(on_buttonBox_clicked()));

    ui->lineEdit->setText(QString::number(btns[0]));
    ui->lineEdit_2->setText(QString::number(btns[1]));
    ui->lineEdit_3->setText(QString::number(btns[2]));
    ui->lineEdit_4->setText(QString::number(btns[3]));
    ui->lineEdit_5->setText(QString::number(btns[4]));
    ui->lineEdit_6->setText(QString::number(btns[5]));

}

ButtonSettings::~ButtonSettings()
{
    delete ui;
}

void ButtonSettings::on_buttonBox_clicked()
{
    int tempArr[12];
    bool okFlag = true;
    tempArr[0] = ui->lineEdit->text().toInt();
    tempArr[1]  = ui->lineEdit_2->text().toInt();
    tempArr[2]  = ui->lineEdit_3->text().toInt();
    tempArr[3]= ui->lineEdit_4->text().toInt();
    tempArr[4]= ui->lineEdit_5->text().toInt();
    tempArr[5] = ui->lineEdit_6->text().toInt();

    for(int i=0;i <6;i++)
    {
        if(tempArr[i]>12 || tempArr[i]<0)
        {
            okFlag = false;
            QMessageBox msgBox;
            msgBox.setText("Please enter numbers between 0 and 12");
            msgBox.exec();

        }
        for(int j=i+1;j<5;j++)
        {
            if(tempArr[i] == tempArr[j])
            {
                okFlag = false;
                QMessageBox msgBox;
                msgBox.setText("Two or more buttons have the same value");
                msgBox.exec();
            }
        }
    }
    if(okFlag)
    {
        for(int i=0;i<12;i++)
        {
            btns[i] = tempArr[i];
        }
        this->close();
    }
}
