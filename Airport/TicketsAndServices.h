#ifndef TICKETSANDSERVICES_H
#define TICKETSANDSERVICES_H

  #include <QString>

	class TicketsAndServices
	{
		public:
                        explicit TicketsAndServices(unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit TicketsAndServices(unsigned int, unsigned int, unsigned int, bool);
						TicketsAndServices(void);

						unsigned int getId(void) const;
						unsigned int getIdService(void) const;
						unsigned int getIdTicket(void) const;
						
						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setIdService(unsigned int&);
						void setIdTicket(unsigned int&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setIdService(unsigned int);
						void setIdTicket(unsigned int);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int IdService;
						unsigned int IdTicket;

						bool IsDeleted;
	};

#endif
