#ifndef ACCOUNTS_H
#define ACCOUNTS_H

	#include <QString>

	class Accounts
	{
		public:
                        explicit Accounts(unsigned int&, QString&, QString&, bool&);
                        explicit Accounts(unsigned int, QString, QString, bool);
						Accounts(void);

						unsigned int getId(void) const;

						QString getLogin(void) const;
						QString getPassword(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setLogin(QString&);
						void setPassword(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setLogin(QString);
						void setPassword(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;

						QString Login;
						QString Password;

						bool IsDeleted;
	};
#endif
