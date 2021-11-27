#include "ClientAndBaggageFull.h"

ClientAndBaggageFull::ClientAndBaggageFull(unsigned int &baggageId, QString &baggageName, QString &baggageDescription, unsigned int &baggageWeight, unsigned int &baggageSize, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, bool &baggageIsDeleted) : BaggageId(baggageId), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), BaggageIsDeleted(baggageIsDeleted){}
ClientAndBaggageFull::ClientAndBaggageFull(unsigned int baggageId, QString baggageName, QString baggageDescription, unsigned int baggageWeight, unsigned int baggageSize, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, bool baggageIsDeleted) : BaggageId(baggageId), BaggageName(baggageName), BaggageDescription(baggageDescription), BaggageWeight(baggageWeight), BaggageSize(baggageSize), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), BaggageIsDeleted(baggageIsDeleted){}
ClientAndBaggageFull::ClientAndBaggageFull(){}

unsigned int ClientAndBaggageFull::getBaggageId() const { return this->BaggageId; }
unsigned int ClientAndBaggageFull::getBaggageWeight() const { return this->BaggageWeight; }
unsigned int ClientAndBaggageFull::getBaggageSize() const { return this->BaggageSize; }
unsigned int ClientAndBaggageFull::getClientPassportNumber() const { return this->ClientPassportNumber; }

unsigned short ClientAndBaggageFull::getClientPassportSeries() const { return this->ClientPassportSeries; }

QString ClientAndBaggageFull::getBaggageName() const { return this->BaggageName; }
QString ClientAndBaggageFull::getBaggageDescription() const { return this->BaggageDescription; }
QString ClientAndBaggageFull::getClientFirstName() const { return this->ClientFirstName; }
QString ClientAndBaggageFull::getClientLastName() const { return this->ClientLastName; }
QString ClientAndBaggageFull::getClientPatronymic() const { return this->ClientPatronymic; }

bool ClientAndBaggageFull::getBaggageIsDeleted() const { return this->BaggageIsDeleted; }

void ClientAndBaggageFull::setBaggageId(unsigned int &baggageId){ this->BaggageId = baggageId; }
void ClientAndBaggageFull::setBaggageWeight(unsigned int &baggageWeight){ this->BaggageWeight = baggageWeight; }
void ClientAndBaggageFull::setBaggageSize(unsigned int &baggageSize){ this->BaggageSize = baggageSize; }
void ClientAndBaggageFull::setClientPassportNumber(unsigned int &clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }

void ClientAndBaggageFull::setClientPassportSeries(unsigned short &clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void ClientAndBaggageFull::setBaggageName(QString &baggageName){ this->BaggageName = baggageName; }
void ClientAndBaggageFull::setBaggageDescription(QString &baggageDescription){ this->BaggageDescription = baggageDescription; }
void ClientAndBaggageFull::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void ClientAndBaggageFull::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void ClientAndBaggageFull::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }

void ClientAndBaggageFull::setBaggageIsDeleted(bool &baggageIsDeleted){ this->BaggageIsDeleted = baggageIsDeleted; }

void ClientAndBaggageFull::setBaggageId(unsigned int baggageId){ this->BaggageId = baggageId; }
void ClientAndBaggageFull::setBaggageWeight(unsigned int baggageWeight){ this->BaggageWeight = baggageWeight; }
void ClientAndBaggageFull::setBaggageSize(unsigned int baggageSize){ this->BaggageSize = baggageSize; }
void ClientAndBaggageFull::setClientPassportNumber(unsigned int clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }

void ClientAndBaggageFull::setClientPassportSeries(unsigned short clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }

void ClientAndBaggageFull::setBaggageName(QString baggageName){ this->BaggageName = baggageName; }
void ClientAndBaggageFull::setBaggageDescription(QString baggageDescription){ this->BaggageDescription = baggageDescription; }
void ClientAndBaggageFull::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void ClientAndBaggageFull::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void ClientAndBaggageFull::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }

void ClientAndBaggageFull::setBaggageIsDeleted(bool baggageIsDeleted){ this->BaggageIsDeleted = baggageIsDeleted; }
