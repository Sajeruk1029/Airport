#include "AirCompanyAndServicesTrunc.h"

AirCompanyAndServicesTrunc::AirCompanyAndServicesTrunc(unsigned int &servicesId, QString &serviceName, unsigned int &servicePrice, QString &airCompanyName, bool &servicesIsDeleted) : ServicesId(servicesId), ServiceName(serviceName), ServicePrice(servicePrice), AirCompanyName(airCompanyName), ServicesIsDeleted(servicesIsDeleted){}
AirCompanyAndServicesTrunc::AirCompanyAndServicesTrunc(unsigned int servicesId, QString serviceName, unsigned int servicePrice, QString airCompanyName, bool servicesIsDeleted) : ServicesId(servicesId), ServiceName(serviceName), ServicePrice(servicePrice), AirCompanyName(airCompanyName), ServicesIsDeleted(servicesIsDeleted){}
AirCompanyAndServicesTrunc::AirCompanyAndServicesTrunc(){}

unsigned int AirCompanyAndServicesTrunc::getServicesId() const { return this->ServicesId; }
unsigned int AirCompanyAndServicesTrunc::getServicePrice() const { return this->ServicePrice; } 

QString AirCompanyAndServicesTrunc::getServiceName() const { return this->ServiceName; }
QString AirCompanyAndServicesTrunc::getAirCompanyName() const { return this->AirCompanyName; }

bool AirCompanyAndServicesTrunc::getServicesIsDeleted() const { return this->ServicesIsDeleted; }

void AirCompanyAndServicesTrunc::setServicesId(unsigned int &servicesId){ this->ServicesId = servicesId; }
void AirCompanyAndServicesTrunc::setServicePrice(unsigned int &servicePrice){ this->ServicePrice = servicePrice; }
void AirCompanyAndServicesTrunc::setServiceName(QString &serviceName){ this->ServiceName = serviceName; }
void AirCompanyAndServicesTrunc::setAirCompanyName(QString &airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndServicesTrunc::setServicesIsDeleted(bool &servicesIsDeleted){ this->ServicesIsDeleted = servicesIsDeleted; }

void AirCompanyAndServicesTrunc::setServicesId(unsigned int servicesId){ this->ServicesId = servicesId; }
void AirCompanyAndServicesTrunc::setServicePrice(unsigned int servicePrice){ this->ServicePrice = servicePrice; }
void AirCompanyAndServicesTrunc::setServiceName(QString serviceName){ this->ServiceName = serviceName; }
void AirCompanyAndServicesTrunc::setAirCompanyName(QString airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndServicesTrunc::setServicesIsDeleted(bool servicesIsDeleted){ this->ServicesIsDeleted = servicesIsDeleted; }
