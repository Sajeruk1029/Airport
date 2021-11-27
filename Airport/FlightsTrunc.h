#ifndef FLIGHTSTRUNC_H
#define FLIGHTSTRUNC_H

	#include <QString>
	#include <QDateTime>

	class FlightsTrunc
	{
		public:
                        explicit FlightsTrunc(unsigned int&, QString&, QString&, unsigned int&, bool&);
                        explicit FlightsTrunc(unsigned int, QString, QString, unsigned int, bool);
                        explicit FlightsTrunc(unsigned int&, QDateTime&, QString&, unsigned int&, bool&);
                        explicit FlightsTrunc(unsigned int, QDateTime, QString, unsigned int, bool);
						FlightsTrunc(void);

						unsigned int getFlightsId(void) const;
						unsigned int getFlightsLadder(void) const;

						QDateTime getFlightsDepartureDate(void) const;

						QString getArrivalPoint(void) const;

						bool getFlightsIsDeleted(void) const;

						void setFlightsId(unsigned int&);
						void setFlightsLadder(unsigned int&);

						void setFlightsDepartureDate(QDateTime&);
						void setFlightsDepartureDate(QString&);

						void setArrivalPoint(QString&);

						void setFlightsIsDeleted(bool&);

						void setFlightsId(unsigned int);
						void setFlightsLadder(unsigned int);

						void setFlightsDepartureDate(QDateTime);
						void setFlightsDepartureDate(QString);

						void setArrivalPoint(QString);

						void setFlightsIsDeleted(bool);

		private:
						unsigned int FlightsId;
						unsigned int FlightsLadder;

						QDateTime FlightsDepartureDate;

						QString ArrivalPoint;

						bool FlightsIsDeleted;
	};

#endif
