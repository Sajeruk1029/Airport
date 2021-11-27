#ifndef TICKETSANDSERVICESFULL_H
#define TICKETSANDSERVICESFULL_H

	#include <QString>
	#include <QDateTime>

	class TicketsAndServicesFull
	{
		public:
                        explicit TicketsAndServicesFull(unsigned int&, unsigned int&, QString&, QString&, QString&, unsigned short&, unsigned int&, QString&, QString&, QString&, QString&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&, QString&, QString&, unsigned int&, unsigned int&, QString&, QString&, unsigned int&, unsigned int&, bool&);
                        explicit TicketsAndServicesFull(unsigned int, unsigned int, QString, QString, QString, unsigned short, unsigned int, QString, QString, QString, QString, QString, QString, unsigned int, unsigned int, unsigned int, unsigned int, bool, QString, QString, unsigned int, unsigned int, QString, QString, unsigned int, unsigned int, bool);
                        explicit TicketsAndServicesFull(unsigned int&, unsigned int&, QString&, QString&, QString&, unsigned short&, unsigned int&, QDateTime&, QDateTime&, QString&, QString&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&, QString&, QString&, unsigned int&, unsigned int&, QString&, QString&, unsigned int&, unsigned int&, bool&);
                        explicit TicketsAndServicesFull(unsigned int, unsigned int, QString, QString, QString, unsigned short, unsigned int, QDateTime, QDateTime, QString, QString, QString, QString, unsigned int, unsigned int, unsigned int, unsigned int, bool, QString, QString, unsigned int, unsigned int, QString, QString, unsigned int, unsigned int, bool);
						TicketsAndServicesFull(void);

						unsigned int getTicketsId(void) const;
						unsigned int getTicketsPrice(void) const;
						unsigned int getClientPassportNumber(void) const;
						unsigned int getAirplaneMaxSizeCargo(void) const;
						unsigned int getAirplaneMaxWeightCargo(void) const;
						unsigned int getAirplaneMaxSeatPlaces(void) const;
						unsigned int getFlightsLadder(void) const;
						unsigned int getBaggageWeight(void) const;
						unsigned int getBaggageSize(void) const;
						unsigned int getServicesPrice(void) const;
						unsigned int getTicketsSeatNumber(void) const;

						unsigned short getClientPassportSeries(void) const;

						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;
						QString getDeparturePoint(void) const;
						QString getArrivalPoint(void) const;
						QString getAirplaneName(void) const;
						QString getAirplaneDescription(void) const;
						QString getBaggageName(void) const;
						QString getBaggageDescription(void) const;
						QString getServicesName(void) const;
						QString getServicesDescription(void) const;

						QDateTime getFlightsDepartureDate(void) const;
						QDateTime getFlightsArrivalDate(void) const;

						bool getTicketsBaggageAvailable(void) const;
						bool getTicketsIsDeleted(void) const;

						void setTicketsId(unsigned int&);
						void setTicketsPrice(unsigned int&);
						void setClientPassportNumber(unsigned int&);
						void setAirplaneMaxSizeCargo(unsigned int&);
						void setAirplaneMaxWeightCargo(unsigned int&);
						void setAirplaneMaxSeatPlaces(unsigned int&);
						void setFlightsLadder(unsigned int&);
						void setBaggageWeight(unsigned int&);
						void setBaggageSize(unsigned int&);
						void setServicesPrice(unsigned int&);
						void setTicketsSeatNumber(unsigned int&);

						void setClientPassportSeries(unsigned short&);

						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setDeparturePoint(QString&);
						void setArrivalPoint(QString&);
						void setAirplaneName(QString&);
						void setAirplaneDescription(QString&);
						void setBaggageName(QString&);
						void setBaggageDescription(QString&);
						void setServicesName(QString&);
						void setServicesDescription(QString&);

						void setFlightsDepartureDate(QDateTime&);
						void setFlightsArrivalDate(QDateTime&);
						void setFlightsDepartureDate(QString&);
						void setFlightsArrivalDate(QString&);

						void setTicketsBaggageAvailable(bool&);
						void setTicketsIsDeleted(bool&);

						void setTicketsId(unsigned int);
						void setTicketsPrice(unsigned int);
						void setClientPassportNumber(unsigned int);
						void setAirplaneMaxSizeCargo(unsigned int);
						void setAirplaneMaxWeightCargo(unsigned int);
						void setAirplaneMaxSeatPlaces(unsigned int);
						void setFlightsLadder(unsigned int);
						void setBaggageWeight(unsigned int);
						void setBaggageSize(unsigned int);
						void setServicesPrice(unsigned int);
						void setTicketsSeatNumber(unsigned int);

						void setClientPassportSeries(unsigned short);

						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setDeparturePoint(QString);
						void setArrivalPoint(QString);
						void setAirplaneName(QString);
						void setAirplaneDescription(QString);
						void setBaggageName(QString);
						void setBaggageDescription(QString);
						void setServicesName(QString);
						void setServicesDescription(QString);

						void setFlightsDepartureDate(QDateTime);
						void setFlightsArrivalDate(QDateTime);
						void setFlightsDepartureDate(QString);
						void setFlightsArrivalDate(QString);

						void setTicketsBaggageAvailable(bool);
						void setTicketsIsDeleted(bool);
		private:
						unsigned int TicketsId;
						unsigned int TicketsPrice;
						unsigned int ClientPassportNumber;
						unsigned int AirplaneMaxSizeCargo;
						unsigned int AirplaneMaxWeightCargo;
						unsigned int AirplaneMaxSeatPlaces;
						unsigned int FlightsLadder;
						unsigned int BaggageWeight;
						unsigned int BaggageSize;
						unsigned int ServicesPrice;
						unsigned int TicketsSeatNumber;

						unsigned short ClientPassportSeries;

						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;
						QString DeparturePoint;
						QString ArrivalPoint;
						QString AirplaneName;
						QString AirplaneDescription;
						QString BaggageName;
						QString BaggageDescription;
						QString ServicesName;
						QString ServicesDescription;

						QDateTime FlightsDepartureDate;
						QDateTime FlightsArrivalDate;

						bool TicketsBaggageAvailable;
						bool TicketsIsDeleted;
	};

#endif
