#ifndef STAFFFULL_H
#define STAFFFULL_H

	#include <QString>

	class StaffFull
	{
		public:
                        explicit StaffFull(unsigned int&, QString&, QString&, QString&, QString&, unsigned int&, unsigned short&, unsigned int&, QString&, QString&, QString&, bool&);
                        explicit StaffFull(unsigned int, QString, QString, QString, QString, unsigned int, unsigned short, unsigned int, QString, QString, QString, bool);
						StaffFull(void);

						unsigned int getStaffId(void) const;
						unsigned int getPostSalary(void) const;
						unsigned int getStaffPassportNumber(void) const;

						unsigned short getStaffPassportSeries(void) const;

						QString getStaffFirstName(void) const;
						QString getStaffLastName(void) const;
						QString getStaffPatronymic(void) const;
						QString getPostName(void) const;
						QString getStaffEducation(void) const;
						QString getAccountLogin(void) const;
						QString getAccountPassword(void) const;

						bool getStaffIsDeleted(void) const;

						void setStaffId(unsigned int&);
						void setPostSalary(unsigned int&);
						void setStaffPassportNumber(unsigned int&);

						void setStaffPassportSeries(unsigned short&);

						void setStaffFirstName(QString&);
						void setStaffLastName(QString&);
						void setStaffPatronymic(QString&);
						void setPostName(QString&);
						void setStaffEducation(QString&);
						void setAccountLogin(QString&);
						void setAccountPassword(QString&);
						void setStaffIsDeleted(bool&);

						void setStaffId(unsigned int);
						void setPostSalary(unsigned int);
						void setStaffPassportNumber(unsigned int);

						void setStaffPassportSeries(unsigned short);

						void setStaffFirstName(QString);
						void setStaffLastName(QString);
						void setStaffPatronymic(QString);
						void setPostName(QString);
						void setStaffEducation(QString);
						void setAccountLogin(QString);
						void setAccountPassword(QString);
						void setStaffIsDeleted(bool);
		private:
						unsigned int StaffId;
						unsigned int PostSalary;
						unsigned int StaffPassportNumber;

						unsigned short StaffPassportSeries;

						QString StaffFirstName;
						QString StaffLastName;
						QString StaffPatronymic;
						QString PostName;
						QString StaffEducation;
						QString AccountLogin;
						QString AccountPassword;

						bool StaffIsDeleted;
	};

#endif
