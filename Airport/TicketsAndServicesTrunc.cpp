#include "TicketsAndServicesTrunc.h"

TicketsAndServicesTrunc::TicketsAndServicesTrunc(unsigned int &ticketsId, unsigned int &ticketsPrice, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, QString &servicesName, unsigned int &servicesPrice, unsigned int &ticketsSeatNumber, bool &ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ServicesName(servicesName), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesTrunc::TicketsAndServicesTrunc(unsigned int ticketsId, unsigned int ticketsPrice, QString clientFirstName, QString clientLastName, QString clientPatronymic, QString servicesName, unsigned int servicesPrice, unsigned int ticketsSeatNumber, bool ticketsIsDeleted) : TicketsId(ticketsId), TicketsPrice(ticketsPrice), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ServicesName(servicesName), ServicesPrice(servicesPrice), TicketsSeatNumber(ticketsSeatNumber), TicketsIsDeleted(ticketsIsDeleted){}
TicketsAndServicesTrunc::TicketsAndServicesTrunc(){}

unsigned int TicketsAndServicesTrunc::getTicketsId() const { return this->TicketsId; }
unsigned int TicketsAndServicesTrunc::getTicketsPrice() const { return this->TicketsPrice; }
unsigned int TicketsAndServicesTrunc::getServicesPrice() const { return this->ServicesPrice; }
unsigned int TicketsAndServicesTrunc::getTicketsSeatNumber() const { return this->TicketsSeatNumber; }

QString TicketsAndServicesTrunc::getClientFirstName() const { return this->ClientFirstName; }
QString TicketsAndServicesTrunc::getClientLastName() const { return this->ClientLastName; }
QString TicketsAndServicesTrunc::getClientPatronymic() const { return this->ClientPatronymic; }
QString TicketsAndServicesTrunc::getServicesName() const { return this->ServicesName; }

bool TicketsAndServicesTrunc::getTicketsIsDeleted() const { return this->TicketsIsDeleted; }

void TicketsAndServicesTrunc::setTicketsId(unsigned int &ticketsId){ this->TicketsId = ticketsId; }
void TicketsAndServicesTrunc::setTicketsPrice(unsigned int &ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsAndServicesTrunc::setServicesPrice(unsigned int &servicesPrice){ this->ServicesPrice = servicesPrice; }
void TicketsAndServicesTrunc::setTicketsSeatNumber(unsigned int &ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsAndServicesTrunc::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsAndServicesTrunc::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void TicketsAndServicesTrunc::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsAndServicesTrunc::setServicesName(QString &servicesName){ this->ServicesName = servicesName; }

void TicketsAndServicesTrunc::setTicketsIsDeleted(bool &ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }

void TicketsAndServicesTrunc::setTicketsId(unsigned int ticketsId){ this->TicketsId = ticketsId; }
void TicketsAndServicesTrunc::setTicketsPrice(unsigned int ticketsPrice){ this->TicketsPrice = ticketsPrice; }
void TicketsAndServicesTrunc::setServicesPrice(unsigned int servicesPrice){ this->ServicesPrice = servicesPrice; }
void TicketsAndServicesTrunc::setTicketsSeatNumber(unsigned int ticketsSeatNumber){ this->TicketsSeatNumber = ticketsSeatNumber; }

void TicketsAndServicesTrunc::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void TicketsAndServicesTrunc::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void TicketsAndServicesTrunc::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void TicketsAndServicesTrunc::setServicesName(QString servicesName){ this->ServicesName = servicesName; }

void TicketsAndServicesTrunc::setTicketsIsDeleted(bool ticketsIsDeleted){ this->TicketsIsDeleted = ticketsIsDeleted; }
