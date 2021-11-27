#ifndef FLIGHTS_H
#define FLIGHTS_H

	#include <QString>
	#include <QDateTime>

	class Flights
	{
		public:
                        explicit Flights(unsigned int&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit Flights(unsigned int, QString, QString, unsigned int, unsigned int, unsigned int, unsigned int, bool);
                        explicit Flights(unsigned int&, QDateTime&, QDateTime&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit Flights(unsigned int, QDateTime, QDateTime, unsigned int, unsigned int, unsigned int, unsigned int, bool);
						Flights(void);

						unsigned int getId(void) const;
						unsigned int getDeparturePoint(void) const;
						unsigned int getArrivalPoint(void) const;
						unsigned int getAirplane(void) const;
						unsigned int getLadder(void) const;

						QDateTime getDepartureDate(void) const;
						QDateTime getArrivalDate(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setDeparturePoint(unsigned int&);
						void setArrivalPoint(unsigned int&);
						void setAirplane(unsigned int&);
						void setLadder(unsigned int&);
						void setDepartureDate(QDateTime&);
						void setArrivalDate(QDateTime&);
						void setDepartureDate(QString&);
						void setArrivalDate(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setDeparturePoint(unsigned int);
						void setArrivalPoint(unsigned int);
						void setAirplane(unsigned int);
						void setLadder(unsigned int);
						void setDepartureDate(QDateTime);
						void setArrivalDate(QDateTime);
						void setDepartureDate(QString);
						void setArrivalDate(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int DeparturePoint;
						unsigned int ArrivalPoint;
						unsigned int Airplane;
						unsigned int Ladder;

						QDateTime DepartureDate;
						QDateTime ArrivalDate;

						bool IsDeleted;
	};

#endif
