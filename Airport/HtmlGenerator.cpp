#include "HtmlGenerator.h"

HTMLGenerator::HTMLGenerator(QString path) : file(new QFile(path)){}

HTMLGenerator::~HTMLGenerator()
{
    if(writer){ delete writer; }
    if(file){ delete file; }
    if(cursor){ delete cursor; }
    if(document){ delete document; }
}

void HTMLGenerator::createHTMLFile(int columnNumber)
{
    writer = new QTextDocumentWriter();

    document = new QTextDocument();
    cursor = new QTextCursor(document);

    file->open(QIODevice::WriteOnly);

    writer->setDevice(file);

    writer->setFormat("HTML");

    cursor->movePosition(QTextCursor::Start);

    table = cursor->insertTable(1, columnNumber);
}

void HTMLGenerator::saveHTMLFile()
{
    writer->write(document);
    table->deleteLater();
    file->close();
}

void HTMLGenerator::addCaptionTable(QStringList headers)
{
    for(int counter = 0; counter < headers.size(); ++counter)
    {
        table->cellAt(0, counter).firstCursorPosition().insertText(headers.at(counter));
    }
}

void HTMLGenerator::addLineTable(Accounts accounts)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(accounts.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(accounts.getLogin());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(accounts.getPassword());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(accounts.getIsDeleted()));
}

void HTMLGenerator::addLineTable(AirCompany airCompany)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airCompany.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airCompany.getName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(airCompany.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Airplane airplane)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airplane.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airplane.getDescription());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(airplane.getMaxSizeCargo()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(airplane.getMaxWeightCargo()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(airplane.getMaxSeatPlaces()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(airplane.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Baggage baggage)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(baggage.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(baggage.getName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(baggage.getDescription());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(baggage.getWeight()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(baggage.getSize()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(baggage.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Cargo cargo)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(cargo.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(cargo.getIdCategory()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(cargo.getWeight()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(cargo.getDescription());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(cargo.getIdTicket()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(cargo.getSize()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(cargo.getIsDeleted()));
}

void HTMLGenerator::addLineTable(CategoriesCargo categoriesCargo)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(categoriesCargo.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(categoriesCargo.getName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(categoriesCargo.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Client client)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(client.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(client.getFirstName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(client.getLastName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(client.getPatronymic());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(client.getPassportSeries()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(client.getPassportNumber()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(client.getAccount()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(client.getMoney()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(client.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Flights flights)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(flights.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(flights.getDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(flights.getArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(flights.getDeparturePoint()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(flights.getArrivalPoint()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(flights.getAirplane()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(flights.getLadder()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(flights.getIsDeleted()));
}

void HTMLGenerator::addLineTable(PlacesOfAirports placesOfAirports)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(placesOfAirports.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(placesOfAirports.getCountry());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(placesOfAirports.getCity());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(placesOfAirports.getStreet());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(placesOfAirports.getHouseNumber()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(placesOfAirports.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Post post)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(post.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(post.getName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(post.getSalary()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(post.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Services services)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(services.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(services.getName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(services.getDescription());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(services.getPrice()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(services.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Staff staff)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(staff.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(staff.getFirstName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(staff.getLastName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(staff.getPatronymic());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(staff.getPost()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(staff.getPassportSeries()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(staff.getPassportNumber()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(staff.getAccount()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(staff.getEducation());
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(QString::number(staff.getIsDeleted()));
}

void HTMLGenerator::addLineTable(Tickets tickets)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(tickets.getId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(tickets.getPrice()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(tickets.getIdClient()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(tickets.getSeatNumber()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(tickets.getFlights()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(tickets.getBaggageAvailable()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(tickets.getBaggage()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(tickets.getIsDeleted()));
}

void HTMLGenerator::addLineTable(AirCompanyAndAirplaneFull airCompanyAndAirplaneFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneFull.getAirplaneId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airCompanyAndAirplaneFull.getAirplaneName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(airCompanyAndAirplaneFull.getAirplaneDescription());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneFull.getAirplaneMaxSizeCargo()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneFull.getAirplaneMaxWeightCargo()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneFull.getAirplaneMaxSeatPlaces()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(airCompanyAndAirplaneFull.getAirCompanyName());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneFull.getAirplaneIsDeleted()));
}

void HTMLGenerator::addLineTable(AirCompanyAndAirplaneTrunc airCompanyAndAirplaneTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneTrunc.getAirplaneId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airCompanyAndAirplaneTrunc.getAirplaneName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(airCompanyAndAirplaneTrunc.getAirCompanyName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(airCompanyAndAirplaneTrunc.getAirplaneIsDeleted()));
}

void HTMLGenerator::addLineTable(AirCompanyAndServicesFull airCompanyAndServicesFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airCompanyAndServicesFull.getServicesId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airCompanyAndServicesFull.getServiceName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(airCompanyAndServicesFull.getServiceDescription());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(airCompanyAndServicesFull.getServicePrice()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(airCompanyAndServicesFull.getAirCompanyName());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(airCompanyAndServicesFull.getServicesIsDeleted()));
}

void HTMLGenerator::addLineTable(AirCompanyAndServicesTrunc airCompanyAndServicesTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(airCompanyAndServicesTrunc.getServicesId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(airCompanyAndServicesTrunc.getServiceName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(airCompanyAndServicesTrunc.getServicePrice()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(airCompanyAndServicesTrunc.getAirCompanyName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(airCompanyAndServicesTrunc.getServicesIsDeleted()));
}

void HTMLGenerator::addLineTable(CargoFull cargoFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(cargoFull.getCargoId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(cargoFull.getCargoDescription());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(cargoFull.getCargoWeight()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(cargoFull.getCargoSize()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(cargoFull.getClientFirstName());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(cargoFull.getClientLastName());
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(cargoFull.getClientPatronymic());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(cargoFull.getClientPassportSeries()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(cargoFull.getClientPassportNumber()));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(cargoFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:dd:ss"));
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(cargoFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:dd:ss"));
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(cargoFull.getDeparturePoint());
    table->cellAt(table->rows() - 1, 12).firstCursorPosition().insertText(cargoFull.getArrivalPoint());
    table->cellAt(table->rows() - 1, 13).firstCursorPosition().insertText(QString::number(cargoFull.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 14).firstCursorPosition().insertText(QString::number(cargoFull.getCargoIsDeleted()));
}

void HTMLGenerator::addLineTable(CargoTrunc cargoTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(cargoTrunc.getCargoId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(cargoTrunc.getCargoDescription());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(QString::number(cargoTrunc.getCargoWeight()));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(cargoTrunc.getCargoSize()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(cargoTrunc.getCategoriesCargoName());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(cargoTrunc.getClientFirstName());
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(cargoTrunc.getClientLastName());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(cargoTrunc.getClientPatronymic());
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(cargoTrunc.getCargoIsDeleted()));
}

void HTMLGenerator::addLineTable(ClientAndBaggageFull clientAndBaggageFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getBaggageId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(clientAndBaggageFull.getBaggageName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(clientAndBaggageFull.getBaggageDescription());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getBaggageWeight()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getBaggageSize()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(clientAndBaggageFull.getClientFirstName());
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(clientAndBaggageFull.getClientLastName());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(clientAndBaggageFull.getClientPatronymic());
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getClientPassportSeries()));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getClientPassportNumber()));
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(QString::number(clientAndBaggageFull.getBaggageIsDeleted()));
}

void HTMLGenerator::addLineTable(ClientAndBaggageTrunc clientAndBaggageTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(clientAndBaggageTrunc.getBaggageId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(clientAndBaggageTrunc.getBaggageName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(clientAndBaggageTrunc.getClientFirstName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(clientAndBaggageTrunc.getClientLastName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(clientAndBaggageTrunc.getClientPatronymic());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(clientAndBaggageTrunc.getBaggageIsDeleted()));
}

void HTMLGenerator::addLineTable(ClientFull clientFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(clientFull.getClientId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(clientFull.getClientFirstName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(clientFull.getClientLastName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(clientFull.getClientPatronymic());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(clientFull.getClientPassportSeries()));
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(clientFull.getClientPassportNumber()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(clientFull.getAccountLogin());
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(clientFull.getAccountPassword());
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(QString::number(clientFull.getClientMoney()));
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(QString::number(clientFull.getClientIsDeleted()));
}

void HTMLGenerator::addLineTable(FlightsFull flightsFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(flightsFull.getFlightsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(flightsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(flightsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(flightsFull.getDeparturePoint());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(flightsFull.getArrivalPoint());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(flightsFull.getAirplaneName());
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(flightsFull.getAirplaneDescription());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(flightsFull.getAirplaneMaxSizeCargo()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(flightsFull.getAirplaneMaxWeightCargo()));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(QString::number(flightsFull.getAirplaneMaxSeatPlaces()));
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(QString::number(flightsFull.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(QString::number(flightsFull.getFlightsIsDeleted()));
}

void HTMLGenerator::addLineTable(FlightsTrunc flightsTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(flightsTrunc.getFlightsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(flightsTrunc.getArrivalPoint());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(QString::number(flightsTrunc.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(QString::number(flightsTrunc.getFlightsIsDeleted()));
}

void HTMLGenerator::addLineTable(StaffFull staffFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(staffFull.getStaffId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(staffFull.getStaffFirstName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(staffFull.getStaffLastName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(staffFull.getStaffFirstName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(staffFull.getPostName());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(staffFull.getPostSalary()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(staffFull.getStaffPassportSeries()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(staffFull.getStaffPassportNumber()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(staffFull.getStaffEducation());
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(staffFull.getAccountLogin());
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(staffFull.getAccountPassword());
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(QString::number(staffFull.getStaffIsDeleted()));
}

void HTMLGenerator::addLineTable(StaffTrunc staffTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(staffTrunc.getStaffId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(staffTrunc.getStaffFirstName());
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(staffTrunc.getStaffLastName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(staffTrunc.getStaffFirstName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(staffTrunc.getPostName());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(staffTrunc.getPostSalary()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(staffTrunc.getPostSalary()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(staffTrunc.getStaffEducation());
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(staffTrunc.getStaffIsDeleted()));
}

void HTMLGenerator::addLineTable(TicketsAndServicesFull ticketsAndServicesFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getTicketsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getTicketsPrice()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(ticketsAndServicesFull.getClientFirstName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(ticketsAndServicesFull.getClientLastName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(ticketsAndServicesFull.getClientPatronymic());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getClientPassportSeries()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getClientPassportNumber()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(ticketsAndServicesFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(ticketsAndServicesFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(ticketsAndServicesFull.getDeparturePoint());
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(ticketsAndServicesFull.getArrivalPoint());
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(ticketsAndServicesFull.getAirplaneName());
    table->cellAt(table->rows() - 1, 12).firstCursorPosition().insertText(ticketsAndServicesFull.getAirplaneDescription());
    table->cellAt(table->rows() - 1, 13).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getAirplaneMaxSizeCargo()));
    table->cellAt(table->rows() - 1, 14).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getAirplaneMaxWeightCargo()));
    table->cellAt(table->rows() - 1, 15).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getAirplaneMaxSeatPlaces()));
    table->cellAt(table->rows() - 1, 16).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 17).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getTicketsBaggageAvailable()));
    table->cellAt(table->rows() - 1, 18).firstCursorPosition().insertText(ticketsAndServicesFull.getBaggageName());
    table->cellAt(table->rows() - 1, 19).firstCursorPosition().insertText(ticketsAndServicesFull.getBaggageDescription());
    table->cellAt(table->rows() - 1, 20).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getBaggageWeight()));
    table->cellAt(table->rows() - 1, 21).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getBaggageSize()));
    table->cellAt(table->rows() - 1, 22).firstCursorPosition().insertText(ticketsAndServicesFull.getServicesName());
    table->cellAt(table->rows() - 1, 23).firstCursorPosition().insertText(ticketsAndServicesFull.getServicesDescription());
    table->cellAt(table->rows() - 1, 24).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getServicesPrice()));
    table->cellAt(table->rows() - 1, 25).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getTicketsSeatNumber()));
    table->cellAt(table->rows() - 1, 26).firstCursorPosition().insertText(QString::number(ticketsAndServicesFull.getTicketsIsDeleted()));
}

void HTMLGenerator::addLineTable(TicketsAndServicesTrunc ticketsAndServicesTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(ticketsAndServicesTrunc.getTicketsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(ticketsAndServicesTrunc.getTicketsPrice()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(ticketsAndServicesTrunc.getClientFirstName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(ticketsAndServicesTrunc.getClientLastName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(ticketsAndServicesTrunc.getClientPatronymic());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(ticketsAndServicesTrunc.getServicesName());
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(ticketsAndServicesTrunc.getServicesPrice()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(ticketsAndServicesTrunc.getTicketsSeatNumber()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(ticketsAndServicesTrunc.getTicketsIsDeleted()));
}

void HTMLGenerator::addLineTable(TicketsFull ticketsFull)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(ticketsFull.getTicketsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(ticketsFull.getTicketsPrice()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(ticketsFull.getClientFirstName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(ticketsFull.getClientLastName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(ticketsFull.getClientPatronymic());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(QString::number(ticketsFull.getClientPassportSeries()));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(QString::number(ticketsFull.getClientPassportNumber()));
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(ticketsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(ticketsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(ticketsFull.getDeparturePoint());
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(ticketsFull.getArrivalPoint());
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(ticketsFull.getAirplaneName());
    table->cellAt(table->rows() - 1, 12).firstCursorPosition().insertText(ticketsFull.getAirplaneDescription());
    table->cellAt(table->rows() - 1, 13).firstCursorPosition().insertText(QString::number(ticketsFull.getAirplaneMaxSizeCargo()));
    table->cellAt(table->rows() - 1, 14).firstCursorPosition().insertText(QString::number(ticketsFull.getAirplaneMaxWeightCargo()));
    table->cellAt(table->rows() - 1, 15).firstCursorPosition().insertText(QString::number(ticketsFull.getAirplaneMaxSeatPlaces()));
    table->cellAt(table->rows() - 1, 16).firstCursorPosition().insertText(QString::number(ticketsFull.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 17).firstCursorPosition().insertText(QString::number(ticketsFull.getTicketsBaggageAvailable()));
    table->cellAt(table->rows() - 1, 18).firstCursorPosition().insertText(ticketsFull.getBaggageName());
    table->cellAt(table->rows() - 1, 19).firstCursorPosition().insertText(ticketsFull.getBaggageDescription());
    table->cellAt(table->rows() - 1, 20).firstCursorPosition().insertText(QString::number(ticketsFull.getBaggageWeight()));
    table->cellAt(table->rows() - 1, 21).firstCursorPosition().insertText(QString::number(ticketsFull.getBaggageSize()));
    table->cellAt(table->rows() - 1, 22).firstCursorPosition().insertText(QString::number(ticketsFull.getTicketsSeatNumber()));
    table->cellAt(table->rows() - 1, 23).firstCursorPosition().insertText(QString::number(ticketsFull.getTicketsIsDeleted()));
}

void HTMLGenerator::addLineTable(TicketsTrunc ticketsTrunc)
{
    table->appendRows(1);

    table->cellAt(table->rows() - 1, 0).firstCursorPosition().insertText(QString::number(ticketsTrunc.getTicketsId()));
    table->cellAt(table->rows() - 1, 1).firstCursorPosition().insertText(QString::number(ticketsTrunc.getTicketsPrice()));
    table->cellAt(table->rows() - 1, 2).firstCursorPosition().insertText(ticketsTrunc.getClientFirstName());
    table->cellAt(table->rows() - 1, 3).firstCursorPosition().insertText(ticketsTrunc.getClientLastName());
    table->cellAt(table->rows() - 1, 4).firstCursorPosition().insertText(ticketsTrunc.getClientPatronymic());
    table->cellAt(table->rows() - 1, 5).firstCursorPosition().insertText(ticketsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));
    table->cellAt(table->rows() - 1, 6).firstCursorPosition().insertText(ticketsTrunc.getArrivalPoint());
    table->cellAt(table->rows() - 1, 7).firstCursorPosition().insertText(QString::number(ticketsTrunc.getFlightsLadder()));
    table->cellAt(table->rows() - 1, 8).firstCursorPosition().insertText(QString::number(ticketsTrunc.getTicketsBaggageAvailable()));
    table->cellAt(table->rows() - 1, 9).firstCursorPosition().insertText(ticketsTrunc.getBaggageName());
    table->cellAt(table->rows() - 1, 10).firstCursorPosition().insertText(QString::number(ticketsTrunc.getTicketsSeatNumber()));
    table->cellAt(table->rows() - 1, 11).firstCursorPosition().insertText(QString::number(ticketsTrunc.getTicketsIsDeleted()));
}
