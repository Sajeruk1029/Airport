#ifndef CLIENTANDBAGGAGE_H
#define CLIENTANDBAGGAGE_H

	#include <QString>

	class ClientAndBaggage
	{
		public:
                        explicit ClientAndBaggage(unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit ClientAndBaggage(unsigned int, unsigned int, unsigned int, bool);
						ClientAndBaggage(void);

						unsigned int getId(void) const;
						unsigned int getIdClient(void) const;
						unsigned int getIdBaggage(void) const;
						
						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setIdClient(unsigned int&);
						void setIdBaggage(unsigned int&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setIdClient(unsigned int);
						void setIdBaggage(unsigned int);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int IdClient;
						unsigned int IdBaggage;

						bool IsDeleted;
	};

#endif
