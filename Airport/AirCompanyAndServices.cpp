#include "AirCompanyAndServices.h"

AirCompanyAndServices::AirCompanyAndServices(unsigned int &id, unsigned int &idAirCompany, unsigned int &idService, bool &isDeleted) : Id(id), IdAirCompany(idAirCompany), IdService(idService), IsDeleted(isDeleted){}
AirCompanyAndServices::AirCompanyAndServices(unsigned int id, unsigned int idAirCompany, unsigned int idService, bool isDeleted) : Id(id), IdAirCompany(idAirCompany), IdService(idService), IsDeleted(isDeleted){}
AirCompanyAndServices::AirCompanyAndServices(){}

unsigned int AirCompanyAndServices::getId() const { return this->Id; }
unsigned int AirCompanyAndServices::getIdAirCompany() const { return this->IdAirCompany; }
unsigned int AirCompanyAndServices::getIdService() const { return this->IdService; }
bool AirCompanyAndServices::getIsDeleted() const { return this->IsDeleted; }

void AirCompanyAndServices::setId(unsigned int &id){ this->Id = id; }
void AirCompanyAndServices::setIdAirCompany(unsigned int &idAirCompany){ this->IdAirCompany = idAirCompany; }
void AirCompanyAndServices::setIdService(unsigned int &idService){ this->IdService = idService; }
void AirCompanyAndServices::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void AirCompanyAndServices::setId(unsigned int id){ this->Id = id; }
void AirCompanyAndServices::setIdAirCompany(unsigned int idAirCompany){ this->IdAirCompany = idAirCompany; }
void AirCompanyAndServices::setIdService(unsigned int idService){ this->IdService = idService; }
void AirCompanyAndServices::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
