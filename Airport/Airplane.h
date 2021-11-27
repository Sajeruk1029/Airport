#ifndef AIRPLANE_H
#define AIRPLANE_H

	#include <QString>

	class Airplane
	{
		public:
                        explicit Airplane(unsigned int&, QString&, QString&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit Airplane(unsigned int, QString, QString, unsigned int, unsigned int, unsigned int, bool);
						Airplane(void);

						unsigned int getId(void) const;
						unsigned int getMaxSizeCargo(void) const;
						unsigned int getMaxWeightCargo(void) const;
						unsigned int getMaxSeatPlaces(void) const;

						QString getName(void) const;
						QString getDescription(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setMaxSizeCargo(unsigned int&);
						void setMaxWeightCargo(unsigned int&);
						void setMaxSeatPlaces(unsigned int&);
						void setName(QString&);
						void setDescription(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setMaxSizeCargo(unsigned int);
						void setMaxWeightCargo(unsigned int);
						void setMaxSeatPlaces(unsigned int);
						void setName(QString);
						void setDescription(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int MaxSizeCargo;
						unsigned int MaxWeightCargo;
						unsigned int MaxSeatPlaces;

						QString Name;
						QString Description;

						bool IsDeleted;
	};

#endif
