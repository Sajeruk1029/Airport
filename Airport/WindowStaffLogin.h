#ifndef WINDOWSTAFFLOGIN_H
#define WINDOWSTAFFLOGIN_H

#include <QObject>
#include <QWidget>

#include <QGroupBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLineEdit>

#include <QCryptographicHash>

#include <QDebug>

#include <QMessageBox>

#include "NetworkAPIRequester.h"
#include "WindowStaffReg.h"
#include "WindowControlPanelStaff.h"

class WindowStaffLogin : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowStaffLogin();
    ~WindowStaffLogin();

private slots:
    void clickButLogin();
    void clickButReg();

private:
    QVBoxLayout *layout;

    QHBoxLayout *layoutButs;

    QWidget *containerButs;

    QPushButton *butReg;
    QPushButton *butLogin;

    QLineEdit *login;
    QLineEdit *password;

    NetworkAPIRequester *requester;

    WindowStaffReg *windowStaffReg;

    WindowControlPanelStaff *windowControlPanelStaff;
};

#endif // WINDOWSTAFFLOGIN_H
