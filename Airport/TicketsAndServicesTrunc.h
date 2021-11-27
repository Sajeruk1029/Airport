#ifndef TICKETSANDSERVICESTRUNC_H
#define TICKETSANDSERVICESTRUNC_H

	#include <QString>
	#include <QDateTime>

	class TicketsAndServicesTrunc
	{
		public:
                        explicit TicketsAndServicesTrunc(unsigned int&, unsigned int&, QString&, QString&, QString&, QString&, unsigned int&, unsigned int&, bool&);
                        explicit TicketsAndServicesTrunc(unsigned int, unsigned int, QString, QString, QString, QString, unsigned int, unsigned int, bool);
						TicketsAndServicesTrunc(void);

						unsigned int getTicketsId(void) const;
						unsigned int getTicketsPrice(void) const;
						unsigned int getServicesPrice(void) const;
						unsigned int getTicketsSeatNumber(void) const;

						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;
						QString getServicesName(void) const;

						bool getTicketsIsDeleted(void) const;

						void setTicketsId(unsigned int&);
						void setTicketsPrice(unsigned int&);
						void setServicesPrice(unsigned int&);
						void setTicketsSeatNumber(unsigned int&);

						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setServicesName(QString&);

						void setTicketsIsDeleted(bool&);

						void setTicketsId(unsigned int);
						void setTicketsPrice(unsigned int);
						void setServicesPrice(unsigned int);
						void setTicketsSeatNumber(unsigned int);

						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setServicesName(QString);

						void setTicketsIsDeleted(bool);
		private:
						unsigned int TicketsId;
						unsigned int TicketsPrice;
						unsigned int ServicesPrice;
						unsigned int TicketsSeatNumber;

						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;
						QString ServicesName;

						bool TicketsIsDeleted;
	};

#endif
