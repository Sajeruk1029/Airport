#include "Accounts.h"

Accounts::Accounts(unsigned int &id, QString &login, QString &password, bool &isDeleted) : Id(id), Login(login), Password(password), IsDeleted(isDeleted){}
Accounts::Accounts(unsigned int id, QString login, QString password, bool isDeleted) : Id(id), Login(login), Password(password), IsDeleted(isDeleted){}
Accounts::Accounts(){}

unsigned int Accounts::getId() const { return this->Id; }

QString Accounts::getLogin() const { return this->Login; }
QString Accounts::getPassword() const { return this->Password; }

bool Accounts::getIsDeleted() const { return this->IsDeleted; }

void Accounts::setId(unsigned int &id){ this->Id = id; }
void Accounts::setLogin(QString &login){ this->Login = login; }
void Accounts::setPassword(QString &password){ this->Password = password; }
void Accounts::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Accounts::setId(unsigned int id){ this->Id = id; }
void Accounts::setLogin(QString login){ this->Login = login; }
void Accounts::setPassword(QString password){ this->Password = password; }
void Accounts::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
