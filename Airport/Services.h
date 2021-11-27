#ifndef SERVICES_H
#define SERVICES_H

	#include <QString>

	class Services
	{
		public:
                        explicit Services(unsigned int&, QString&, QString&, unsigned int&, bool&);
                        explicit Services(unsigned int, QString, QString, unsigned int, bool);
						Services(void);

						unsigned int getId(void) const;
						unsigned int getPrice(void) const;

						QString getName(void) const;
						QString getDescription(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setPrice(unsigned int&);
						void setName(QString&);
						void setDescription(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setPrice(unsigned int);
						void setName(QString);
						void setDescription(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int Price;

						QString Name;
						QString Description;

						bool IsDeleted;
	};

#endif
