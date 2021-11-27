#ifndef AIRCOMPANYANDAIRPLANEFULL
#define AIRCOMPANYANDAIRPLANEFULL

	#include <QString>

	class AirCompanyAndAirplaneFull
	{
		public:
                        explicit AirCompanyAndAirplaneFull(unsigned int&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, QString&, bool&);
                        explicit AirCompanyAndAirplaneFull(unsigned int, QString, QString, unsigned int, unsigned int, unsigned int, QString, bool);
						AirCompanyAndAirplaneFull(void);

						unsigned int getAirplaneId(void) const;
						unsigned int getAirplaneMaxSizeCargo(void) const;
						unsigned int getAirplaneMaxWeightCargo(void) const;
						unsigned int getAirplaneMaxSeatPlaces(void) const;

						QString getAirplaneName(void) const;
						QString getAirplaneDescription(void) const;
						QString getAirCompanyName(void) const;

						bool getAirplaneIsDeleted(void) const;

						void setAirplaneId(unsigned int&);
						void setAirplaneMaxSizeCargo(unsigned int&);
						void setAirplaneMaxWeightCargo(unsigned int&);
						void setAirplaneMaxSeatPlaces(unsigned int&);
						void setAirplaneName(QString&);
						void setAirplaneDescription(QString&);
						void setAirCompanyName(QString&);
						void setAirplaneIsDeleted(bool&);

						void setAirplaneId(unsigned int);
						void setAirplaneMaxSizeCargo(unsigned int);
						void setAirplaneMaxWeightCargo(unsigned int);
						void setAirplaneMaxSeatPlaces(unsigned int);
						void setAirplaneName(QString);
						void setAirplaneDescription(QString);
						void setAirCompanyName(QString);
						void setAirplaneIsDeleted(bool);
		private:
						unsigned int AirplaneId;
						unsigned int AirplaneMaxSizeCargo;
						unsigned int AirplaneMaxWeightCargo;
						unsigned int AirplaneMaxSeatPlaces;

						QString AirplaneName;
						QString AirplaneDescription;
						QString AirCompanyName;

						bool AirplaneIsDeleted;
	};

#endif
