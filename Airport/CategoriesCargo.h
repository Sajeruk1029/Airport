#ifndef CATEGORIESCARGO_H
#define CATEGORIESCARGO_H

	#include <QString>

	class CategoriesCargo
	{
		public:
                        explicit CategoriesCargo(unsigned int&, QString&, QString&, bool&);
                        explicit CategoriesCargo(unsigned int, QString, QString, bool);
						CategoriesCargo(void);

						unsigned int getId(void) const;

						QString getName(void) const;
						QString getDescription(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setName(QString&);
						void setDescription(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setName(QString);
						void setDescription(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;

						QString Name;
						QString Description;

						bool IsDeleted;
	};

#endif
