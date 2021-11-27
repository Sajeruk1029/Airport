#include "Staff.h"

Staff::Staff(unsigned int &id, QString &firstName, QString &lastName, QString &patronymic, unsigned int &post, unsigned short &passportSeries, unsigned int &passportNumber, unsigned int &account, QString &education, bool &isDeleted) : Id(id), FirstName(firstName), LastName(lastName), Patronymic(patronymic), PassportSeries(passportSeries), PassportNumber(passportNumber), Account(account), Post(post), Education(education), IsDeleted(isDeleted){}
Staff::Staff(unsigned int id, QString firstName, QString lastName, QString patronymic, unsigned int post, unsigned short passportSeries, unsigned int passportNumber, unsigned int account, QString education, bool isDeleted) : Id(id), FirstName(firstName), LastName(lastName), Patronymic(patronymic), PassportSeries(passportSeries), PassportNumber(passportNumber), Account(account), Post(post), Education(education), IsDeleted(isDeleted){}
Staff::Staff(){}

unsigned int Staff::getId() const { return this->Id; }
unsigned int Staff::getPassportNumber() const { return this->PassportNumber; }
unsigned int Staff::getAccount() const { return this->Account; }
unsigned int Staff::getPost() const { return this->Post; }

unsigned short Staff::getPassportSeries() const { return this->PassportSeries; }

QString Staff::getFirstName() const { return this->FirstName; }
QString Staff::getLastName() const { return this->LastName; }
QString Staff::getPatronymic() const { return this->Patronymic; }
QString Staff::getEducation() const { return this->Education; }

bool Staff::getIsDeleted() const { return this->IsDeleted; }

void Staff::setId(unsigned int &id){ this->Id = id; }
void Staff::setPassportNumber(unsigned int &passportNumber){ this->PassportNumber = passportNumber; }
void Staff::setAccount(unsigned int &account){ this->Account = account; }
void Staff::setPost(unsigned int &post){ this->Post = post; }
void Staff::setPassportSeries(unsigned short &passportSeries){ this->PassportSeries = passportSeries; }
void Staff::setFirstName(QString &firstName){ this->FirstName = firstName; }
void Staff::setLastName(QString &lastName){ this->LastName = lastName; }
void Staff::setPatronymic(QString &patronymic){ this->Patronymic = patronymic; }
void Staff::setEducation(QString &education){ this->Education = education; }
void Staff::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }


void Staff::setId(unsigned int id){ this->Id = id; }
void Staff::setPassportNumber(unsigned int passportNumber){ this->PassportNumber = passportNumber; }
void Staff::setAccount(unsigned int account){ this->Account = account; }
void Staff::setPost(unsigned int post){ this->Post = post; }
void Staff::setPassportSeries(unsigned short passportSeries){ this->PassportSeries = passportSeries; }
void Staff::setFirstName(QString firstName){ this->FirstName = firstName; }
void Staff::setLastName(QString lastName){ this->LastName = lastName; }
void Staff::setPatronymic(QString patronymic){ this->Patronymic = patronymic; }
void Staff::setEducation(QString education){ this->Education = education; }
void Staff::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
