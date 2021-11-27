#include "AirCompanyAndAirplaneTrunc.h"

AirCompanyAndAirplaneTrunc::AirCompanyAndAirplaneTrunc(unsigned int &airplaneId, QString &airplaneName, QString &airCompanyName, bool &airplaneIsDeleted) : AirplaneId(airplaneId), AirplaneName(airplaneName), AirCompanyName(airCompanyName), AirplaneIsDeleted(airplaneIsDeleted){}
AirCompanyAndAirplaneTrunc::AirCompanyAndAirplaneTrunc(unsigned int airplaneId, QString airplaneName, QString airCompanyName, bool airplaneIsDeleted) : AirplaneId(airplaneId), AirplaneName(airplaneName), AirCompanyName(airCompanyName), AirplaneIsDeleted(airplaneIsDeleted){}
AirCompanyAndAirplaneTrunc::AirCompanyAndAirplaneTrunc(){}

unsigned int AirCompanyAndAirplaneTrunc::getAirplaneId() const { return this->AirplaneId; }

QString AirCompanyAndAirplaneTrunc::getAirplaneName() const { return this->AirplaneName; }
QString AirCompanyAndAirplaneTrunc::getAirCompanyName() const { return this->AirCompanyName; }

bool AirCompanyAndAirplaneTrunc::getAirplaneIsDeleted() const { return this->AirplaneIsDeleted; }

void AirCompanyAndAirplaneTrunc::setAirplaneId(unsigned int &airplaneId){ this->AirplaneId = airplaneId; }
void AirCompanyAndAirplaneTrunc::setAirplaneName(QString &airplaneName){ this->AirplaneName = airplaneName; }
void AirCompanyAndAirplaneTrunc::setAirCompanyName(QString &airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndAirplaneTrunc::setAirplaneIsDeleted(bool &airplaneIsDeleted){ this->AirplaneIsDeleted = airplaneIsDeleted; }

void AirCompanyAndAirplaneTrunc::setAirplaneId(unsigned int airplaneId){ this->AirplaneId = airplaneId; }
void AirCompanyAndAirplaneTrunc::setAirplaneName(QString airplaneName){ this->AirplaneName = airplaneName; }
void AirCompanyAndAirplaneTrunc::setAirCompanyName(QString airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndAirplaneTrunc::setAirplaneIsDeleted(bool airplaneIsDeleted){ this->AirplaneIsDeleted = airplaneIsDeleted; }

