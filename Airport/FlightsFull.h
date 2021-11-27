#ifndef FLIGHTSFULL_H
#define FLIGHTSFULL_H

	#include <QString>
	#include <QDateTime>

	class FlightsFull
	{
		public:
                        explicit FlightsFull(unsigned int&, QString&, QString&, QString&, QString&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit FlightsFull(unsigned int, QString, QString, QString, QString, QString, QString, unsigned int, unsigned int, unsigned int, unsigned int, bool);
                        explicit FlightsFull(unsigned int&, QDateTime&, QDateTime&, QString&, QString&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit FlightsFull(unsigned int, QDateTime, QDateTime, QString, QString, QString, QString, unsigned int, unsigned int, unsigned int, unsigned int, bool);
						FlightsFull(void);

						unsigned int getFlightsId(void) const;
						unsigned int getAirplaneMaxSizeCargo(void) const;
						unsigned int getAirplaneMaxWeightCargo(void) const;
						unsigned int getAirplaneMaxSeatPlaces(void) const;
						unsigned int getFlightsLadder(void) const;

						QDateTime getFlightsArrivalDate(void) const;
						QDateTime getFlightsDepartureDate(void) const;

						QString getDeparturePoint(void) const;
						QString getArrivalPoint(void) const;
						QString getAirplaneName(void) const;
						QString getAirplaneDescription(void) const;

						bool getFlightsIsDeleted(void) const;

						void setFlightsId(unsigned int&);
						void setAirplaneMaxSizeCargo(unsigned int&);
						void setAirplaneMaxWeightCargo(unsigned int&);
						void setAirplaneMaxSeatPlaces(unsigned int&);
						void setFlightsLadder(unsigned int&);

						void setFlightsArrivalDate(QDateTime&);
						void setFlightsDepartureDate(QDateTime&);
						void setFlightsArrivalDate(QString&);
						void setFlightsDepartureDate(QString&);

						void setDeparturePoint(QString&);
						void setArrivalPoint(QString&);
						void setAirplaneName(QString&);
						void setAirplaneDescription(QString&);

						void setFlightsIsDeleted(bool&);

						void setFlightsId(unsigned int);
						void setAirplaneMaxSizeCargo(unsigned int);
						void setAirplaneMaxWeightCargo(unsigned int);
						void setAirplaneMaxSeatPlaces(unsigned int);
						void setFlightsLadder(unsigned int);

						void setFlightsArrivalDate(QDateTime);
						void setFlightsDepartureDate(QDateTime);
						void setFlightsArrivalDate(QString);
						void setFlightsDepartureDate(QString);

						void setDeparturePoint(QString);
						void setArrivalPoint(QString);
						void setAirplaneName(QString);
						void setAirplaneDescription(QString);

						void setFlightsIsDeleted(bool);
		private:
						unsigned int FlightsId;
						unsigned int AirplaneMaxSizeCargo;
						unsigned int AirplaneMaxWeightCargo;
						unsigned int AirplaneMaxSeatPlaces;
						unsigned int FlightsLadder;

						QDateTime FlightsArrivalDate;
						QDateTime FlightsDepartureDate;

						QString DeparturePoint;
						QString ArrivalPoint;
						QString AirplaneName;
						QString AirplaneDescription;

						bool FlightsIsDeleted;
	};

#endif
