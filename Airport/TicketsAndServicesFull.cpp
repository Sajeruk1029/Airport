#include "TicketsAndServicesFull.h"

TicketsAndServicesFull::TicketsAndServicesFull(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QString flightsDepartureDate, QString flightsArrivalDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, QString baggageDescription, unsigned int baggageWeight, unsigned int baggageSize, QString servicesName, QString servicesDescription, unsigned int servicesPrice, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ServicesName(servicesName), ServicesDescription(servicesDescription), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesFull::TicketsAndServicesFull(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QDateTime flightsDepartureDate, QDateTime flightsArrivalDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, QString baggageDescription, unsigned int baggageWeight, unsigned int baggageSize, QString servicesName, QString servicesDescription, unsigned int servicesPrice, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(flightsDepartureDate), FlightsArrivalDate(flightsArrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ServicesName(servicesName), ServicesDescription(servicesDescription), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesFull::TicketsAndServicesFull(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QString &flightsDepartureDate, QString &flightsArrivalDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, QString &baggageDescription, unsigned int &baggageWeight, unsigned int &baggageSize, QString &servicesName, QString &servicesDescription, unsigned int &servicesPrice, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ServicesName(servicesName), ServicesDescription(servicesDescription), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesFull::TicketsAndServicesFull(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QDateTime &flightsDepartureDate, QDateTime &flightsArrivalDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, QString &baggageDescription, unsigned int &baggageWeight, unsigned int &baggageSize, QString &servicesName, QString &servicesDescription, unsigned int &servicesPrice, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(flightsDepartureDate), FlightsArrivalDate(flightsArrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ServicesName(servicesName), ServicesDescription(servicesDescription), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesFull::TicketsAndServicesFull(){}

unsigned int TicketsAndServicesFull::getTicketsId() const { return this->TicketsId; }
unsigned int TicketsAndServicesFull::getTicketsPrice() const { return this->TicketsPrice; }
unsigned int TicketsAndServicesFull::getClientPassportNumber() const { return this->ClientPassportNumber; }
unsigned int TicketsAndServicesFull::getAirplaneMaxSizeCargo() const { return this->AirplaneMaxSizeCargo; }
unsigned int TicketsAndServicesFull::getAirplaneMaxWeightCargo() const { return this->AirplaneMaxWeightCargo; }
unsigned int TicketsAndServicesFull::getAirplaneMaxSeatPlaces() const { return this->AirplaneMaxSeatPlaces; }
unsigned int TicketsAndServicesFull::getFlightsLadder() const { return this->FlightsLadder; }
unsigned int TicketsAndServicesFull::getBaggageWeight() const { return this->BaggageWeight; }
unsigned int TicketsAndServicesFull::getBaggageSize() const { return this->BaggageSize; }
unsigned int TicketsAndServicesFull::getServicesPrice() const { return this->ServicesPrice; }
unsigned int TicketsAndServicesFull::getTicketsSeatNumber() const { return this->TicketsSeatNumber; }

unsigned short TicketsAndServicesFull::getClientPassportSeries() const { return this->ClientPassportSeries; }

QString TicketsAndServicesFull::getClientFirstName() const { return this->ClientFirstName; }
QString TicketsAndServicesFull::getClientLastName() const { return this->ClientLastName; }
QString TicketsAndServicesFull::getClientPatronymic() const { return this->ClientPatronymic; }
QString TicketsAndServicesFull::getDeparturePoint() const { return this->DeparturePoint; }
QString TicketsAndServicesFull::getArrivalPoint() const { return this->ArrivalPoint; }
QString TicketsAndServicesFull::getAirplaneName() const { return this->AirplaneName; }
QString TicketsAndServicesFull::getAirplaneDescription() const { return this->AirplaneDescription; }
QString TicketsAndServicesFull::getBaggageName() const { return this->BaggageName; }
QString TicketsAndServicesFull::getBaggageDescription() const { return this->BaggageDescription; }
QString TicketsAndServicesFull::getServicesName() const { return this->ServicesName; }
QString TicketsAndServicesFull::getServicesDescription() const { return this->ServicesDescription; }

QDateTime TicketsAndServicesFull::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }
QDateTime TicketsAndServicesFull::getFlightsArrivalDate() const { return this->FlightsArrivalDate; }

bool TicketsAndServicesFull::getTicketsBaggageAvailable() const { return this->TicketsBaggageAvailable; }
bool TicketsAndServicesFull::getTicketsIsDeleted() const { return this->TicketsIsDeleted; }

void TicketsAndServicesFull::setTicketsId(unsigned int &ticketsId){ this->TicketsId = ticketsId; }
void TicketsAndServicesFull::setTicketsPrice(unsigned int &ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsAndServicesFull::setClientPassportNumber(unsigned int &clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void TicketsAndServicesFull::setAirplaneMaxSizeCargo(unsigned int &airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void TicketsAndServicesFull::setAirplaneMaxWeightCargo(unsigned int &airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void TicketsAndServicesFull::setAirplaneMaxSeatPlaces(unsigned int &airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void TicketsAndServicesFull::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsAndServicesFull::setBaggageWeight(unsigned int &baggageWeight){ this->BaggageWeight = baggageWeight; }
void TicketsAndServicesFull::setBaggageSize(unsigned int &baggageSize){ this->BaggageSize = baggageSize; }
void TicketsAndServicesFull::setServicesPrice(unsigned int &servicesPrice){ this->ServicesPrice = servicesPrice; }
void TicketsAndServicesFull::setTicketsSeatNumber(unsigned int &ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsAndServicesFull::setClientPassportSeries(unsigned short &clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void TicketsAndServicesFull::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsAndServicesFull::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void TicketsAndServicesFull::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsAndServicesFull::setDeparturePoint(QString &departurePoint){ this->DeparturePoint = departurePoint; }
void TicketsAndServicesFull::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsAndServicesFull::setAirplaneName(QString &airplaneName){ this->AirplaneName = airplaneName; }
void TicketsAndServicesFull::setAirplaneDescription(QString &airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void TicketsAndServicesFull::setBaggageName(QString &baggageName){ this->BaggageName = baggageName; }
void TicketsAndServicesFull::setBaggageDescription(QString &baggageDescription){ this->BaggageDescription = baggageDescription; }
void TicketsAndServicesFull::setServicesName(QString &servicesName){ this->ServicesName = servicesName; }
void TicketsAndServicesFull::setServicesDescription(QString &servicesDescription){ this->ServicesDescription = servicesDescription; }

void TicketsAndServicesFull::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsAndServicesFull::setFlightsArrivalDate(QDateTime &flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void TicketsAndServicesFull::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void TicketsAndServicesFull::setFlightsArrivalDate(QString &flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsAndServicesFull::setTicketsBaggageAvailable(bool &ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsAndServicesFull::setTicketsIsDeleted(bool &ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }

void TicketsAndServicesFull::setTicketsId(unsigned int ticketsId){ this->TicketsId = ticketsId; }
void TicketsAndServicesFull::setTicketsPrice(unsigned int ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsAndServicesFull::setClientPassportNumber(unsigned int clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void TicketsAndServicesFull::setAirplaneMaxSizeCargo(unsigned int airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void TicketsAndServicesFull::setAirplaneMaxWeightCargo(unsigned int airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void TicketsAndServicesFull::setAirplaneMaxSeatPlaces(unsigned int airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void TicketsAndServicesFull::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsAndServicesFull::setBaggageWeight(unsigned int baggageWeight){ this->BaggageWeight = baggageWeight; }
void TicketsAndServicesFull::setBaggageSize(unsigned int baggageSize){ this->BaggageSize = baggageSize; }
void TicketsAndServicesFull::setServicesPrice(unsigned int servicesPrice){ this->ServicesPrice = servicesPrice; }
void TicketsAndServicesFull::setTicketsSeatNumber(unsigned int ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsAndServicesFull::setClientPassportSeries(unsigned short clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void TicketsAndServicesFull::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsAndServicesFull::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void TicketsAndServicesFull::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsAndServicesFull::setDeparturePoint(QString departurePoint){ this->DeparturePoint = departurePoint; }
void TicketsAndServicesFull::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsAndServicesFull::setAirplaneName(QString airplaneName){ this->AirplaneName = airplaneName; }
void TicketsAndServicesFull::setAirplaneDescription(QString airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void TicketsAndServicesFull::setBaggageName(QString baggageName){ this->BaggageName = baggageName; }
void TicketsAndServicesFull::setBaggageDescription(QString baggageDescription){ this->BaggageDescription = baggageDescription; }
void TicketsAndServicesFull::setServicesName(QString servicesName){ this->ServicesName = servicesName; }
void TicketsAndServicesFull::setServicesDescription(QString servicesDescription){ this->ServicesDescription = servicesDescription; }

void TicketsAndServicesFull::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsAndServicesFull::setFlightsArrivalDate(QDateTime flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void TicketsAndServicesFull::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void TicketsAndServicesFull::setFlightsArrivalDate(QString flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsAndServicesFull::setTicketsBaggageAvailable(bool ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsAndServicesFull::setTicketsIsDeleted(bool ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }
