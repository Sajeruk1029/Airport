#ifndef WINDOWAIRCOMPANY_H
#define WINDOWAIRCOMPANY_H

#include <QObject>
#include <QWidget>

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

class WindowAirCompany : public QWidget
{
    Q_OBJECT
public:
    explicit WindowAirCompany();
    ~WindowAirCompany();

private slots:
    void onClickSearch();
    void onClickRefresh();
    void onClickAdd();
    void onClickGeneratedHTML();

private:

    void refreshTable();

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
};

#endif // WINDOWAIRCOMPANY_H
