#ifndef AIRCOMPANY_H
#define AIRCOMPANY_H

	#include <QString>

	class AirCompany
	{
		public:
                        explicit AirCompany(unsigned int&, QString&, bool&);
                        explicit AirCompany(unsigned int, QString, bool);
						AirCompany(void);

						unsigned int getId(void) const;

						QString getName(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setName(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setName(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;

						QString Name;

						bool IsDeleted;
	};

#endif
