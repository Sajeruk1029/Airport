#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QTextDocumentFragment>

#include <QTextCursor>

#include <QTextTable>
#include <QTextTableCell>
#include <QTextTableFormat>

#include <QString>

#include <QFile>

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

#include "AirCompanyAndAirplaneFull.h"
#include "AirCompanyAndAirplaneTrunc.h"
#include "AirCompanyAndServicesFull.h"
#include "AirCompanyAndServicesTrunc.h"
#include "CargoFull.h"
#include "CargoTrunc.h"
#include "ClientAndBaggageFull.h"
#include "ClientAndBaggageTrunc.h"
#include "FlightsFull.h"
#include "FlightsTrunc.h"
#include "StaffFull.h"
#include "StaffTrunc.h"
#include "TicketsAndServicesFull.h"
#include "TicketsAndServicesTrunc.h"
#include "TicketsFull.h"
#include "TicketsTrunc.h"
#include "ClientFull.h"

#include <QDebug>

class HTMLGenerator
{
public:
    explicit HTMLGenerator(QString);
    ~HTMLGenerator(void);

    void createHTMLFile(int);
    void saveHTMLFile(void);

    void addCaptionTable(QStringList);

    void addLineTable(Accounts);
    void addLineTable(AirCompany);
    void addLineTable(Airplane);
    void addLineTable(Baggage);
    void addLineTable(Cargo);
    void addLineTable(CategoriesCargo);
    void addLineTable(Client);
    void addLineTable(Flights);
    void addLineTable(PlacesOfAirports);
    void addLineTable(Post);
    void addLineTable(Services);
    void addLineTable(Staff);
    void addLineTable(Tickets);

    void addLineTable(AirCompanyAndAirplaneFull);
    void addLineTable(AirCompanyAndAirplaneTrunc);
    void addLineTable(AirCompanyAndServicesFull);
    void addLineTable(AirCompanyAndServicesTrunc);
    void addLineTable(CargoFull);
    void addLineTable(CargoTrunc);
    void addLineTable(ClientAndBaggageFull);
    void addLineTable(ClientAndBaggageTrunc);
    void addLineTable(FlightsFull);
    void addLineTable(FlightsTrunc);
    void addLineTable(StaffFull);
    void addLineTable(StaffTrunc);
    void addLineTable(TicketsAndServicesFull);
    void addLineTable(TicketsAndServicesTrunc);
    void addLineTable(TicketsFull);
    void addLineTable(TicketsTrunc);
    void addLineTable(ClientFull);

private:
    QTextDocumentWriter *writer;

    QTextDocument *document;

    QTextCursor *cursor;

    QTextTable *table;

    QFile *file;
};

#endif // HTMLGENERATOR_H
