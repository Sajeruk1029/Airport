#include "PlacesOfAirports.h"

PlacesOfAirports::PlacesOfAirports(unsigned int &id, QString &country, QString &city, QString &street, unsigned int &houseNumber, bool &isDeleted) : Id(id), Country(country), City(city), Street(street), HouseNumber(houseNumber), IsDeleted(isDeleted){}
PlacesOfAirports::PlacesOfAirports(unsigned int id, QString country, QString city, QString street, unsigned int houseNumber, bool isDeleted) : Id(id), Country(country), City(city), Street(street), HouseNumber(houseNumber), IsDeleted(isDeleted){}
PlacesOfAirports::PlacesOfAirports(){}

unsigned int PlacesOfAirports::getId() const { return this->Id; }
unsigned int PlacesOfAirports::getHouseNumber() const { return this->HouseNumber; }

QString PlacesOfAirports::getCountry() const { return this->Country; }
QString PlacesOfAirports::getCity() const { return this->City; }
QString PlacesOfAirports::getStreet() const { return this->Street; }

bool PlacesOfAirports::getIsDeleted() const { return this->IsDeleted; }

void PlacesOfAirports::setId(unsigned int &id){ this->Id = id; }
void PlacesOfAirports::setHouseNumber(unsigned int &houseNumber){ this->HouseNumber = houseNumber; }
void PlacesOfAirports::setCountry(QString &country){ this->Country = country; }
void PlacesOfAirports::setCity(QString &city){ this->City = city; }
void PlacesOfAirports::setStreet(QString &street){ this->Street = street; }
void PlacesOfAirports::setIsDeleted(bool &isDeleted){ this->IsDeleted = isDeleted; }

void PlacesOfAirports::setId(unsigned int id){ this->Id = id; }
void PlacesOfAirports::setHouseNumber(unsigned int houseNumber){ this->HouseNumber = houseNumber; }
void PlacesOfAirports::setCountry(QString country){ this->Country = country; }
void PlacesOfAirports::setCity(QString city){ this->City = city; }
void PlacesOfAirports::setStreet(QString street){ this->Street = street; }
void PlacesOfAirports::setIsDeleted(bool isDeleted){ this->IsDeleted = isDeleted; }
