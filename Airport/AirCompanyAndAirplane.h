#ifndef AIRCOMPANYANDAIRPLANE_H
#define AIRCOMPANYANDAIRPLANE_H

	#include <QString>

	class AirCompanyAndAirplane
	{
		public:
                        explicit AirCompanyAndAirplane(unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit AirCompanyAndAirplane(unsigned int, unsigned int, unsigned int, bool);
						AirCompanyAndAirplane(void);

						unsigned int getId(void) const;
						unsigned int getIdAirplane(void) const;
						unsigned int getIdAirCompany(void) const;
						
						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setIdAirplane(unsigned int&);
						void setIdAirCompany(unsigned int&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setIdAirplane(unsigned int);
						void setIdAirCompany(unsigned int);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int IdAirplane;
						unsigned int IdAirCompany;

						bool IsDeleted;
	};

#endif
