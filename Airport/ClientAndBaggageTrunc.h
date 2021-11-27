#ifndef CLIENTANDBAGGAGETRUNC_H
#define CLIENTANDBAGGAGETRUNC_H

	#include <QString>

	class ClientAndBaggageTrunc
	{
		public:
                        explicit ClientAndBaggageTrunc(unsigned int&, QString&, QString&, QString&, QString&, bool&);
                        explicit ClientAndBaggageTrunc(unsigned int, QString, QString, QString, QString, bool);
						ClientAndBaggageTrunc(void);

						unsigned int getBaggageId(void) const;

						QString getBaggageName(void) const;
						QString getClientFirstName(void) const;
						QString getClientLastName(void) const;
						QString getClientPatronymic(void) const;

						bool getBaggageIsDeleted(void) const;

						void setBaggageId(unsigned int&);
						void setBaggageName(QString&);
						void setClientFirstName(QString&);
						void setClientLastName(QString&);
						void setClientPatronymic(QString&);
						void setBaggageIsDeleted(bool&);

						void setBaggageId(unsigned int);
						void setBaggageName(QString);
						void setClientFirstName(QString);
						void setClientLastName(QString);
						void setClientPatronymic(QString);
						void setBaggageIsDeleted(bool);
		private:
						unsigned int BaggageId;

						QString BaggageName;
						QString ClientFirstName;
						QString ClientLastName;
						QString ClientPatronymic;

						bool BaggageIsDeleted;
	};

#endif
