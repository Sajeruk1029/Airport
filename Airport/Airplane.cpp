#include "Airplane.h"

Airplane::Airplane(unsigned int &id, QString &name, QString &description, unsigned int &maxSizeCargo, unsigned int &maxWeightCargo, unsigned int &maxSeatPlaces, bool &isDeleted) : Id(id), Name(name), Description(description), MaxSizeCargo(maxSizeCargo), MaxWeightCargo(maxWeightCargo), MaxSeatPlaces(maxSeatPlaces), IsDeleted(isDeleted){}
Airplane::Airplane(unsigned int id, QString name, QString description, unsigned int maxSizeCargo, unsigned int maxWeightCargo, unsigned int maxSeatPlaces, bool isDeleted) : Id(id), Name(name), Description(description), MaxSizeCargo(maxSizeCargo), MaxWeightCargo(maxWeightCargo), MaxSeatPlaces(maxSeatPlaces), IsDeleted(isDeleted){}
Airplane::Airplane(){}

unsigned int Airplane::getId() const { return this->Id; }
unsigned int Airplane::getMaxSizeCargo() const { return this->MaxSizeCargo; }
unsigned int Airplane::getMaxWeightCargo() const { return this->MaxWeightCargo; }
unsigned int Airplane::getMaxSeatPlaces() const { return this->MaxSeatPlaces; }

QString Airplane::getName() const { return this->Name; }
QString Airplane::getDescription() const { return this->Description; }

bool Airplane::getIsDeleted() const { return this->IsDeleted; }

void Airplane::setId(unsigned int &id){ this->Id = id; }
void Airplane::setMaxSizeCargo(unsigned int &maxSizeCargo){ this->MaxSizeCargo = maxSizeCargo; }
void Airplane::setMaxWeightCargo(unsigned int &maxWeightCargo){ this->MaxWeightCargo = maxWeightCargo; }
void Airplane::setMaxSeatPlaces(unsigned int &maxSeatPlaces){ this->MaxSeatPlaces = maxSeatPlaces; }
void Airplane::setName(QString &name){ this->Name = name; }
void Airplane::setDescription(QString &description){ this->Description = description; }
void Airplane::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Airplane::setId(unsigned int id){ this->Id = id; }
void Airplane::setMaxSizeCargo(unsigned int maxSizeCargo){ this->MaxSizeCargo = maxSizeCargo; }
void Airplane::setMaxWeightCargo(unsigned int maxWeightCargo){ this->MaxWeightCargo = maxWeightCargo; }
void Airplane::setMaxSeatPlaces(unsigned int maxSeatPlaces){ this->MaxSeatPlaces = maxSeatPlaces; }
void Airplane::setName(QString name){ this->Name = name; }
void Airplane::setDescription(QString description){ this->Description = description; }
void Airplane::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
