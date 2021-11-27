#ifndef TICKETSTRUNC_H
#define TICKETSTRUNC_H

	#include <QString>
	#include <QDateTime>

	class TicketsTrunc
	{
		public:
                        explicit TicketsTrunc(unsigned int&, unsigned int&, QString&, QString&, QString&, QString&, QString&, unsigned int&, bool&, QString&, unsigned int&, bool&);
                        explicit TicketsTrunc(unsigned int, unsigned int, QString, QString, QString, QString, QString, unsigned int, bool, QString, unsigned int, bool);
                        explicit TicketsTrunc(unsigned int&, unsigned int&, QString&, QString&, QString&, QDateTime&, QString&, unsigned int&, bool&, QString&, unsigned int&, bool&);
                        explicit TicketsTrunc(unsigned int, unsigned int, QString, QString, QString, QDateTime, QString, unsigned int, bool, QString, unsigned int, bool);
						TicketsTrunc(void);

						unsigned int getTicketsId(void) const;
						unsigned int getTicketsPrice(void) const;
						unsigned int getFlightsLadder(void) const;
						unsigned int getTicketsSeatNumber(void) const;

						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;
						QString getArrivalPoint(void) const;
						QString getBaggageName(void) const;

						QDateTime getFlightsDepartureDate(void) const;

						bool getTicketsBaggageAvailable(void) const;
						bool getTicketsIsDeleted(void) const;

						void setTicketsId(unsigned int&);
						void setTicketsPrice(unsigned int&);
						void setFlightsLadder(unsigned int&);
						void setTicketsSeatNumber(unsigned int&);

						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setArrivalPoint(QString&);
						void setBaggageName(QString&);

						void setFlightsDepartureDate(QDateTime&);
						void setFlightsDepartureDate(QString&);

						void setTicketsBaggageAvailable(bool&);
						void setTicketsIsDeleted(bool&);

						void setTicketsId(unsigned int);
						void setTicketsPrice(unsigned int);
						void setFlightsLadder(unsigned int);
						void setTicketsSeatNumber(unsigned int);

						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setArrivalPoint(QString);
						void setBaggageName(QString);

						void setFlightsDepartureDate(QDateTime);
						void setFlightsDepartureDate(QString);

						void setTicketsBaggageAvailable(bool);
						void setTicketsIsDeleted(bool);
		private:
						unsigned int TicketsId;
						unsigned int TicketsPrice;
						unsigned int FlightsLadder;
						unsigned int TicketsSeatNumber;

						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;
						QString ArrivalPoint;
						QString BaggageName;

						QDateTime FlightsDepartureDate;

						bool TicketsBaggageAvailable;
						bool TicketsIsDeleted;
	};

#endif
