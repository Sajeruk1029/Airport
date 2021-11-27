#ifndef STAFFTRUNC_H
#define STAFFTRUNC_H

	#include <QString>

	class StaffTrunc
	{
		public:
                        explicit StaffTrunc(unsigned int&, QString&, QString&, QString&, QString&, unsigned int&, QString&, bool&);
                        explicit StaffTrunc(unsigned int, QString, QString, QString, QString, unsigned int, QString, bool);
						StaffTrunc(void);

						unsigned int getStaffId(void) const;
						unsigned int getPostSalary(void) const;

						QString getStaffFirstName(void) const;
						QString getStaffLastName(void) const;
						QString getStaffPatronymic(void) const;
						QString getPostName(void) const;
						QString getStaffEducation(void) const;

						bool getStaffIsDeleted(void) const;

						void setStaffId(unsigned int&);
						void setPostSalary(unsigned int&);

						void setStaffFirstName(QString&);
						void setStaffLastName(QString&);
						void setStaffPatronymic(QString&);
						void setPostName(QString&);
						void setStaffEducation(QString&);
						void setStaffIsDeleted(bool&);

						void setStaffId(unsigned int);
						void setPostSalary(unsigned int);

						void setStaffFirstName(QString);
						void setStaffLastName(QString);
						void setStaffPatronymic(QString);
						void setPostName(QString);
						void setStaffEducation(QString);
						void setStaffIsDeleted(bool);
		private:
						unsigned int StaffId;
						unsigned int PostSalary;

						QString StaffFirstName;
						QString StaffLastName;
						QString StaffPatronymic;
						QString PostName;
						QString StaffEducation;

						bool StaffIsDeleted;
	};

#endif
