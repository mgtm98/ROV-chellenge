#ifndef BUTTONSETTINGS_H
#define BUTTONSETTINGS_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class ButtonSettings;
}

class ButtonSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ButtonSettings(QWidget *parent = nullptr,int btns[12] = nullptr);
    ~ButtonSettings();

private slots:
    void on_buttonBox_clicked();
private:
    Ui::ButtonSettings *ui;
    int *btns;
};

#endif // BUTTONSETTINGS_H
