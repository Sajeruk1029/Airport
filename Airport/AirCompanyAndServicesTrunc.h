#ifndef AIRCOMPANYANDSERVICESTRUNC
#define AIRCOMPANYANDSERVICESTRUNC

	#include <QString>

	class AirCompanyAndServicesTrunc
	{
		public:
                        explicit AirCompanyAndServicesTrunc(unsigned int&, QString&, unsigned int&, QString&, bool&);
                        explicit AirCompanyAndServicesTrunc(unsigned int, QString, unsigned int, QString, bool);
						AirCompanyAndServicesTrunc(void);

						unsigned int getServicesId(void) const;
						unsigned int getServicePrice(void) const;

						QString getServiceName(void) const;
						QString getAirCompanyName(void) const;

						bool getServicesIsDeleted(void) const;

						void setServicesId(unsigned int&);
						void setServicePrice(unsigned int&);
						void setServiceName(QString&);
						void setAirCompanyName(QString&);
						void setServicesIsDeleted(bool&);

						void setServicesId(unsigned int);
						void setServicePrice(unsigned int);
						void setServiceName(QString);
						void setAirCompanyName(QString);
						void setServicesIsDeleted(bool);
		private:
						unsigned int ServicesId;
						unsigned int ServicePrice;

						QString ServiceName;
						QString AirCompanyName;

						bool ServicesIsDeleted;
	};

#endif
