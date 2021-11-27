#include "CargoTrunc.h"

CargoTrunc::CargoTrunc(unsigned int &cargoId, QString &cargoDescription, unsigned int &cargoWeight, unsigned int &cargoSize, QString &categoriesCargoName, QString &clientFirstName, QString &clientLastName, QString &clientPatronymic, bool &cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), CargoIsDeleted(cargoIsDeleted){}
CargoTrunc::CargoTrunc(unsigned int cargoId, QString cargoDescription, unsigned int cargoWeight, unsigned int cargoSize, QString categoriesCargoName, QString clientFirstName, QString clientLastName, QString clientPatronymic, bool cargoIsDeleted) : CargoId(cargoId), CargoDescription(cargoDescription), CargoWeight(cargoWeight), CargoSize(cargoSize), CategoriesCargoName(categoriesCargoName), ClientFirstName(clientFirstName), ClientLastName(clientLastName), ClientPatronymic(clientPatronymic), CargoIsDeleted(cargoIsDeleted){}
CargoTrunc::CargoTrunc(){}

unsigned int CargoTrunc::getCargoId() const { return this->CargoId; }
unsigned int CargoTrunc::getCargoWeight() const { return this->CargoWeight; }
unsigned int CargoTrunc::getCargoSize() const { return this->CargoSize; }

QString CargoTrunc::getCargoDescription() const { return this->CargoDescription; }
QString CargoTrunc::getCategoriesCargoName() const { return this->CategoriesCargoName; }
QString CargoTrunc::getClientFirstName() const { return this->ClientFirstName; }
QString CargoTrunc::getClientLastName() const { return this->ClientLastName; }
QString CargoTrunc::getClientPatronymic() const { return this->ClientPatronymic; }

bool CargoTrunc::getCargoIsDeleted() const { return this->CargoIsDeleted; }

void CargoTrunc::setCargoId(unsigned int &cargoId){ this->CargoId = cargoId; }
void CargoTrunc::setCargoWeight(unsigned int &cargoWeight){ this->CargoWeight = cargoWeight; }
void CargoTrunc::setCargoSize(unsigned int &cargoSize){ this->CargoSize = cargoSize; }
void CargoTrunc::setCargoDescription(QString &cargoDescription){ this->CargoDescription = cargoDescription; }
void CargoTrunc::setCategoriesCargoName(QString &categoriesCargoName){ this->CategoriesCargoName = categoriesCargoName; }
void CargoTrunc::setClientFirstName(QString &clientFirstName){ this->ClientFirstName = clientFirstName; }
void CargoTrunc::setClientLastName(QString &clientLastName){ this->ClientLastName = clientLastName; }
void CargoTrunc::setClientPatronymic(QString &clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void CargoTrunc::setCargoIsDeleted(bool &cargoIsDeleted){ this->CargoIsDeleted = cargoIsDeleted; }

void CargoTrunc::setCargoId(unsigned int cargoId){ this->CargoId = cargoId; }
void CargoTrunc::setCargoWeight(unsigned int cargoWeight){ this->CargoWeight = cargoWeight; }
void CargoTrunc::setCargoSize(unsigned int cargoSize){ this->CargoSize = cargoSize; }
void CargoTrunc::setCargoDescription(QString cargoDescription){ this->CargoDescription = cargoDescription; }
void CargoTrunc::setCategoriesCargoName(QString categoriesCargoName){ this->CategoriesCargoName = categoriesCargoName; }
void CargoTrunc::setClientFirstName(QString clientFirstName){ this->ClientFirstName = clientFirstName; }
void CargoTrunc::setClientLastName(QString clientLastName){ this->ClientLastName = clientLastName; }
void CargoTrunc::setClientPatronymic(QString clientPatronymic){ this->ClientPatronymic = clientPatronymic; }
void CargoTrunc::setCargoIsDeleted(bool cargoIsDeleted){ this->CargoIsDeleted = cargoIsDeleted; }
