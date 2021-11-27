#include "FlightsFull.h"

FlightsFull::FlightsFull(unsigned int &flightsId, QString &flightsArrivalDate, QString &flightsDepartureDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &flightsIsDeleted) : FlightsId(flightsId), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh::mm:ss")), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsFull::FlightsFull(unsigned int flightsId, QString flightsArrivalDate, QString flightsDepartureDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool flightsIsDeleted) : FlightsId(flightsId), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh::mm:ss")), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsFull::FlightsFull(unsigned int &flightsId, QDateTime &flightsArrivalDate, QDateTime &flightsDepartureDate, QString &departurePoint, QString &arrivalPoint, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, unsigned int &flightsLadder, bool &flightsIsDeleted) : FlightsId(flightsId), FlightsArrivalDate(flightsArrivalDate), FlightsDepartureDate(flightsDepartureDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsFull::FlightsFull(unsigned int flightsId, QDateTime flightsArrivalDate, QDateTime flightsDepartureDate, QString departurePoint, QString arrivalPoint, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, unsigned int flightsLadder, bool flightsIsDeleted) : FlightsId(flightsId), FlightsArrivalDate(flightsArrivalDate), FlightsDepartureDate(flightsDepartureDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), FlightsLadder(flightsLadder), FlightsIsDeleted(flightsIsDeleted){}
FlightsFull::FlightsFull(){}

unsigned int FlightsFull::getFlightsId() const { return this->FlightsId; }
unsigned int FlightsFull::getAirplaneMaxSizeCargo() const { return this->AirplaneMaxSizeCargo; }
unsigned int FlightsFull::getAirplaneMaxWeightCargo() const { return this->AirplaneMaxWeightCargo; }
unsigned int FlightsFull::getAirplaneMaxSeatPlaces() const { return this->AirplaneMaxSeatPlaces; }
unsigned int FlightsFull::getFlightsLadder() const { return this->FlightsLadder; }

QDateTime FlightsFull::getFlightsArrivalDate() const { return this->FlightsArrivalDate; }
QDateTime FlightsFull::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }

QString FlightsFull::getDeparturePoint() const { return this->DeparturePoint; }
QString FlightsFull::getArrivalPoint() const { return this->ArrivalPoint; }
QString FlightsFull::getAirplaneName() const { return this->AirplaneName; }
QString FlightsFull::getAirplaneDescription() const { return this->AirplaneDescription; }

bool FlightsFull::getFlightsIsDeleted() const { return this->FlightsIsDeleted; }

void FlightsFull::setFlightsId(unsigned int &flightsId){ this->FlightsId = flightsId; }
void FlightsFull::setAirplaneMaxSizeCargo(unsigned int &airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void FlightsFull::setAirplaneMaxWeightCargo(unsigned int &airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void FlightsFull::setAirplaneMaxSeatPlaces(unsigned int &airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void FlightsFull::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void FlightsFull::setFlightsArrivalDate(QDateTime &flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void FlightsFull::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void FlightsFull::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsFull::setFlightsArrivalDate(QString &flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsFull::setDeparturePoint(QString &departurePoint){ this->DeparturePoint = departurePoint; }
void FlightsFull::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void FlightsFull::setAirplaneName(QString &airplaneName){ this->AirplaneName = airplaneName; }
void FlightsFull::setAirplaneDescription(QString &airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void FlightsFull::setFlightsIsDeleted(bool &flightsIsDeleted){ this->FlightsIsDeleted = flightsIsDeleted; }

void FlightsFull::setFlightsId(unsigned int flightsId){ this->FlightsId = flightsId; }
void FlightsFull::setAirplaneMaxSizeCargo(unsigned int airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void FlightsFull::setAirplaneMaxWeightCargo(unsigned int airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void FlightsFull::setAirplaneMaxSeatPlaces(unsigned int airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void FlightsFull::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void FlightsFull::setFlightsArrivalDate(QDateTime flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void FlightsFull::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void FlightsFull::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsFull::setFlightsArrivalDate(QString flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void FlightsFull::setDeparturePoint(QString departurePoint){ this->DeparturePoint = departurePoint; }
void FlightsFull::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void FlightsFull::setAirplaneName(QString airplaneName){ this->AirplaneName = airplaneName; }
void FlightsFull::setAirplaneDescription(QString airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void FlightsFull::setFlightsIsDeleted(bool flightsIsDeleted){ this->FlightsIsDeleted = flightsIsDeleted; }
