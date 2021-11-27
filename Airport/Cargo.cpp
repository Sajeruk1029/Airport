#include "Cargo.h"

Cargo::Cargo(unsigned int &id, unsigned int &idCategory, unsigned int &weight, QString &description, unsigned int &idTicket, unsigned int &size, bool &isDeleted) : Id(id), IdCategory(idCategory), Weight(weight), Description(description), IdTicket(idTicket), Size(size), IsDeleted(isDeleted){}
Cargo::Cargo(unsigned int id, unsigned int idCategory, unsigned int weight, QString description, unsigned int idTicket, unsigned int size, bool isDeleted) : Id(id), IdCategory(idCategory), Weight(weight), Description(description), IdTicket(idTicket), Size(size), IsDeleted(isDeleted){}
Cargo::Cargo(){}

unsigned int Cargo::getId() const { return this->Id; };
unsigned int Cargo::getIdCategory() const { return this->IdCategory; }
unsigned int Cargo::getWeight() const { return this->Weight; }
unsigned int Cargo::getIdTicket() const { return this->IdTicket; }
unsigned int Cargo::getSize() const { return this->Size; }

QString Cargo::getDescription() const { return this->Description; }

bool Cargo::getIsDeleted() const { return this->IsDeleted; }

void Cargo::setId(unsigned int &id){ this->Id = id; }
void Cargo::setIdCategory(unsigned int &idCategory){ this->IdCategory = idCategory; }
void Cargo::setWeight(unsigned int &weight){ this->Weight = weight; }
void Cargo::setIdTicket(unsigned int &idTicket){ this->IdTicket = idTicket; }
void Cargo::setSize(unsigned int &size){ this->Size = size; }
void Cargo::setDescription(QString &description){ this->Description = description; }
void Cargo::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Cargo::setId(unsigned int id){ this->Id = id; }
void Cargo::setIdCategory(unsigned int idCategory){ this->IdCategory = idCategory; }
void Cargo::setWeight(unsigned int weight){ this->Weight = weight; }
void Cargo::setIdTicket(unsigned int idTicket){ this->IdTicket = idTicket; }
void Cargo::setSize(unsigned int size){ this->Size = size; }
void Cargo::setDescription(QString description){ this->Description = description; }
void Cargo::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
