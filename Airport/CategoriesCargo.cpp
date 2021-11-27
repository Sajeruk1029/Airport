#include "CategoriesCargo.h"

CategoriesCargo::CategoriesCargo(unsigned int &id, QString &name, QString &description, bool &isDeleted) : Id(id), Name(name), Description(description), IsDeleted(isDeleted){}
CategoriesCargo::CategoriesCargo(unsigned int id, QString name, QString description, bool isDeleted) : Id(id), Name(name), Description(description), IsDeleted(isDeleted){}
CategoriesCargo::CategoriesCargo(){};

unsigned int CategoriesCargo::getId() const { return this->Id; }

QString CategoriesCargo::getName() const { return this->Name; }
QString CategoriesCargo::getDescription() const { return this->Description; }

bool CategoriesCargo::getIsDeleted() const { return this->IsDeleted; }

void CategoriesCargo::setId(unsigned int &id){ this->Id = id; }
void CategoriesCargo::setName(QString &name){ this->Name = name; }
void CategoriesCargo::setDescription(QString &description){ this->Description = description; }
void CategoriesCargo::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void CategoriesCargo::setId(unsigned int id){ this->Id = id; }
void CategoriesCargo::setName(QString name){ this->Name = name; }
void CategoriesCargo::setDescription(QString description){ this->Description = description; }
void CategoriesCargo::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
