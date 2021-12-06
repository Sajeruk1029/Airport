#ifndef WINDOWCONTROLPANELSTAFF_H
#define WINDOWCONTROLPANELSTAFF_H

#include <QObject>
#include <QWidget>

#include <QGroupBox>

#include <QVBoxLayout>

#include <QPushButton>

#include <QTabWidget>

#include "WindowAirCompany.h"
#include "WindowAirplane.h"
#include "WindowServices.h"
#include "WindowPost.h"
#include "WindowTickets.h"
#include "WindowPlacesOfAirports.h"
#include "WindowCategoriesCargo.h"
#include "WindowFlights.h"
#include "WindowProfile.h"

class WindowControlPanelStaff : public QGroupBox
{
    Q_OBJECT
public:
    explicit WindowControlPanelStaff(StaffFull, QString);
    ~WindowControlPanelStaff();

private:
    QVBoxLayout *layout;

    QTabWidget *tabs;

    WindowAirCompany *windowAirCompany;
    WindowAirplane *windowAirplane;
    WindowServices *windowServices;
    WindowPost *windowPost;
    WindowTickets *windowTickets;
    WindowPlacesOfAirports *windowPlacesOfAirports;
    WindowCategoriesCargo *windowCategoriesCargo;
    WindowFlights *windowFlights;
    WindowProfile *windowProfile;

    QString Host;

    /*
    QPushButton *butAirCompanies;+
    QPushButton *butAirplanes;+
    QPushButton *butStaff;-
    QPushButton *butAccounts;
    QPushButton *butServices;+
    QPushButton *butPosts;+
    QPushButton *butTickets;+
    QPushButton *butPlacesOfAirports;+
    QPushButton *butClients;-
    QPushButton *butBaggage;-
    QPushButton *butCargo;-
    QPushButton *butCategoriesCargo;-
    QPushButton *butFlights;+
    */
};

#endif // WINDOWCONTROLPANELSTAFF_H
