#include "ClientFull.h"

ClientFull::ClientFull(unsigned int &ClientId, QString &ClientFirstName, QString &ClientLastName, QString &ClientPatronymic, unsigned short &ClientPassportSeries, unsigned int &ClientPassportNumber, QString &accountLogin, QString &accountPassword, unsigned int &ClientMoney, bool &ClientIsDeleted) : ClientId(ClientId), ClientFirstName(ClientFirstName), ClientLastName(ClientLastName), ClientPatronymic(ClientPatronymic), ClientPassportSeries(ClientPassportSeries), ClientPassportNumber(ClientPassportNumber), AccountLogin(accountLogin), AccountPassword(accountPassword), ClientMoney(ClientMoney), ClientIsDeleted(ClientIsDeleted){}
ClientFull::ClientFull(unsigned int ClientId, QString ClientFirstName, QString ClientLastName, QString ClientPatronymic, unsigned short ClientPassportSeries, unsigned int ClientPassportNumber, QString accountLogin, QString accountPassword, unsigned int ClientMoney, bool ClientIsDeleted) : ClientId(ClientId), ClientFirstName(ClientFirstName), ClientLastName(ClientLastName), ClientPatronymic(ClientPatronymic), ClientPassportSeries(ClientPassportSeries), ClientPassportNumber(ClientPassportNumber), AccountLogin(accountLogin), AccountPassword(accountPassword), ClientMoney(ClientMoney), ClientIsDeleted(ClientIsDeleted){}
ClientFull::ClientFull(){}

unsigned int ClientFull::getClientId() const { return this->ClientId; }
unsigned int ClientFull::getClientMoney() const { return this->ClientMoney; }
unsigned int ClientFull::getClientPassportNumber() const { return this->ClientPassportNumber; }

unsigned short ClientFull::getClientPassportSeries() const { return this->ClientPassportSeries; }

QString ClientFull::getClientFirstName() const { return this->ClientFirstName; }
QString ClientFull::getClientLastName() const { return this->ClientLastName; }
QString ClientFull::getClientPatronymic() const { return this->ClientPatronymic; }

QString ClientFull::getAccountLogin() const { return this->AccountLogin; }
QString ClientFull::getAccountPassword() const { return this->AccountPassword; }

bool ClientFull::getClientIsDeleted() const { return this->ClientIsDeleted; }

void ClientFull::setClientId(unsigned int &ClientId){ this->ClientId = ClientId; }
void ClientFull::setClientMoney(unsigned int &ClientMoney){ this->ClientMoney = ClientMoney; }
void ClientFull::setClientPassportNumber(unsigned int &ClientPassportNumber){ this->ClientPassportNumber = ClientPassportNumber; }

void ClientFull::setClientPassportSeries(unsigned short &ClientPassportSeries){ this->ClientPassportSeries = ClientPassportSeries; }

void ClientFull::setClientFirstName(QString &ClientFirstName){ this->ClientFirstName = ClientFirstName; }
void ClientFull::setClientLastName(QString &ClientLastName){ this->ClientLastName = ClientLastName; }
void ClientFull::setClientPatronymic(QString &ClientPatronymic){ this->ClientPatronymic = ClientPatronymic; }
void ClientFull::setAccountLogin(QString &accountLogin){ this->AccountLogin = accountLogin; }
void ClientFull::setAccountPassword(QString &accountPassword){ this->AccountPassword = accountPassword; }

void ClientFull::setClientIsDeleted(bool &ClientIsDeleted){ this->ClientIsDeleted = ClientIsDeleted; }

void ClientFull::setClientId(unsigned int ClientId){ this->ClientId = ClientId; }
void ClientFull::setClientMoney(unsigned int ClientMoney){ this->ClientMoney = ClientMoney; }
void ClientFull::setClientPassportNumber(unsigned int ClientPassportNumber){ this->ClientPassportNumber = ClientPassportNumber; }

void ClientFull::setClientPassportSeries(unsigned short ClientPassportSeries){ this->ClientPassportSeries = ClientPassportSeries; }

void ClientFull::setClientFirstName(QString ClientFirstName){ this->ClientFirstName = ClientFirstName; }
void ClientFull::setClientLastName(QString ClientLastName){ this->ClientLastName = ClientLastName; }
void ClientFull::setClientPatronymic(QString ClientPatronymic){ this->ClientPatronymic = ClientPatronymic; }
void ClientFull::setAccountLogin(QString accountLogin){ this->AccountLogin = accountLogin; }
void ClientFull::setAccountPassword(QString accountPassword){ this->AccountPassword = accountPassword; }

void ClientFull::setClientIsDeleted(bool ClientIsDeleted){ this->ClientIsDeleted = ClientIsDeleted; }
