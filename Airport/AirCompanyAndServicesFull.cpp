#include "AirCompanyAndServicesFull.h"

AirCompanyAndServicesFull::AirCompanyAndServicesFull(unsigned int &servicesId, QString &serviceName, QString &serviceDescription, unsigned int &servicePrice, QString &airCompanyName, bool &servicesIsDeleted) : ServicesId(servicesId), ServiceName(serviceName), ServiceDescription(serviceDescription), ServicePrice(servicePrice), AirCompanyName(airCompanyName), ServicesIsDeleted(servicesIsDeleted){}
AirCompanyAndServicesFull::AirCompanyAndServicesFull(unsigned int servicesId, QString serviceName, QString serviceDescription, unsigned int servicePrice, QString airCompanyName, bool servicesIsDeleted) : ServicesId(servicesId), ServiceName(serviceName), ServiceDescription(serviceDescription), ServicePrice(servicePrice), AirCompanyName(airCompanyName), ServicesIsDeleted(servicesIsDeleted){}
AirCompanyAndServicesFull::AirCompanyAndServicesFull(){}

unsigned int AirCompanyAndServicesFull::getServicesId() const { return this->ServicesId; }
unsigned int AirCompanyAndServicesFull::getServicePrice() const { return this->ServicePrice; } 

QString AirCompanyAndServicesFull::getServiceName() const { return this->ServiceName; }
QString AirCompanyAndServicesFull::getServiceDescription() const { return this->ServiceDescription; }
QString AirCompanyAndServicesFull::getAirCompanyName() const { return this->AirCompanyName; }

bool AirCompanyAndServicesFull::getServicesIsDeleted() const { return this->ServicesIsDeleted; }

void AirCompanyAndServicesFull::setServicesId(unsigned int &servicesId){ this->ServicesId = servicesId; }
void AirCompanyAndServicesFull::setServicePrice(unsigned int &servicePrice){ this->ServicePrice = servicePrice; }
void AirCompanyAndServicesFull::setServiceName(QString &serviceName){ this->ServiceName = serviceName; }
void AirCompanyAndServicesFull::setServiceDescription(QString &serviceDescription){ this->ServiceDescription = serviceDescription; }
void AirCompanyAndServicesFull::setAirCompanyName(QString &airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndServicesFull::setServicesIsDeleted(bool &servicesIsDeleted){ this->ServicesIsDeleted = servicesIsDeleted; }

void AirCompanyAndServicesFull::setServicesId(unsigned int servicesId){ this->ServicesId = servicesId; }
void AirCompanyAndServicesFull::setServicePrice(unsigned int servicePrice){ this->ServicePrice = servicePrice; }
void AirCompanyAndServicesFull::setServiceName(QString serviceName){ this->ServiceName = serviceName; }
void AirCompanyAndServicesFull::setServiceDescription(QString serviceDescription){ this->ServiceDescription = serviceDescription; }
void AirCompanyAndServicesFull::setAirCompanyName(QString airCompanyName){ this->AirCompanyName = airCompanyName; }
void AirCompanyAndServicesFull::setServicesIsDeleted(bool servicesIsDeleted){ this->ServicesIsDeleted = servicesIsDeleted; }
