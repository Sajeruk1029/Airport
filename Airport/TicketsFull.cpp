#include "TicketsFull.h"

TicketsFull::TicketsFull(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QString &flightsDepartureDate, QString &flightsArrivalDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, QString &baggageDescription, unsigned int &baggageWeight, unsigned int &baggageSize, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsFull::TicketsFull(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QString flightsDepartureDate, QString flightsArrivalDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, QString baggageDescription, unsigned int baggageWeight, unsigned int baggageSize, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsFull::TicketsFull(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QDateTime &flightsDepartureDate, QDateTime &flightsArrivalDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, QString &baggageDescription, unsigned int &baggageWeight, unsigned int &baggageSize, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(flightsDepartureDate), FlightsArrivalDate(flightsArrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsFull::TicketsFull(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QDateTime flightsDepartureDate, QDateTime flightsArrivalDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, QString baggageDescription, unsigned int baggageWeight, unsigned int baggageSize, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsDepartureDate(flightsDepartureDate), FlightsArrivalDate(flightsArrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsFull::TicketsFull(){}

unsigned int TicketsFull::getTicketsId() const { return this->TicketsId; }
unsigned int TicketsFull::getTicketsPrice() const { return this->TicketsPrice; }
unsigned int TicketsFull::getClientPassportNumber() const { return this->ClientPassportNumber; }
unsigned int TicketsFull::getAirplaneMaxSizeCargo() const { return this->AirplaneMaxSizeCargo; }
unsigned int TicketsFull::getAirplaneMaxWeightCargo() const { return this->AirplaneMaxWeightCargo; }
unsigned int TicketsFull::getAirplaneMaxSeatPlaces() const { return this->AirplaneMaxSeatPlaces; }
unsigned int TicketsFull::getFlightsLadder() const { return this->FlightsLadder; }
unsigned int TicketsFull::getBaggageWeight() const { return this->BaggageWeight; }
unsigned int TicketsFull::getBaggageSize() const { return this->BaggageSize; }
unsigned int TicketsFull::getTicketsSeatNumber() const { return this->TicketsSeatNumber; }

unsigned short TicketsFull::getClientPassportSeries() const { return this->ClientPassportSeries; }

QString TicketsFull::getClientFirstName() const { return this->ClientFirstName; }
QString TicketsFull::getClientLastName() const { return this->ClientLastName; }
QString TicketsFull::getClientPatronymic() const { return this->ClientPatronymic; }
QString TicketsFull::getDeparturePoint() const { return this->DeparturePoint; }
QString TicketsFull::getArrivalPoint() const { return this->ArrivalPoint; }
QString TicketsFull::getAirplaneName() const { return this->AirplaneName; }
QString TicketsFull::getAirplaneDescription() const { return this->AirplaneDescription; }
QString TicketsFull::getBaggageName() const { return this->BaggageName; }
QString TicketsFull::getBaggageDescription() const { return this->BaggageDescription; }

QDateTime TicketsFull::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }
QDateTime TicketsFull::getFlightsArrivalDate() const { return this->FlightsArrivalDate; }

bool TicketsFull::getTicketsBaggageAvailable() const { return this->TicketsBaggageAvailable; }
bool TicketsFull::getTicketsIsDeleted() const { return this->TicketsIsDeleted; }

void TicketsFull::setTicketsId(unsigned int &ticketsId){ this->TicketsId = ticketsId; }
void TicketsFull::setTicketsPrice(unsigned int &ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsFull::setClientPassportNumber(unsigned int &clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void TicketsFull::setAirplaneMaxSizeCargo(unsigned int &airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void TicketsFull::setAirplaneMaxWeightCargo(unsigned int &airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void TicketsFull::setAirplaneMaxSeatPlaces(unsigned int &airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void TicketsFull::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsFull::setBaggageWeight(unsigned int &baggageWeight){ this->BaggageWeight = baggageWeight; }
void TicketsFull::setBaggageSize(unsigned int &baggageSize){ this->BaggageSize = baggageSize; }
void TicketsFull::setTicketsSeatNumber(unsigned int &ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsFull::setClientPassportSeries(unsigned short &clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void TicketsFull::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsFull::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void TicketsFull::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsFull::setDeparturePoint(QString &departurePoint){ this->DeparturePoint = departurePoint; }
void TicketsFull::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsFull::setAirplaneName(QString &airplaneName){ this->AirplaneName = airplaneName; }
void TicketsFull::setAirplaneDescription(QString &airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void TicketsFull::setBaggageName(QString &baggageName){ this->BaggageName = baggageName; }
void TicketsFull::setBaggageDescription(QString &baggageDescription){ this->BaggageDescription = baggageDescription; }

void TicketsFull::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsFull::setFlightsArrivalDate(QDateTime &flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void TicketsFull::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void TicketsFull::setFlightsArrivalDate(QString &flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsFull::setTicketsBaggageAvailable(bool &ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsFull::setTicketsIsDeleted(bool &ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }

void TicketsFull::setTicketsId(unsigned int ticketsId){ this->TicketsId = ticketsId; }
void TicketsFull::setTicketsPrice(unsigned int ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsFull::setClientPassportNumber(unsigned int clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void TicketsFull::setAirplaneMaxSizeCargo(unsigned int airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void TicketsFull::setAirplaneMaxWeightCargo(unsigned int airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void TicketsFull::setAirplaneMaxSeatPlaces(unsigned int airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void TicketsFull::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsFull::setBaggageWeight(unsigned int baggageWeight){ this->BaggageWeight = baggageWeight; }
void TicketsFull::setBaggageSize(unsigned int baggageSize){ this->BaggageSize = baggageSize; }
void TicketsFull::setTicketsSeatNumber(unsigned int ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsFull::setClientPassportSeries(unsigned short clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void TicketsFull::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsFull::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void TicketsFull::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsFull::setDeparturePoint(QString departurePoint){ this->DeparturePoint = departurePoint; }
void TicketsFull::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsFull::setAirplaneName(QString airplaneName){ this->AirplaneName = airplaneName; }
void TicketsFull::setAirplaneDescription(QString airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void TicketsFull::setBaggageName(QString baggageName){ this->BaggageName = baggageName; }
void TicketsFull::setBaggageDescription(QString baggageDescription){ this->BaggageDescription = baggageDescription; }

void TicketsFull::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsFull::setFlightsArrivalDate(QDateTime flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void TicketsFull::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void TicketsFull::setFlightsArrivalDate(QString flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsFull::setTicketsBaggageAvailable(bool ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsFull::setTicketsIsDeleted(bool ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }
