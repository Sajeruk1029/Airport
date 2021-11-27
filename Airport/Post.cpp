#include "Post.h"

Post::Post(unsigned int &id, QString &name, unsigned int &salary, bool &isDeleted): Id(id), Name(name), Salary(salary), IsDeleted(isDeleted){}
Post::Post(unsigned int id, QString name, unsigned int salary, bool isDeleted): Id(id), Name(name), Salary(salary), IsDeleted(isDeleted){}
Post::Post(){}

unsigned int Post::getId() const { return this->Id; }
unsigned int Post::getSalary() const { return this->Salary; }

QString Post::getName() const { return this->Name; }

bool Post::getIsDeleted() const { return this->IsDeleted; }

void Post::setId(unsigned int &id){ this->Id = id; }
void Post::setSalary(unsigned int &salary){ this->Salary = salary; }
void Post::setName(QString &name){ this->Name = name; }
void Post::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void Post::setId(unsigned int id){ this->Id = id; }
void Post::setSalary(unsigned int salary){ this->Salary = salary; }
void Post::setName(QString name){ this->Name = name; }
void Post::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
