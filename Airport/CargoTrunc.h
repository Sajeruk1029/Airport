#ifndef CARGOTRUNC_H
#define CARGOTRUNC_H

	#include <QString>
	#include <QDateTime>

    class CargoTrunc
	{
		public:
                        explicit CargoTrunc(unsigned int&, QString&, unsigned int&, unsigned int&, QString&, QString&, QString&, QString&, bool&);
                        explicit CargoTrunc(unsigned int, QString, unsigned int, unsigned int, QString, QString, QString, QString, bool);
                        CargoTrunc(void);

						unsigned int getCargoId(void) const;
						unsigned int getCargoWeight(void) const;
						unsigned int getCargoSize(void) const;

						QString getCargoDescription(void) const;
						QString getCategoriesCargoName(void) const;
						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;

						bool getCargoIsDeleted(void) const;

						void setCargoId(unsigned int&);
						void setCargoWeight(unsigned int&);
						void setCargoSize(unsigned int&);
						void setCargoDescription(QString&);
						void setCategoriesCargoName(QString&);
						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setCargoIsDeleted(bool&);

						void setCargoId(unsigned int);
						void setCargoWeight(unsigned int);
						void setCargoSize(unsigned int);
						void setCargoDescription(QString);
						void setCategoriesCargoName(QString);
						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setCargoIsDeleted(bool);
		private:
						unsigned int CargoId;
						unsigned int CargoWeight;
						unsigned int CargoSize;

						QString CargoDescription;
						QString CategoriesCargoName;
						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;

						bool CargoIsDeleted;
	};

#endif
