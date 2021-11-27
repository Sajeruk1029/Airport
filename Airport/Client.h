#ifndef CLIENT_H
#define CLIENT_H

	#include <QString>

	class Client
	{
		public:
                        explicit Client(unsigned int&, QString&, QString&, QString&, unsigned short&, unsigned int&, unsigned int&, unsigned int&, bool&);
                        explicit Client(unsigned int, QString, QString, QString, unsigned short, unsigned int, unsigned int, unsigned int, bool);
						Client(void);

						unsigned int getId(void) const;
						unsigned int getPassportNumber(void) const;
						unsigned int getAccount(void) const;
						unsigned int getMoney(void) const;

						unsigned short getPassportSeries(void) const;

						QString getFirstName(void) const;
						QString getLastName(void) const;
						QString getPatronymic(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setPassportNumber(unsigned int&);
						void setAccount(unsigned int&);
						void setMoney(unsigned int&);
						void setPassportSeries(unsigned short&);
						void setFirstName(QString&);
						void setLastName(QString&);
						void setPatronymic(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setPassportNumber(unsigned int);
						void setAccount(unsigned int);
						void setMoney(unsigned int);
						void setPassportSeries(unsigned short);
						void setFirstName(QString);
						void setLastName(QString);
						void setPatronymic(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int PassportNumber;
						unsigned int Account;
						unsigned int Money;

						unsigned short PassportSeries;

						QString FirstName;
						QString LastName;
						QString Patronymic;

						bool IsDeleted;
	};

#endif
