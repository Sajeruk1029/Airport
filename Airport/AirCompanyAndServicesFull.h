#ifndef AIRCOMPANYANDSERVICESFULL
#define AIRCOMPANYANDSERVICESFULL

	#include <QString>

	class AirCompanyAndServicesFull
	{
		public:
                        explicit AirCompanyAndServicesFull(unsigned int&, QString&, QString&, unsigned int&, QString&, bool&);
                        explicit AirCompanyAndServicesFull(unsigned int, QString, QString, unsigned int, QString, bool);
						AirCompanyAndServicesFull(void);

						unsigned int getServicesId(void) const;
						unsigned int getServicePrice(void) const;

						QString getServiceName(void) const;
						QString getServiceDescription(void) const;
						QString getAirCompanyName(void) const;

						bool getServicesIsDeleted(void) const;

						void setServicesId(unsigned int&);
						void setServicePrice(unsigned int&);
						void setServiceName(QString&);
						void setServiceDescription(QString&);
						void setAirCompanyName(QString&);
						void setServicesIsDeleted(bool&);

						void setServicesId(unsigned int);
						void setServicePrice(unsigned int);
						void setServiceName(QString);
						void setServiceDescription(QString);
						void setAirCompanyName(QString);
						void setServicesIsDeleted(bool);
		private:
						unsigned int ServicesId;
						unsigned int ServicePrice;

						QString ServiceName;
						QString ServiceDescription;
						QString AirCompanyName;

						bool ServicesIsDeleted;
	};

#endif
