#include "Tickets.h"

Tickets::Tickets(unsigned int &id, unsigned int &price, unsigned int &idClient, unsigned int &seatNumber, unsigned int &flights, bool &baggageAvailable, unsigned int &baggage, bool &isDeleted) : Id(id), Price(price), IdClient(idClient), SeatNumber(seatNumber), Flights(flights), BaggageAvailable(baggageAvailable), Baggage(baggage), IsDeleted(isDeleted){}
Tickets::Tickets(unsigned int id, unsigned int price, unsigned int idClient, unsigned int seatNumber, unsigned int flights, bool baggageAvailable, unsigned int baggage, bool isDeleted) : Id(id), Price(price), IdClient(idClient), SeatNumber(seatNumber), Flights(flights), BaggageAvailable(baggageAvailable), Baggage(baggage), IsDeleted(isDeleted){}
Tickets::Tickets(){}

unsigned int Tickets::getId() const { return this->Id; }
unsigned int Tickets::getPrice() const { return this->Price; }
unsigned int Tickets::getIdClient() const { return this->IdClient; }
unsigned int Tickets::getSeatNumber() const { return this->SeatNumber; }
unsigned int Tickets::getFlights() const { return this->Flights; }
unsigned int Tickets::getBaggage() const { return this->Baggage; }

bool Tickets::getBaggageAvailable() const { return this->Flights; }
bool Tickets::getIsDeleted() const { return this->IsDeleted; }

void Tickets::setId(unsigned int &id){ this->Id = id; }
void Tickets::setPrice(unsigned int &price){ this->Price = price; }
void Tickets::setIdClient(unsigned int &idClient){ this->IdClient = idClient; }
void Tickets::setSeatNumber(unsigned int &seatNumber){ this->SeatNumber = seatNumber; }
void Tickets::setFlights(unsigned int &flights){ this->Flights = flights; }
void Tickets::setBaggage(unsigned int &baggage){ this->Baggage = baggage; }
void Tickets::setBaggageAvailable(bool &baggageAvailable){ this->BaggageAvailable = baggageAvailable; }
void Tickets::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Tickets::setId(unsigned int id){ this->Id = id; }
void Tickets::setPrice(unsigned int price){ this->Price = price; }
void Tickets::setIdClient(unsigned int idClient){ this->IdClient = idClient; }
void Tickets::setSeatNumber(unsigned int seatNumber){ this->SeatNumber = seatNumber; }
void Tickets::setFlights(unsigned int flights){ this->Flights = flights; }
void Tickets::setBaggage(unsigned int baggage){ this->Baggage = baggage; }
void Tickets::setBaggageAvailable(bool baggageAvailable){ this->BaggageAvailable = baggageAvailable; }
void Tickets::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
