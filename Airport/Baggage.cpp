#include "Baggage.h"

Baggage::Baggage(unsigned int &id, QString &name, QString &description, unsigned int &weight, unsigned int &size, bool &isDeleted) : Id(id), Name(name), Description(description), Weight(weight), Size(size), IsDeleted(isDeleted){}
Baggage::Baggage(unsigned int id, QString name, QString description, unsigned int weight, unsigned int size, bool isDeleted) : Id(id), Name(name), Description(description), Weight(weight), Size(size), IsDeleted(isDeleted){}
Baggage::Baggage(){}

unsigned int Baggage::getId() const { return this->Id; }
unsigned int Baggage::getWeight() const { return this->Weight; }
unsigned int Baggage::getSize() const { return this->Size; }

QString Baggage::getName() const { return this->Name; }
QString Baggage::getDescription() const { return this->Description; }

bool Baggage::getIsDeleted() const { return this->IsDeleted; }

void Baggage::setId(unsigned int &id){ this->Id = id; }
void Baggage::setWeight(unsigned int &weight){ this->Weight = weight; }
void Baggage::setSize(unsigned int &size){ this->Size = size; }
void Baggage::setName(QString &name){ this->Name = name; }
void Baggage::setDescription(QString &description){ this->Description = description; }
void Baggage::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Baggage::setId(unsigned int id){ this->Id = id; }
void Baggage::setWeight(unsigned int weight){ this->Weight = weight; }
void Baggage::setSize(unsigned int size){ this->Size = size; }
void Baggage::setName(QString name){ this->Name = name; }
void Baggage::setDescription(QString description){ this->Description = description; }
void Baggage::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
