#ifndef CLIENTANDBAGGAGEFULL_H
#define CLIENTANDBAGGAGEFULL_H

	#include <QString>

	class ClientAndBaggageFull
	{
		public:
                        explicit ClientAndBaggageFull(unsigned int&, QString&, QString&, unsigned int&, unsigned int&, QString&, QString&, QString&, unsigned short&, unsigned int&, bool&);
                        explicit ClientAndBaggageFull(unsigned int, QString, QString, unsigned int, unsigned int, QString, QString, QString, unsigned short, unsigned int, bool);
						ClientAndBaggageFull(void);

						unsigned int getBaggageId(void) const;
						unsigned int getBaggageWeight(void) const;
						unsigned int getBaggageSize(void) const;
						unsigned int getClientPassportNumber(void) const;

						unsigned short getClientPassportSeries(void) const;

						QString getBaggageName(void) const;
						QString getBaggageDescription(void) const;
						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;

						bool getBaggageIsDeleted(void) const;

						void setBaggageId(unsigned int&);
						void setBaggageWeight(unsigned int&);
						void setBaggageSize(unsigned int&);
						void setClientPassportNumber(unsigned int&);
						void setClientPassportSeries(unsigned short&);
						void setBaggageName(QString&);
						void setBaggageDescription(QString&);
						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setBaggageIsDeleted(bool&);

						void setBaggageId(unsigned int);
						void setBaggageWeight(unsigned int);
						void setBaggageSize(unsigned int);
						void setClientPassportNumber(unsigned int);
						void setClientPassportSeries(unsigned short);
						void setBaggageName(QString);
						void setBaggageDescription(QString);
						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setBaggageIsDeleted(bool);
		private:
						unsigned int BaggageId;
						unsigned int BaggageWeight;
						unsigned int BaggageSize;
						unsigned int ClientPassportNumber;

						unsigned short ClientPassportSeries;

						QString BaggageName;
						QString BaggageDescription;
						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;

						bool BaggageIsDeleted;
	};

#endif
