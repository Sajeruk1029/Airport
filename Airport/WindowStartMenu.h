#ifndef WINDOWSTARTMENU_H
#define WINDOWSTARTMENU_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>

#include <QGroupBox>

#include <QPushButton>

#include "WindowStaffLogin.h"
#include "WindowClientLogin.h"

class WindowStartMenu : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowStartMenu(QString);
    ~WindowStartMenu();

private:    
    QVBoxLayout *layout;

    QPushButton *buttonClient;
    QPushButton *buttonStaff;

    WindowStaffLogin *windowStaffLogin;
    WindowClientLogin *windowClientLogin;

    QString Host;
private slots:
    void clickButClient();
    void clickButStaff();

};

#endif // WINDOWSTARTMENU_H
