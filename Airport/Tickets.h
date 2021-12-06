#ifndef TICKETS_H
#define TICKETS_H

        #include <QString>

	class Tickets
	{
		public:
                        explicit Tickets(unsigned int&, unsigned int&, unsigned int&, unsigned int&, unsigned int&, bool&, unsigned int&, bool&);
                        explicit Tickets(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, unsigned int, bool);
						Tickets(void);

						unsigned int getId(void) const;
						unsigned int getPrice(void) const;
						unsigned int getIdClient(void) const;
						unsigned int getSeatNumber(void) const;
						unsigned int getFlights(void) const;
						unsigned int getBaggage(void) const;

						bool getBaggageAvailable(void) const;
						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setPrice(unsigned int&);
						void setIdClient(unsigned int&);
						void setSeatNumber(unsigned int&);
						void setFlights(unsigned int&);
						void setBaggage(unsigned int&);
						void setBaggageAvailable(bool&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setPrice(unsigned int);
						void setIdClient(unsigned int);
						void setSeatNumber(unsigned int);
						void setFlights(unsigned int);
                        void setBaggage(unsigned int);
						void setBaggageAvailable(bool);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int Price;
						unsigned int IdClient;
						unsigned int SeatNumber;
						unsigned int Flights;
						unsigned int Baggage;

						bool BaggageAvailable;
						bool IsDeleted;
	};

#endif
