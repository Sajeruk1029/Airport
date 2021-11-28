#ifndef CUSTOMINPUTWIDGET_H
#define CUSTOMINPUTWIDGET_H

#include <QObject>

#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLineEdit>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>

#include <QValidator>
#include <QIntValidator>
#include <QRegExpValidator>

#include <QRegExp>

#include <QMessageBox>

#include <QEventLoop>
#include <QEvent>

#include <QList>

#include "Accounts.h"
#include "AirCompany.h"
#include "AirCompanyAndAirplane.h"
#include "AirCompanyAndServices.h"
#include "Airplane.h"
#include "Baggage.h"
#include "Cargo.h"
#include "CategoriesCargo.h"
#include "Client.h"
#include "ClientAndBaggage.h"
#include "Flights.h"
#include "PlacesOfAirports.h"
#include "Post.h"
#include "Services.h"
#include "Staff.h"
#include "Tickets.h"
#include "TicketsAndServices.h"

#include "ClientAndAccounts.h"
#include "StaffAndAccounts.h"

#include "NetworkAPIRequester.h"

class CustomInputWidget : public QObject
{
    Q_OBJECT
public:
    explicit CustomInputWidget(void);

    static Accounts getAccounts(QString, bool, bool&, QWidget * = nullptr);
    static AirCompany getAirCompany(QString, bool&, QWidget *);
    static AirCompanyAndAirplane getAirCompanyAndAirplane(QString, bool&, QString, QWidget *);
    static AirCompanyAndServices getAirCompanyAndServices(QString, bool&, QString, QWidget *);
    static Airplane getAirplane(QString, bool&, QWidget *);
    static Baggage getBaggage(QString, bool&, QWidget *);
    static Cargo getCargo(QString, bool&, QString, QWidget *);
    static CategoriesCargo getCategoriesCargo(QString, bool&, QWidget *);
    static ClientAndAccounts getClientAndAccounts(QString, bool&, QWidget *, bool);
    static ClientAndBaggage getClientAndBaggage(QString, bool&, QString, QWidget *);
    static Flights getFlights(QString, bool&, QString, QWidget *);
    static PlacesOfAirports getPlacesOfAirport(QString, bool&, QWidget *);
    static Post getPost(QString, bool&, QWidget *);
    static Services getServices(QString, bool&, QWidget *);
    static StaffAndAccounts getStaffAndAccounts(QString, bool&, QString, QWidget *, bool);
    static Tickets getTickets(QString, bool&, QString, QWidget *);
    static TicketsAndServices getTicketsAndServices(QString, bool&, QString, QWidget *);

};

#endif // CUSTOMINPUTWIDGET_H
