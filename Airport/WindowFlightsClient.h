#ifndef WINDOWFLIGHTSCLIENT_H
#define WINDOWFLIGHTSCLIENT_H

#include <QVBoxLayout>

#include <QHBoxLayout>

#include <QLineEdit>

#include <QTableWidget>

#include <QPushButton>

#include <QCheckBox>

#include <QValidator>
#include <QRegExpValidator>

#include <QMessageBox>

#include <QInputDialog>

#include <QFile>
#include <QFileDialog>

#include "NetworkAPIRequester.h"
#include "HtmlGenerator.h"
#include "CustomInputWidget.h"

class WindowFlightsClient : public QWidget
{
    Q_OBJECT
public:
    explicit WindowFlightsClient(QString);
    ~WindowFlightsClient();

private slots:
    void onClickSearch(void);
    void onClickRefresh(void);
    void onClickGeneratedHTML(void);

private:

    void refreshTable(void);

    QVBoxLayout *layout;

    QHBoxLayout *layoutContaner;

    QWidget *container;

    QLineEdit *search;

    QPushButton *butSearch;
    QPushButton *butRefresh;
    QPushButton *butGenerateTable;

    QTableWidget *table;

    QValidator *validator;

    NetworkAPIRequester *requester;

    HTMLGenerator *gen;

    QString Host;
};

#endif // WINDOWFLIGHTSCLIENT_H
