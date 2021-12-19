#ifndef WINDOWFLIGHTS_H
#define WINDOWFLIGHTS_H

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

#include <QHeaderView>

#include "NetworkAPIRequester.h"
#include "HtmlGenerator.h"
#include "CustomInputWidget.h"

class WindowFlights : public QWidget
{
    Q_OBJECT
public:
    explicit WindowFlights(QString);
    ~WindowFlights();

private slots:
    void onClickSearch(void);
    void onClickRefresh(void);
    void onClickAdd(void);
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
    QPushButton *butGenerateTable;

    QTableWidget *table;

    QValidator *validator;

    QCheckBox *deleted;

    NetworkAPIRequester *requester;

    HTMLGenerator *gen;

    QString Host;
};

#endif // WINDOWFLIGHTS_H
