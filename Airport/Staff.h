#ifndef STAFF_H
#define STAFF_H

	#include <QString>

	class Staff
	{
		public:
                        explicit Staff(unsigned int&, QString&, QString&, QString&, unsigned int&, unsigned short&, unsigned int&, unsigned int&, QString&, bool&);
                        explicit Staff(unsigned int, QString, QString, QString, unsigned int, unsigned short, unsigned int, unsigned int, QString, bool);
						Staff(void);

						unsigned int getId(void) const;
						unsigned int getPassportNumber(void) const;
						unsigned int getAccount(void) const;
						unsigned int getPost(void) const;

						unsigned short getPassportSeries(void) const;

						QString getFirstName(void) const;
						QString getLastName(void) const;
						QString getPatronymic(void) const;
						QString getEducation(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setPassportNumber(unsigned int&);
						void setAccount(unsigned int&);
						void setPost(unsigned int&);
						void setPassportSeries(unsigned short&);
						void setFirstName(QString&);
						void setLastName(QString&);
						void setPatronymic(QString&);
						void setEducation(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setPassportNumber(unsigned int);
						void setAccount(unsigned int);
						void setPost(unsigned int);
						void setPassportSeries(unsigned short);
						void setFirstName(QString);
						void setLastName(QString);
						void setPatronymic(QString);
						void setEducation(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int PassportNumber;
						unsigned int Account;
						unsigned int Post;

						unsigned short PassportSeries;

						QString FirstName;
						QString LastName;
						QString Patronymic;
						QString Education;

						bool IsDeleted;
	};

#endif
