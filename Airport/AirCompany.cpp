#include "AirCompany.h"

AirCompany::AirCompany(unsigned int &id, QString &name, bool &isDeleted) : Id(id), Name(name), IsDeleted(isDeleted){}
AirCompany::AirCompany(unsigned int id, QString name, bool isDeleted) : Id(id), Name(name), IsDeleted(isDeleted){}
AirCompany::AirCompany(){}

unsigned int AirCompany::getId() const { return this->Id; }

QString AirCompany::getName() const { return this->Name; }

bool AirCompany::getIsDeleted() const { return this->IsDeleted; }

void AirCompany::setId(unsigned int &id){ this->Id = id; }
void AirCompany::setName(QString &name){ this->Name = name; }
void AirCompany::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void AirCompany::setId(unsigned int id){ this->Id = id; }
void AirCompany::setName(QString name){ this->Name = name; }
void AirCompany::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
