#ifndef WINDOWPROFILE_H
#define WINDOWPROFILE_H

#include <QVBoxLayout>

#include <QGridLayout>

#include <QLineEdit>

#include <QPushButton>

#include <QCheckBox>

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

#include <QComboBox>

#include <QLabel>

#include "NetworkAPIRequester.h"
#include "HtmlGenerator.h"
#include "CustomInputWidget.h"

class WindowProfile : public QWidget
{
    Q_OBJECT
public:
    explicit WindowProfile(StaffFull, QString);
    explicit WindowProfile(ClientFull, QString);
    ~WindowProfile();

private slots:
    void onClickSave(void);
    void onClickEnterPassword(void);
    void onClickGeneratedHTML(void);
    void onClickEnterPost(void);

private:
    QVBoxLayout *layout;

    QGridLayout *contaynerLayout;

    QWidget *contayner;

    QLabel *lineHintFirstName;
    QLabel *lineHintLastName;
    QLabel *lineHintPatronymic;

    QLabel *lineHintPostName;

    QLabel *lineHintPassportSeries;
    QLabel *lineHintPassportNumber;

    QLabel *lineHintEducation;

    QLabel*lineHintLogin;

    QLabel *lineHintMoney;

    QLineEdit *lineFirstName;
    QLineEdit *lineLastName;
    QLineEdit *linePatronymic;

    QLineEdit *linePostName;

    QLineEdit *linePassportSeries;
    QLineEdit *linePassportNumber;

    QLineEdit *lineEducation;

    QLineEdit *lineLogin;

    QLineEdit *lineMoney;

    QPushButton *butEnterPassword;
    QPushButton *butSave;
    QPushButton *butGenerateHTML;
    QPushButton *butEnterPost;

    NetworkAPIRequester *requster;

    HTMLGenerator *gen;

    QValidator *validator;
    QValidator *validatorPassportSeries;
    QValidator *validatorPassportNumber;

    StaffFull dataStaffFull;
    ClientFull dataClientFull;

    Staff staff;
    Client client;

    bool isStaff;

    QString Host;
};

#endif // WINDOWPROFILE_H
