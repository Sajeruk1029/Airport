#include "FlightsTrunc.h"

FlightsTrunc::FlightsTrunc(unsigned int &flightsId, QString &flightsDepartureDate, QString &arrivalPoint, unsigned int &flightsLadder, bool &flightsIsDeleted) : FlightsId(flightsId), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsTrunc::FlightsTrunc(unsigned int flightsId, QString flightsDepartureDate, QString arrivalPoint, unsigned int flightsLadder, bool flightsIsDeleted) : FlightsId(flightsId), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsTrunc::FlightsTrunc(unsigned int &flightsId, QDateTime &flightsDepartureDate, QString &arrivalPoint, unsigned int &flightsLadder, bool &flightsIsDeleted) : FlightsId(flightsId), FlightsDepartureDate(flightsDepartureDate), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsTrunc::FlightsTrunc(unsigned int flightsId, QDateTime flightsDepartureDate, QString arrivalPoint, unsigned int flightsLadder, bool flightsIsDeleted) : FlightsId(flightsId), FlightsDepartureDate(flightsDepartureDate), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsTrunc::FlightsTrunc(){}

unsigned int FlightsTrunc::getFlightsId() const { return this->FlightsId; }
unsigned int FlightsTrunc::getFlightsLadder() const { return this->FlightsLadder; }

QDateTime FlightsTrunc::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }

QString FlightsTrunc::getArrivalPoint() const { return this->ArrivalPoint; }

bool FlightsTrunc::getFlightsIsDeleted() const { return this->FlightsIsDeleted; }

void FlightsTrunc::setFlightsId(unsigned int &flightsId){ this->FlightsId = flightsId; }
void FlightsTrunc::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void FlightsTrunc::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void FlightsTrunc::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsTrunc::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void FlightsTrunc::setFlightsIsDeleted(bool &flightsIsDeleted){ this->FlightsIsDeleted = flightsIsDeleted; }

void FlightsTrunc::setFlightsId(unsigned int flightsId){ this->FlightsId = flightsId; }
void FlightsTrunc::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void FlightsTrunc::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void FlightsTrunc::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsTrunc::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void FlightsTrunc::setFlightsIsDeleted(bool flightsIsDeleted){ this->FlightsIsDeleted = flightsIsDeleted; }
