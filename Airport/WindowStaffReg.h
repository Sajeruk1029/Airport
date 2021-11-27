#ifndef WINDOWSTAFFREG_H
#define WINDOWSTAFFREG_H

#include <QObject>
#include <QWidget>

#include <QGroupBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include <QCryptographicHash>

#include <QDebug>

#include <QMessageBox>

#include <QComboBox>

#include <QValidator>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QRegExp>

#include "NetworkAPIRequester.h"

class WindowStaffReg : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowStaffReg();
    ~WindowStaffReg();

private slots:
    void clickButReg();

private:
    QVBoxLayout *layout;

    QHBoxLayout *layoutButs;

    QWidget *containerButs;

    QPushButton *butReg;

    QLineEdit *firstName;
    QLineEdit *lastName;
    QLineEdit *patronymic;

    QComboBox *postList;

    QLineEdit *passportSeries;
    QLineEdit *passportNumber;

    QTextEdit *education;

    QLineEdit *login;
    QLineEdit *password;

    NetworkAPIRequester *requester;

    QValidator *passportSeriesValidator;
    QValidator *passportNumberValidator;
    QValidator *textValidator;
    QValidator *passwordValidator;
};

#endif // WINDOWSTAFFREG_H
