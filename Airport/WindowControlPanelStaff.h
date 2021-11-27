#ifndef WINDOWCONTROLPANELSTAFF_H
#define WINDOWCONTROLPANELSTAFF_H

#include <QObject>
#include <QWidget>

#include <QGroupBox>

#include <QVBoxLayout>

#include <QPushButton>

#include <QTabWidget>

#include "WindowAirCompany.h"

class WindowControlPanelStaff : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowControlPanelStaff();
    ~WindowControlPanelStaff();

private:
    QVBoxLayout *layout;

    QTabWidget *tabs;

    WindowAirCompany *windowAirCompany;

    /*
    QPushButton *butAirCompanies;
    QPushButton *butAirplanes;
    QPushButton *butStaff;
    QPushButton *butAccounts;
    QPushButton *butServices;
    QPushButton *butPosts;
    QPushButton *butTickets;
    QPushButton *butPlacesOfAirports;
    QPushButton *butClients;
    QPushButton *butBaggage;
    QPushButton *butCargo;
    QPushButton *butCategoriesCargo;
    QPushButton *butFlights;
    */
};

#endif // WINDOWCONTROLPANELSTAFF_H
