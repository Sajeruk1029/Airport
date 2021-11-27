#include "AirCompanyAndAirplane.h"

AirCompanyAndAirplane::AirCompanyAndAirplane(unsigned int &id, unsigned int &idAirplane, unsigned int &idAirCompany, bool &isDeleted) : Id(id), IdAirplane(idAirplane), IdAirCompany(idAirCompany), IsDeleted(isDeleted){}
AirCompanyAndAirplane::AirCompanyAndAirplane(unsigned int id, unsigned int idAirplane, unsigned int idAirCompany, bool isDeleted) : Id(id), IdAirplane(idAirplane), IdAirCompany(idAirCompany), IsDeleted(isDeleted){}
AirCompanyAndAirplane::AirCompanyAndAirplane(){}

unsigned int AirCompanyAndAirplane::getId() const { return this->Id; }
unsigned int AirCompanyAndAirplane::getIdAirplane() const { return this->IdAirplane; }
unsigned int AirCompanyAndAirplane::getIdAirCompany() const { return this->IdAirCompany; }

bool AirCompanyAndAirplane::getIsDeleted() const { return this->IsDeleted; }

void AirCompanyAndAirplane::setId(unsigned int &id){ this->Id = id; }
void AirCompanyAndAirplane::setIdAirplane(unsigned int &idAirplane){ this->IdAirplane = idAirplane; }
void AirCompanyAndAirplane::setIdAirCompany(unsigned int &idAirCompany){ this->IdAirCompany = idAirCompany; }
void AirCompanyAndAirplane::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void AirCompanyAndAirplane::setId(unsigned int id){ this->Id = id; }
void AirCompanyAndAirplane::setIdAirplane(unsigned int idAirplane){ this->IdAirplane = idAirplane; }
void AirCompanyAndAirplane::setIdAirCompany(unsigned int idAirCompany){ this->IdAirCompany = idAirCompany; }
void AirCompanyAndAirplane::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
