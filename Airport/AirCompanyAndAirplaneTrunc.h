#ifndef AIRCOMPANYANDAIRPLANETRUNC
#define AIRCOMPANYANDAIRPLANETRUNC

	#include <QString>

	class AirCompanyAndAirplaneTrunc
	{
		public:
                        explicit AirCompanyAndAirplaneTrunc(unsigned int&, QString&, QString&, bool&);
                        explicit AirCompanyAndAirplaneTrunc(unsigned int, QString, QString, bool);
						AirCompanyAndAirplaneTrunc(void);

						unsigned int getAirplaneId(void) const;

						QString getAirplaneName(void) const;
						QString getAirCompanyName(void) const;

						bool getAirplaneIsDeleted(void) const;

						void setAirplaneId(unsigned int&);
						void setAirplaneName(QString&);
						void setAirCompanyName(QString&);
						void setAirplaneIsDeleted(bool&);

						void setAirplaneId(unsigned int);
						void setAirplaneName(QString);
						void setAirCompanyName(QString);
						void setAirplaneIsDeleted(bool);
		private:
						unsigned int AirplaneId;

						QString AirplaneName;
						QString AirCompanyName;

						bool AirplaneIsDeleted;
	};

#endif
