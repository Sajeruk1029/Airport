#include "Client.h"

Client::Client(unsigned int &id, QString &firstName, QString &lastName, QString &patronymic, unsigned short &passportSeries, unsigned int &passportNumber, unsigned int &account, unsigned int &money, bool &isDeleted) : Id(id), FirstName(firstName), LastName(lastName), Patronymic(patronymic), PassportSeries(passportSeries), PassportNumber(passportNumber), Account(account), Money(money), IsDeleted(isDeleted){}
Client::Client(unsigned int id, QString firstName, QString lastName, QString patronymic, unsigned short passportSeries, unsigned int passportNumber, unsigned int account, unsigned int money, bool isDeleted) : Id(id), FirstName(firstName), LastName(lastName), Patronymic(patronymic), PassportSeries(passportSeries), PassportNumber(passportNumber), Account(account), Money(money), IsDeleted(isDeleted){}
Client::Client(){}

unsigned int Client::getId() const { return this->Id; }
unsigned int Client::getPassportNumber() const { return this->PassportNumber; }
unsigned int Client::getAccount() const { return this->Account; }
unsigned int Client::getMoney() const { return this->Money; }

unsigned short Client::getPassportSeries() const { return this->PassportSeries; }

QString Client::getFirstName() const { return this->FirstName; }
QString Client::getLastName() const { return this->LastName; }
QString Client::getPatronymic() const { return this->Patronymic; }

bool Client::getIsDeleted() const { return this->IsDeleted; }

void Client::setId(unsigned int &id){ this->Id = id; }
void Client::setPassportNumber(unsigned int &passportNumber){ this->PassportNumber = passportNumber; }
void Client::setAccount(unsigned int &account){ this->Account = account; }
void Client::setMoney(unsigned int &money){ this->Money = money; }
void Client::setPassportSeries(unsigned short &passportSeries){ this->PassportSeries = passportSeries; }
void Client::setFirstName(QString &firstName){ this->FirstName = firstName; }
void Client::setLastName(QString &lastName){ this->LastName = lastName; }
void Client::setPatronymic(QString &patronymic){ this->Patronymic = patronymic; }
void Client::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Client::setId(unsigned int id){ this->Id = id; }
void Client::setPassportNumber(unsigned int passportNumber){ this->PassportNumber = passportNumber; }
void Client::setAccount(unsigned int account){ this->Account = account; }
void Client::setMoney(unsigned int money){ this->Money = money; }
void Client::setPassportSeries(unsigned short passportSeries){ this->PassportSeries = passportSeries; }
void Client::setFirstName(QString firstName){ this->FirstName = firstName; }
void Client::setLastName(QString lastName){ this->LastName = lastName; }
void Client::setPatronymic(QString patronymic){ this->Patronymic = patronymic; }
void Client::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
