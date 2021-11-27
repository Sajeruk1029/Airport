#include "Services.h"

Services::Services(unsigned int &id, QString &name, QString &description, unsigned int &price, bool &isDeleted) : Id(id), Name(name), Description(description), Price(price), IsDeleted(isDeleted){}
Services::Services(unsigned int id, QString name, QString description, unsigned int price, bool isDeleted) : Id(id), Name(name), Description(description), Price(price), IsDeleted(isDeleted){}
Services::Services(){}

unsigned int Services::getId() const { return this->Id; }
unsigned int Services::getPrice() const { return this->Price; }

QString Services::getName() const { return this->Name; }
QString Services::getDescription() const { return this->Description; }

bool Services::getIsDeleted() const { return this->IsDeleted; }

void Services::setId(unsigned int &id){ this->Id = id; }
void Services::setPrice(unsigned int &price){ this->Price = price; }
void Services::setName(QString &name){ this->Name = name; }
void Services::setDescription(QString &description){ this->Description = description; }
void Services::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Services::setId(unsigned int id){ this->Id = id; }
void Services::setPrice(unsigned int price){ this->Price = price; }
void Services::setName(QString name){ this->Name = name; }
void Services::setDescription(QString description){ this->Description = description; }
void Services::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
