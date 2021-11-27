#ifndef CARGOFULL_H
#define CARGOFULL_H

	#include <QString>
	#include <QDateTime>

	class CargoFull
	{
		public:
                        explicit CargoFull(unsigned int&, QString&, unsigned int&, unsigned int&, QString&, QString&, QString&, QString&, unsigned short&, unsigned int&, QString&, QString&, QString&, QString&, unsigned int&, bool&);
                        explicit CargoFull(unsigned int, QString, unsigned int, unsigned int, QString, QString, QString, QString, unsigned short, unsigned int, QString, QString, QString, QString, unsigned int, bool);
                        explicit CargoFull(unsigned int&, QString&, unsigned int&, unsigned int&, QString&, QString&, QString&, QString&, unsigned short&, unsigned int&, QDateTime&, QDateTime&, QString&, QString&, unsigned int&, bool&);
                        explicit CargoFull(unsigned int, QString, unsigned int, unsigned int, QString, QString, QString, QString, unsigned short, unsigned int, QDateTime, QDateTime, QString, QString, unsigned int, bool);
						CargoFull(void);

						unsigned int getCargoId(void) const;
						unsigned int getCargoWeight(void) const;
						unsigned int getCargoSize(void) const;
						unsigned int getClientPassportNumber(void) const;
						unsigned int getFlightsLadder(void) const;

						unsigned short getClientPassportSeries(void) const;

						QString getCargoDescription(void) const;
						QString getCategoriesCargoName(void) const;
						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;
						QString getDeparturePoint(void) const;
						QString getArrivalPoint(void) const;

						QDateTime getFlightsArrivalDate(void) const;
						QDateTime getFlightsDepartureDate(void) const;

						bool getCargoIsDeleted(void) const;

						void setCargoId(unsigned int&);
						void setCargoWeight(unsigned int&);
						void setCargoSize(unsigned int&);
						void setClientPassportNumber(unsigned int&);
						void setFlightsLadder(unsigned int&);
						void setClientPassportSeries(unsigned short&);
						void setCargoDescription(QString&);
						void setCategoriesCargoName(QString&);
						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setDeparturePoint(QString&);
						void setArrivalPoint(QString&);
						void setFlightsArrivalDate(QDateTime&);
						void setFlightsDepartureDate(QDateTime&);
						void setFlightsArrivalDate(QString&);
						void setFlightsDepartureDate(QString&);
						void setCargoIsDeleted(bool&);

						void setCargoId(unsigned int);
						void setCargoWeight(unsigned int);
						void setCargoSize(unsigned int);
						void setClientPassportNumber(unsigned int);
						void setFlightsLadder(unsigned int);
						void setClientPassportSeries(unsigned short);
						void setCargoDescription(QString);
						void setCategoriesCargoName(QString);
						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setDeparturePoint(QString);
						void setArrivalPoint(QString);
						void setFlightsArrivalDate(QDateTime);
						void setFlightsDepartureDate(QDateTime);
						void setFlightsArrivalDate(QString);
						void setFlightsDepartureDate(QString);
						void setCargoIsDeleted(bool);
		private:
						unsigned int CargoId;
						unsigned int CargoWeight;
						unsigned int CargoSize;
						unsigned int ClientPassportNumber;
						unsigned int FlightsLadder;

						unsigned short ClientPassportSeries;

						QString CargoDescription;
						QString CategoriesCargoName;
						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;
						QString DeparturePoint;
						QString ArrivalPoint;

						QDateTime FlightsArrivalDate;
						QDateTime FlightsDepartureDate;

						bool CargoIsDeleted;
	};

#endif
