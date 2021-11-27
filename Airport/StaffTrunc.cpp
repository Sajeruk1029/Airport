#include "StaffTrunc.h"

StaffTrunc::StaffTrunc(unsigned int &staffId, QString &staffFirstName, QString &staffLastName, QString &staffPatronymic, QString &postName, unsigned int &postSalary, QString &staffEducation, bool &staffIsDeleted) : StaffId(staffId), StaffFirstName(staffFirstName), StaffLastName(staffLastName), StaffPatronymic(staffPatronymic), PostName(postName), PostSalary(postSalary), StaffEducation(staffEducation), StaffIsDeleted(staffIsDeleted){}
StaffTrunc::StaffTrunc(unsigned int staffId, QString staffFirstName, QString staffLastName, QString staffPatronymic, QString postName, unsigned int postSalary, QString staffEducation, bool staffIsDeleted) : StaffId(staffId), StaffFirstName(staffFirstName), StaffLastName(staffLastName), StaffPatronymic(staffPatronymic), PostName(postName), PostSalary(postSalary), StaffEducation(staffEducation), StaffIsDeleted(staffIsDeleted){}
StaffTrunc::StaffTrunc(){}

unsigned int StaffTrunc::getStaffId() const { return this->StaffId; }
unsigned int StaffTrunc::getPostSalary() const { return this->PostSalary; }

QString StaffTrunc::getStaffFirstName() const { return this->StaffFirstName; }
QString StaffTrunc::getStaffLastName() const { return this->StaffLastName; }
QString StaffTrunc::getStaffPatronymic() const { return this->StaffPatronymic; }
QString StaffTrunc::getPostName() const { return this->PostName; }
QString StaffTrunc::getStaffEducation() const { return this->StaffEducation; }

bool StaffTrunc::getStaffIsDeleted() const { return this->StaffIsDeleted; }

void StaffTrunc::setStaffId(unsigned int &staffId){ this->StaffId = staffId; }
void StaffTrunc::setPostSalary(unsigned int &postSalary){ this->PostSalary = postSalary; }

void StaffTrunc::setStaffFirstName(QString &staffFirstName){ this->StaffFirstName = staffFirstName; }
void StaffTrunc::setStaffLastName(QString &staffLastName){ this->StaffLastName = staffLastName; }
void StaffTrunc::setStaffPatronymic(QString &staffPatronymic){ this->StaffPatronymic = staffPatronymic; }
void StaffTrunc::setPostName(QString &postName){ this->PostName = postName; }
void StaffTrunc::setStaffEducation(QString &staffEducation){ this->StaffEducation = staffEducation; }

void StaffTrunc::setStaffIsDeleted(bool &staffIsDeleted){ this->StaffIsDeleted = staffIsDeleted; }

void StaffTrunc::setStaffId(unsigned int staffId){ this->StaffId = staffId; }
void StaffTrunc::setPostSalary(unsigned int postSalary){ this->PostSalary = postSalary; }

void StaffTrunc::setStaffFirstName(QString staffFirstName){ this->StaffFirstName = staffFirstName; }
void StaffTrunc::setStaffLastName(QString staffLastName){ this->StaffLastName = staffLastName; }
void StaffTrunc::setStaffPatronymic(QString staffPatronymic){ this->StaffPatronymic = staffPatronymic; }
void StaffTrunc::setPostName(QString postName){ this->PostName = postName; }
void StaffTrunc::setStaffEducation(QString staffEducation){ this->StaffEducation = staffEducation; }

void StaffTrunc::setStaffIsDeleted(bool staffIsDeleted){ this->StaffIsDeleted = staffIsDeleted; }
