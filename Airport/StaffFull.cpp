#include "StaffFull.h"

StaffFull::StaffFull(unsigned int &staffId, QString &staffFirstName, QString &staffLastName, QString &staffPatronymic, QString &postName, unsigned int &postSalary, unsigned short &staffPassportSeries, unsigned int &staffPassportNumber, QString &staffEducation, QString &accountLogin, QString &accountPassword, bool &staffIsDeleted) : StaffId(staffId), StaffFirstName(staffFirstName), StaffLastName(staffLastName), StaffPatronymic(staffPatronymic), PostName(postName), PostSalary(postSalary), StaffPassportSeries(staffPassportSeries), StaffPassportNumber(staffPassportNumber), StaffEducation(staffEducation), AccountLogin(accountLogin), AccountPassword(accountPassword),	StaffIsDeleted(staffIsDeleted){}
StaffFull::StaffFull(unsigned int staffId, QString staffFirstName, QString staffLastName, QString staffPatronymic, QString postName, unsigned int postSalary, unsigned short staffPassportSeries, unsigned int staffPassportNumber, QString staffEducation, QString accountLogin, QString accountPassword, bool staffIsDeleted) : StaffId(staffId), StaffFirstName(staffFirstName), StaffLastName(staffLastName), StaffPatronymic(staffPatronymic), PostName(postName), PostSalary(postSalary), StaffPassportSeries(staffPassportSeries), StaffPassportNumber(staffPassportNumber), StaffEducation(staffEducation), AccountLogin(accountLogin), AccountPassword(accountPassword),	StaffIsDeleted(staffIsDeleted){}
StaffFull::StaffFull(){}

unsigned int StaffFull::getStaffId() const { return this->StaffId; }
unsigned int StaffFull::getPostSalary() const { return this->PostSalary; }
unsigned int StaffFull::getStaffPassportNumber() const { return this->StaffPassportNumber; }

unsigned short StaffFull::getStaffPassportSeries() const { return this->StaffPassportSeries; }

QString StaffFull::getStaffFirstName() const { return this->StaffFirstName; }
QString StaffFull::getStaffLastName() const { return this->StaffLastName; }
QString StaffFull::getStaffPatronymic() const { return this->StaffPatronymic; }
QString StaffFull::getPostName() const { return this->PostName; }
QString StaffFull::getStaffEducation() const { return this->StaffEducation; }
QString StaffFull::getAccountLogin() const { return this->AccountLogin; }
QString StaffFull::getAccountPassword() const { return this->AccountPassword; }

bool StaffFull::getStaffIsDeleted() const { return this->StaffIsDeleted; }

void StaffFull::setStaffId(unsigned int &staffId){ this->StaffId = staffId; }
void StaffFull::setPostSalary(unsigned int &postSalary){ this->PostSalary = postSalary; }
void StaffFull::setStaffPassportNumber(unsigned int &staffPassportNumber){ this->StaffPassportNumber = staffPassportNumber; }

void StaffFull::setStaffPassportSeries(unsigned short &staffPassportSeries){ this->StaffPassportSeries = staffPassportSeries; }

void StaffFull::setStaffFirstName(QString &staffFirstName){ this->StaffFirstName = staffFirstName; }
void StaffFull::setStaffLastName(QString &staffLastName){ this->StaffLastName = staffLastName; }
void StaffFull::setStaffPatronymic(QString &staffPatronymic){ this->StaffPatronymic = staffPatronymic; }
void StaffFull::setPostName(QString &postName){ this->PostName = postName; }
void StaffFull::setStaffEducation(QString &staffEducation){ this->StaffEducation = staffEducation; }
void StaffFull::setAccountLogin(QString &accountLogin){ this->AccountLogin = accountLogin; }
void StaffFull::setAccountPassword(QString &accountPassword){ this->AccountPassword = accountPassword; }

void StaffFull::setStaffIsDeleted(bool &staffIsDeleted){ this->StaffIsDeleted = staffIsDeleted; }

void StaffFull::setStaffId(unsigned int staffId){ this->StaffId = staffId; }
void StaffFull::setPostSalary(unsigned int postSalary){ this->PostSalary = postSalary; }
void StaffFull::setStaffPassportNumber(unsigned int staffPassportNumber){ this->StaffPassportNumber = staffPassportNumber; }

void StaffFull::setStaffPassportSeries(unsigned short staffPassportSeries){ this->StaffPassportSeries = staffPassportSeries; }

void StaffFull::setStaffFirstName(QString staffFirstName){ this->StaffFirstName = staffFirstName; }
void StaffFull::setStaffLastName(QString staffLastName){ this->StaffLastName = staffLastName; }
void StaffFull::setStaffPatronymic(QString staffPatronymic){ this->StaffPatronymic = staffPatronymic; }
void StaffFull::setPostName(QString postName){ this->PostName = postName; }
void StaffFull::setStaffEducation(QString staffEducation){ this->StaffEducation = staffEducation; }
void StaffFull::setAccountLogin(QString accountLogin){ this->AccountLogin = accountLogin; }
void StaffFull::setAccountPassword(QString accountPassword){ this->AccountPassword = accountPassword; }

void StaffFull::setStaffIsDeleted(bool staffIsDeleted){ this->StaffIsDeleted = staffIsDeleted; }
