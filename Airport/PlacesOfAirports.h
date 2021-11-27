#ifndef PLACESOFAIRPORTS_H
#define PLACESOFAIRPORTS_H

	#include <QString>

	class PlacesOfAirports
	{
		public:
                        explicit PlacesOfAirports(unsigned int&, QString&, QString&, QString&, unsigned int&, bool&);
                        explicit PlacesOfAirports(unsigned int, QString, QString, QString, unsigned int, bool);
						PlacesOfAirports(void);

						unsigned int getId(void) const;
						unsigned int getHouseNumber(void) const;

						QString getCountry(void) const;
						QString getCity(void) const;
						QString getStreet(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setHouseNumber(unsigned int&);
						void setCountry(QString&);
						void setCity(QString&);
						void setStreet(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setHouseNumber(unsigned int);
						void setCountry(QString);
						void setCity(QString);
						void setStreet(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int HouseNumber;

						QString Country;
						QString City;
						QString Street;

						bool IsDeleted;
	};

#endif
