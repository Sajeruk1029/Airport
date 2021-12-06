#ifndef WINDOWTICKETSCLIENT_H
#define WINDOWTICKETSCLIENT_H

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

class WindowTicketsClient : public QWidget
{
    Q_OBJECT
public:
    explicit WindowTicketsClient(ClientFull, QString);
    ~WindowTicketsClient();

private slots:
    void onClickSearch(void);
    void onClickRefresh(void);
    void onClickAdd(void);
    void onClickAddCargo(void);
    void onClickGeneratedHTML(void);

private:

    void refreshTable(void);

    QVBoxLayout *layout;

    QHBoxLayout *layoutContaner;

    QWidget *container;

    QLineEdit *search;

    QPushButton *butSearch;
    QPushButton *butRefresh;
    QPushButton *butAdd;
    QPushButton *butAddCargo;
    QPushButton *butGenerateTable;

    QTableWidget *table;

    QValidator *validator;

    NetworkAPIRequester *requester;

    HTMLGenerator *gen;

    ClientFull dataClientFull;

    QString Host;
};

#endif // WINDOWTICKETSCLIENT_H
