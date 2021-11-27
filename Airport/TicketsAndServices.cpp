#include "TicketsAndServices.h"

TicketsAndServices::TicketsAndServices(unsigned int &id, unsigned int &idService, unsigned int &idTicket, bool &isDeleted) : Id(id), IdService(idService), IdTicket(idTicket), IsDeleted(isDeleted){}
TicketsAndServices::TicketsAndServices(unsigned int id, unsigned int idService, unsigned int idTicket, bool isDeleted) : Id(id), IdService(idService), IdTicket(idTicket), IsDeleted(isDeleted){}
TicketsAndServices::TicketsAndServices(){}

unsigned int TicketsAndServices::getId() const { return this->Id; }
unsigned int TicketsAndServices::getIdService() const { return this->IdService; }
unsigned int TicketsAndServices::getIdTicket() const { return this->IdTicket; }

bool TicketsAndServices::getIsDeleted() const { return this->IsDeleted; }

void TicketsAndServices::setId(unsigned int &id){ this->Id = id; }
void TicketsAndServices::setIdService(unsigned int &idService){ this->IdService = idService; }
void TicketsAndServices::setIdTicket(unsigned int &idTicket){ this->IdTicket = idTicket; }
void TicketsAndServices::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void TicketsAndServices::setId(unsigned int id){ this->Id = id; }
void TicketsAndServices::setIdService(unsigned int idService){ this->IdService = idService; }
void TicketsAndServices::setIdTicket(unsigned int idTicket){ this->IdTicket = idTicket; }
void TicketsAndServices::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
