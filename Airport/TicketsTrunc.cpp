#include "TicketsTrunc.h"

TicketsTrunc::TicketsTrunc(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, QString &flightsDepartureDate, QString &arrivalPoint, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsTrunc::TicketsTrunc(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, QDateTime flightsDepartureDate, QString arrivalPoint, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), FlightsDepartureDate(flightsDepartureDate), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsTrunc::TicketsTrunc(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, QString flightsDepartureDate, QString arrivalPoint, unsigned int flightsLadder, bool ticketsBaggageAvailable, QString baggageName, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsTrunc::TicketsTrunc(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, QDateTime &flightsDepartureDate, QString &arrivalPoint, unsigned int &flightsLadder, bool &ticketsBaggageAvailable, QString &baggageName, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), FlightsDepartureDate(flightsDepartureDate), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), TicketsBaggageAvailable(ticketsBaggageAvailable), BaggageName(baggageName), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsTrunc::TicketsTrunc(){}

unsigned int TicketsTrunc::getTicketsId() const { return this->TicketsId; }
unsigned int TicketsTrunc::getTicketsPrice() const { return this->TicketsPrice; }
unsigned int TicketsTrunc::getFlightsLadder() const { return this->FlightsLadder; }
unsigned int TicketsTrunc::getTicketsSeatNumber() const { return this->TicketsSeatNumber; }

QString TicketsTrunc::getClientFirstName() const { return this->ClientFirstName; }
QString TicketsTrunc::getClientLastName() const { return this->ClientLastName; }
QString TicketsTrunc::getClientPatronymic() const { return this->ClientPatronymic; }
QString TicketsTrunc::getArrivalPoint() const { return this->ArrivalPoint; }
QString TicketsTrunc::getBaggageName() const { return this->BaggageName; }

QDateTime TicketsTrunc::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }

bool TicketsTrunc::getTicketsBaggageAvailable() const { return this->TicketsBaggageAvailable; }
bool TicketsTrunc::getTicketsIsDeleted() const { return this->TicketsIsDeleted; }

void TicketsTrunc::setTicketsId(unsigned int &ticketsId){ this->TicketsId = ticketsId; }
void TicketsTrunc::setTicketsPrice(unsigned int &ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsTrunc::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsTrunc::setTicketsSeatNumber(unsigned int &ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsTrunc::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsTrunc::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void TicketsTrunc::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsTrunc::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsTrunc::setBaggageName(QString &baggageName){ this->BaggageName = baggageName; }

void TicketsTrunc::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsTrunc::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsTrunc::setTicketsBaggageAvailable(bool &ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsTrunc::setTicketsIsDeleted(bool &ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }

void TicketsTrunc::setTicketsId(unsigned int ticketsId){ this->TicketsId = ticketsId; }
void TicketsTrunc::setTicketsPrice(unsigned int ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsTrunc::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void TicketsTrunc::setTicketsSeatNumber(unsigned int ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsTrunc::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsTrunc::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void TicketsTrunc::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsTrunc::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void TicketsTrunc::setBaggageName(QString baggageName){ this->BaggageName = baggageName; }

void TicketsTrunc::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void TicketsTrunc::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }

void TicketsTrunc::setTicketsBaggageAvailable(bool ticketsBaggageAvailable){ this->TicketsBaggageAvailable = ticketsBaggageAvailable; }
void TicketsTrunc::setTicketsIsDeleted(bool ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }
