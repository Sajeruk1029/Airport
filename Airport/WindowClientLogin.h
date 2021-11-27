#ifndef WINDOWCLIENTLOGIN_H
#define WINDOWCLIENTLOGIN_H

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

#include "WindowClientReg.h"

class WindowClientLogin : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowClientLogin();
    ~WindowClientLogin();

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

    WindowClientReg *windowClientReg;

};

#endif // WINDOWCLIENTLOGIN_H
