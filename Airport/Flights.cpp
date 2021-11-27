#include "Flights.h"

Flights::Flights(unsigned int &id, QString &departureDate, QString &arrivalDate, unsigned int &departurePoint, unsigned int &arrivalPoint, unsigned int &airplane, unsigned int &ladder, bool &isDeleted) : Id(id), DepartureDate(QDateTime::fromString(departureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalDate(QDateTime::fromString(arrivalDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), DeparturePoint(departurePoint), Airplane(airplane), Ladder(ladder), IsDeleted(isDeleted){}
Flights::Flights(unsigned int id, QString departureDate, QString arrivalDate, unsigned int departurePoint, unsigned int arrivalPoint, unsigned int airplane, unsigned int ladder, bool isDeleted) : Id(id), DepartureDate(QDateTime::fromString(departureDate, "yyyy-MM-dd hh:mm:ss")), ArrivalDate(QDateTime::fromString(arrivalDate, "yyyy-MM-dd hh:mm:ss")), ArrivalPoint(arrivalPoint), DeparturePoint(departurePoint), Airplane(airplane), Ladder(ladder), IsDeleted(isDeleted){}
Flights::Flights(unsigned int &id, QDateTime &departureDate, QDateTime &arrivalDate, unsigned int &departurePoint, unsigned int &arrivalPoint, unsigned int &airplane, unsigned int &ladder, bool &isDeleted) : Id(id), DepartureDate(departureDate), ArrivalDate(arrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), Airplane(airplane), Ladder(ladder), IsDeleted(isDeleted){}
Flights::Flights(unsigned int id, QDateTime departureDate, QDateTime arrivalDate, unsigned int departurePoint, unsigned int arrivalPoint, unsigned int airplane, unsigned int ladder, bool isDeleted) : Id(id), DepartureDate(departureDate), ArrivalDate(arrivalDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), Airplane(airplane), Ladder(ladder), IsDeleted(isDeleted){}
Flights::Flights(){}

unsigned int Flights::getId() const { return this->Id; }
unsigned int Flights::getDeparturePoint() const { return this->DeparturePoint; }
unsigned int Flights::getArrivalPoint() const { return this->ArrivalPoint; }
unsigned int Flights::getAirplane() const { return this->Airplane; }
unsigned int Flights::getLadder() const { return this->Ladder; }

QDateTime Flights::getDepartureDate() const { return this->DepartureDate; }
QDateTime Flights::getArrivalDate() const { return this->ArrivalDate; }

bool Flights::getIsDeleted() const { return this->IsDeleted; }

void Flights::setId(unsigned int &id){ this->Id = id; }
void Flights::setDeparturePoint(unsigned int &departurePoint){ this->DeparturePoint = departurePoint; }
void Flights::setArrivalPoint(unsigned int &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void Flights::setAirplane(unsigned int &airplane){ this->Airplane = airplane; }
void Flights::setLadder(unsigned int &ladder){ this->Ladder = ladder; }
void Flights::setDepartureDate(QDateTime &departureDate){ this->DepartureDate = departureDate; }
void Flights::setArrivalDate(QDateTime &arrivalDate){ this->ArrivalDate = arrivalDate; }
void Flights::setDepartureDate(QString &departureDate){ this->DepartureDate = QDateTime::fromString(departureDate, "yyyy-MM-dd hh:mm:ss"); }
void Flights::setArrivalDate(QString &arrivalDate){ this->ArrivalDate = QDateTime::fromString(arrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void Flights::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Flights::setId(unsigned int id){ this->Id = id; }
void Flights::setDeparturePoint(unsigned int departurePoint){ this->DeparturePoint = departurePoint; }
void Flights::setArrivalPoint(unsigned int arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void Flights::setAirplane(unsigned int airplane){ this->Airplane = airplane; }
void Flights::setLadder(unsigned int ladder){ this->Ladder = ladder; }
void Flights::setDepartureDate(QDateTime departureDate){ this->DepartureDate = departureDate; }
void Flights::setArrivalDate(QDateTime arrivalDate){ this->ArrivalDate = arrivalDate; }
void Flights::setDepartureDate(QString departureDate){ this->DepartureDate = QDateTime::fromString(departureDate, "yyyy-MM-dd hh:mm:ss"); }
void Flights::setArrivalDate(QString arrivalDate){ this->ArrivalDate = QDateTime::fromString(arrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void Flights::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
