#ifndef AIRCOMPANYANDSERVICES_H
#define AIRCOMPANYANDSERVICES_H

	#include <QString>

	class AirCompanyAndServices
	{
		public:
                        explicit AirCompanyAndServices(unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit AirCompanyAndServices(unsigned int, unsigned int, unsigned int, bool);
						AirCompanyAndServices(void);

						unsigned int getId(void) const;
						unsigned int getIdAirCompany(void) const;
						unsigned int getIdService(void) const;
						
						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setIdAirCompany(unsigned int&);
						void setIdService(unsigned int&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setIdAirCompany(unsigned int);
						void setIdService(unsigned int);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int IdAirCompany;
						unsigned int IdService;

						bool IsDeleted;
	};

#endif
