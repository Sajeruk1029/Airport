#include "ClientAndBaggage.h"

ClientAndBaggage::ClientAndBaggage(unsigned int &id, unsigned int &idClient, unsigned int &idBaggage, bool &isDeleted) : Id(id), IdClient(idClient), IdBaggage(idBaggage), IsDeleted(isDeleted){}
ClientAndBaggage::ClientAndBaggage(unsigned int id, unsigned int idClient, unsigned int idBaggage, bool isDeleted) : Id(id), IdClient(idClient), IdBaggage(idBaggage), IsDeleted(isDeleted){}
ClientAndBaggage::ClientAndBaggage(){}

unsigned int ClientAndBaggage::getId() const { return this->Id; }
unsigned int ClientAndBaggage::getIdClient() const { return this->IdClient; }
unsigned int ClientAndBaggage::getIdBaggage() const { return this->IdBaggage; }

bool ClientAndBaggage::getIsDeleted() const { return this->IsDeleted; }

void ClientAndBaggage::setId(unsigned int &id){ this->Id = id; }
void ClientAndBaggage::setIdClient(unsigned int &idClient){ this->IdClient = idClient; }
void ClientAndBaggage::setIdBaggage(unsigned int &idBaggage){ this->IdBaggage = idBaggage; }
void ClientAndBaggage::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void ClientAndBaggage::setId(unsigned int id){ this->Id = id; }
void ClientAndBaggage::setIdClient(unsigned int idClient){ this->IdClient = idClient; }
void ClientAndBaggage::setIdBaggage(unsigned int idBaggage){ this->IdBaggage = idBaggage; }
void ClientAndBaggage::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
