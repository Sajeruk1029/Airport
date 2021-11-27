#include "AirCompanyAndAirplaneFull.h"

AirCompanyAndAirplaneFull::AirCompanyAndAirplaneFull(unsigned int &airplaneId, QString &airplaneName, QString &airplaneDescription, unsigned int &airplaneMaxSizeCargo, unsigned int &airplaneMaxWeightCargo, unsigned int &airplaneMaxSeatPlaces, QString &airCompanyName, bool &airplaneIsDeleted) : AirplaneId(airplaneId), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), AirCompanyName(airCompanyName), AirplaneIsDeleted(airplaneIsDeleted){}
AirCompanyAndAirplaneFull::AirCompanyAndAirplaneFull(unsigned int airplaneId, QString airplaneName, QString airplaneDescription, unsigned int airplaneMaxSizeCargo, unsigned int airplaneMaxWeightCargo, unsigned int airplaneMaxSeatPlaces, QString airCompanyName, bool airplaneIsDeleted) : AirplaneId(airplaneId), AirplaneName(airplaneName), AirplaneDescription(airplaneDescription), AirplaneMaxSizeCargo(airplaneMaxSizeCargo), AirplaneMaxWeightCargo(airplaneMaxWeightCargo), AirplaneMaxSeatPlaces(airplaneMaxSeatPlaces), AirCompanyName(airCompanyName), AirplaneIsDeleted(airplaneIsDeleted){}
AirCompanyAndAirplaneFull::AirCompanyAndAirplaneFull(){}

unsigned int AirCompanyAndAirplaneFull::getAirplaneId() const { return this->AirplaneId; }
unsigned int AirCompanyAndAirplaneFull::getAirplaneMaxSizeCargo() const { return this->AirplaneMaxSizeCargo; }
unsigned int AirCompanyAndAirplaneFull::getAirplaneMaxWeightCargo() const { return this->AirplaneMaxWeightCargo; }
unsigned int AirCompanyAndAirplaneFull::getAirplaneMaxSeatPlaces() const { return this->AirplaneMaxSeatPlaces; }

QString AirCompanyAndAirplaneFull::getAirplaneName() const { return this->AirplaneName; }
QString AirCompanyAndAirplaneFull::getAirplaneDescription() const { return this->AirplaneDescription; }
QString AirCompanyAndAirplaneFull::getAirCompanyName() const { return this->AirCompanyName; }

bool AirCompanyAndAirplaneFull::getAirplaneIsDeleted() const { return this->AirplaneIsDeleted; }

void AirCompanyAndAirplaneFull::setAirplaneId(unsigned int &airplaneId){ this->AirplaneId = airplaneId; }
void AirCompanyAndAirplaneFull::setAirplaneMaxSizeCargo(unsigned int &airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void AirCompanyAndAirplaneFull::setAirplaneMaxWeightCargo(unsigned int &airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void AirCompanyAndAirplaneFull::setAirplaneMaxSeatPlaces(unsigned int &airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void AirCompanyAndAirplaneFull::setAirplaneName(QString &airplaneName){ this->AirplaneName = airplaneName; }
void AirCompanyAndAirplaneFull::setAirplaneDescription(QString &airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void AirCompanyAndAirplaneFull::setAirCompanyName(QString &airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndAirplaneFull::setAirplaneIsDeleted(bool &airplaneIsDeleted){ this->AirplaneIsDeleted = airplaneIsDeleted; }

void AirCompanyAndAirplaneFull::setAirplaneId(unsigned int airplaneId){ this->AirplaneId = airplaneId; }
void AirCompanyAndAirplaneFull::setAirplaneMaxSizeCargo(unsigned int airplaneMaxSizeCargo){ this->AirplaneMaxSizeCargo = airplaneMaxSizeCargo; }
void AirCompanyAndAirplaneFull::setAirplaneMaxWeightCargo(unsigned int airplaneMaxWeightCargo){ this->AirplaneMaxWeightCargo = airplaneMaxWeightCargo; }
void AirCompanyAndAirplaneFull::setAirplaneMaxSeatPlaces(unsigned int airplaneMaxSeatPlaces){ this->AirplaneMaxSeatPlaces = airplaneMaxSeatPlaces; }
void AirCompanyAndAirplaneFull::setAirplaneName(QString airplaneName){ this->AirplaneName = airplaneName; }
void AirCompanyAndAirplaneFull::setAirplaneDescription(QString airplaneDescription){ this->AirplaneDescription = airplaneDescription; }
void AirCompanyAndAirplaneFull::setAirCompanyName(QString airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndAirplaneFull::setAirplaneIsDeleted(bool airplaneIsDeleted){ this->AirplaneIsDeleted = airplaneIsDeleted; }

