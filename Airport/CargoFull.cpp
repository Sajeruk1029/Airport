#include "CargoFull.h"

CargoFull::CargoFull(unsigned int &cargoId, QString &cargoDescription, unsigned int &cargoWeight, unsigned int &cargoSize, QString &categoriesCargoName, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QString &flightsArrivalDate, QString &flightsDepartureDate, QString &departurePoint, QString &arrivalPoint, unsigned int &flightsLadder, bool &cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), CargoIsDeleted(cargoIsDeleted){}
CargoFull::CargoFull(unsigned int cargoId, QString cargoDescription, unsigned int cargoWeight, unsigned int cargoSize, QString categoriesCargoName, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QString flightsArrivalDate, QString flightsDepartureDate, QString departurePoint, QString arrivalPoint, unsigned int flightsLadder, bool cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsArrivalDate(QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss")), FlightsDepartureDate(QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss")), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), CargoIsDeleted(cargoIsDeleted){}
CargoFull::CargoFull(unsigned int &cargoId, QString &cargoDescription, unsigned int &cargoWeight, unsigned int &cargoSize, QString &categoriesCargoName, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, unsigned short &clientPassportSeries, unsigned int &clientPassportNumber, QDateTime &flightsArrivalDate, QDateTime &flightsDepartureDate, QString &departurePoint, QString &arrivalPoint, unsigned int &flightsLadder, bool &cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsArrivalDate(flightsArrivalDate), FlightsDepartureDate(flightsDepartureDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), CargoIsDeleted(cargoIsDeleted){}
CargoFull::CargoFull(unsigned int cargoId, QString cargoDescription, unsigned int cargoWeight, unsigned int cargoSize, QString categoriesCargoName, QString clientFirstName, QString clientLastName, QString clientPatronymic, unsigned short clientPassportSeries, unsigned int clientPassportNumber, QDateTime flightsArrivalDate, QDateTime flightsDepartureDate, QString departurePoint, QString arrivalPoint, unsigned int flightsLadder, bool cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), ClientPassportSeries(clientPassportSeries), ClientPassportNumber(clientPassportNumber), FlightsArrivalDate(flightsArrivalDate), FlightsDepartureDate(flightsDepartureDate), DeparturePoint(departurePoint), ArrivalPoint(arrivalPoint), FlightsLadder(flightsLadder), CargoIsDeleted(cargoIsDeleted){}
CargoFull::CargoFull(){}

unsigned int CargoFull::getCargoId() const { return this->CargoId; }
unsigned int CargoFull::getCargoWeight() const { return this->CargoWeight; }
unsigned int CargoFull::getCargoSize() const { return this->CargoSize; }
unsigned int CargoFull::getClientPassportNumber() const { return this->ClientPassportNumber; }
unsigned int CargoFull::getFlightsLadder() const { return this->FlightsLadder; }

unsigned short CargoFull::getClientPassportSeries() const { return this->ClientPassportSeries; }

QString CargoFull::getCargoDescription() const { return this->CargoDescription; }
QString CargoFull::getCategoriesCargoName() const { return this->CategoriesCargoName; }
QString CargoFull::getClientFirstName() const { return this->ClientFirstName; }
QString CargoFull::getClientLastName() const { return this->ClientLastName; }
QString CargoFull::getClientPatronymic() const { return this->ClientPatronymic; }
QString CargoFull::getDeparturePoint() const { return this->DeparturePoint; }
QString CargoFull::getArrivalPoint() const { return this->ArrivalPoint; }

QDateTime CargoFull::getFlightsArrivalDate() const { return this->FlightsArrivalDate; }
QDateTime CargoFull::getFlightsDepartureDate() const { return this->FlightsDepartureDate; }

bool CargoFull::getCargoIsDeleted() const { return this->CargoIsDeleted; }

void CargoFull::setCargoId(unsigned int &cargoId){ this->CargoId = cargoId; }
void CargoFull::setCargoWeight(unsigned int &cargoWeight){ this->CargoWeight = cargoWeight; }
void CargoFull::setCargoSize(unsigned int &cargoSize){ this->CargoSize = cargoSize; }
void CargoFull::setClientPassportNumber(unsigned int &clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void CargoFull::setFlightsLadder(unsigned int &flightsLadder){ this->FlightsLadder = flightsLadder; }
void CargoFull::setClientPassportSeries(unsigned short &clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }
void CargoFull::setCargoDescription(QString &cargoDescription){ this->CargoDescription = cargoDescription; }
void CargoFull::setCategoriesCargoName(QString &categoriesCargoName){ this->CategoriesCargoName = categoriesCargoName; }
void CargoFull::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void CargoFull::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void CargoFull::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void CargoFull::setDeparturePoint(QString &departurePoint){ this->DeparturePoint = departurePoint; }
void CargoFull::setArrivalPoint(QString &arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void CargoFull::setFlightsArrivalDate(QDateTime &flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void CargoFull::setFlightsDepartureDate(QDateTime &flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void CargoFull::setFlightsArrivalDate(QString &flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void CargoFull::setFlightsDepartureDate(QString &flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void CargoFull::setCargoIsDeleted(bool &cargoIsDeleted){ this->CargoIsDeleted = cargoIsDeleted; }

void CargoFull::setCargoId(unsigned int cargoId){ this->CargoId = cargoId; }
void CargoFull::setCargoWeight(unsigned int cargoWeight){ this->CargoWeight = cargoWeight; }
void CargoFull::setCargoSize(unsigned int cargoSize){ this->CargoSize = cargoSize; }
void CargoFull::setClientPassportNumber(unsigned int clientPassportNumber){ this->ClientPassportNumber = clientPassportNumber; }
void CargoFull::setFlightsLadder(unsigned int flightsLadder){ this->FlightsLadder = flightsLadder; }
void CargoFull::setClientPassportSeries(unsigned short clientPassportSeries){ this->ClientPassportSeries = clientPassportSeries; }
void CargoFull::setCargoDescription(QString cargoDescription){ this->CargoDescription = cargoDescription; }
void CargoFull::setCategoriesCargoName(QString categoriesCargoName){ this->CategoriesCargoName = categoriesCargoName; }
void CargoFull::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void CargoFull::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void CargoFull::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void CargoFull::setDeparturePoint(QString departurePoint){ this->DeparturePoint = departurePoint; }
void CargoFull::setArrivalPoint(QString arrivalPoint){ this->ArrivalPoint = arrivalPoint; }
void CargoFull::setFlightsArrivalDate(QDateTime flightsArrivalDate){ this->FlightsArrivalDate = flightsArrivalDate; }
void CargoFull::setFlightsDepartureDate(QDateTime flightsDepartureDate){ this->FlightsDepartureDate = flightsDepartureDate; }
void CargoFull::setFlightsArrivalDate(QString flightsArrivalDate){ this->FlightsArrivalDate = QDateTime::fromString(flightsArrivalDate, "yyyy-MM-dd hh:mm:ss"); }
void CargoFull::setFlightsDepartureDate(QString flightsDepartureDate){ this->FlightsDepartureDate = QDateTime::fromString(flightsDepartureDate, "yyyy-MM-dd hh:mm:ss"); }
void CargoFull::setCargoIsDeleted(bool cargoIsDeleted){ this->CargoIsDeleted = cargoIsDeleted; }
