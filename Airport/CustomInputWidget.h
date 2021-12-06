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
#include <QListWidget>

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
#include "BaggageAndTicketsAndServices.h"
#include "CargoAndTickets.h"

#include "NetworkAPIRequester.h"

class CustomInputWidget : public QObject
{
    Q_OBJECT
public:
    explicit CustomInputWidget(void);

    static Accounts getAccounts(QString, bool, bool&, QWidget * = nullptr);
    static QString getPassword(QString, bool&, bool, QWidget * = nullptr);
    static AirCompany getAirCompany(QString, bool&, QWidget * = nullptr);
    static AirCompanyAndAirplane getAirCompanyAndAirplane(QString, bool&, QString, QWidget * = nullptr);
    static AirCompanyAndServices getAirCompanyAndServices(QString, bool&, QString, QWidget * = nullptr);
    static Airplane getAirplane(QString, bool&, QWidget * = nullptr);
    static Baggage getBaggage(QString, bool&, QWidget * = nullptr);
    static CargoAndTickets getCargoAndTickets(QString, bool&, QString, QWidget * = nullptr);
    static CargoAndTickets getCargoAndTickets(QString, bool&, QString, unsigned int, QWidget * = nullptr);
    static CategoriesCargo getCategoriesCargo(QString, bool&, QWidget * = nullptr);
    static ClientAndAccounts getClientAndAccounts(QString, bool&, bool, QWidget * = nullptr);
    static ClientAndBaggage getClientAndBaggage(QString, bool&, QString, QWidget * = nullptr);
    static Flights getFlights(QString, bool&, QString, QWidget * = nullptr);
    static PlacesOfAirports getPlacesOfAirport(QString, bool&, QWidget * = nullptr);
    static Post getPost(QString, bool&, QWidget * = nullptr);
    static Post getPost(QString, bool&, QString, QWidget * = nullptr);
    static Services getServices(QString, bool&, QWidget * = nullptr);
    static StaffAndAccounts getStaffAndAccounts(QString, bool&, QString, bool, QWidget * = nullptr);
    static BaggageAndTicketsAndServices getBaggageAndTicketsAndServices(QString, bool&, QString, QWidget * = nullptr);
    static BaggageAndTicketsAndServices getBaggageAndTicketsAndServices(QString, bool&, QString, unsigned int, QWidget * = nullptr);
    static TicketsAndServices getTicketsAndServices(QString, bool&, QString, QWidget * = nullptr);

};

#endif // CUSTOMINPUTWIDGET_H
