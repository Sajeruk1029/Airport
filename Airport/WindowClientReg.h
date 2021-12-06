#ifndef WINDOWCLIENTREG_H
#define WINDOWCLIENTREG_H

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

class WindowClientReg : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowClientReg(QString);
    ~WindowClientReg();

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

    QLineEdit *passportSeries;
    QLineEdit *passportNumber;

    QLineEdit *money;

    QLineEdit *login;
    QLineEdit *password;

    NetworkAPIRequester *requester;

    QValidator *passportSeriesValidator;
    QValidator *passportNumberValidator;
    QValidator *textValidator;
    QValidator *passwordValidator;

    QString Host;
};

#endif // WINDOWCLIENTREG_H
