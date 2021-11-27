#include "ClientAndBaggageTrunc.h"

ClientAndBaggageTrunc::ClientAndBaggageTrunc(unsigned int &baggageId, QString &baggageName, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, bool &baggageIsDeleted) : BaggageId(baggageId), BaggageName(baggageName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), BaggageIsDeleted(baggageIsDeleted){}
ClientAndBaggageTrunc::ClientAndBaggageTrunc(unsigned int baggageId, QString baggageName, QString clientFirstName, QString clientLastName, QString clientPatronymic, bool baggageIsDeleted) : BaggageId(baggageId), BaggageName(baggageName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), BaggageIsDeleted(baggageIsDeleted){}
ClientAndBaggageTrunc::ClientAndBaggageTrunc(){}

unsigned int ClientAndBaggageTrunc::getBaggageId() const { return this->BaggageId; }

QString ClientAndBaggageTrunc::getBaggageName() const { return this->BaggageName; }
QString ClientAndBaggageTrunc::getClientFirstName() const { return this->ClientFirstName; }
QString ClientAndBaggageTrunc::getClientLastName() const { return this->ClientLastName; }
QString ClientAndBaggageTrunc::getClientPatronymic() const { return this->ClientPatronymic; }

bool ClientAndBaggageTrunc::getBaggageIsDeleted() const { return this->BaggageIsDeleted; }

void ClientAndBaggageTrunc::setBaggageId(unsigned int &baggageId){ this->BaggageId = baggageId; }

void ClientAndBaggageTrunc::setBaggageName(QString &baggageName){ this->BaggageName = baggageName; }
void ClientAndBaggageTrunc::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void ClientAndBaggageTrunc::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void ClientAndBaggageTrunc::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }

void ClientAndBaggageTrunc::setBaggageIsDeleted(bool &baggageIsDeleted){ this->BaggageIsDeleted = baggageIsDeleted; }

void ClientAndBaggageTrunc::setBaggageId(unsigned int baggageId){ this->BaggageId = baggageId; }

void ClientAndBaggageTrunc::setBaggageName(QString baggageName){ this->BaggageName = baggageName; }
void ClientAndBaggageTrunc::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void ClientAndBaggageTrunc::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void ClientAndBaggageTrunc::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }

void ClientAndBaggageTrunc::setBaggageIsDeleted(bool baggageIsDeleted){ this->BaggageIsDeleted = baggageIsDeleted; }
