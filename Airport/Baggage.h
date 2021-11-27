#ifndef BAGGAGE_H
#define BAGGAGE_H

	#include <QString>

	class Baggage
	{
		public:
                        explicit Baggage(unsigned int&, QString&, QString&, unsigned int&, unsigned int&, bool&);
                        explicit Baggage(unsigned int, QString, QString, unsigned int, unsigned int, bool);
						Baggage(void);

						unsigned int getId(void) const;
						unsigned int getWeight(void) const;
						unsigned int getSize(void) const;

						QString getName(void) const;
						QString getDescription(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setWeight(unsigned int&);
						void setSize(unsigned int&);

						void setName(QString&);
						void setDescription(QString&);

						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setWeight(unsigned int);
						void setSize(unsigned int);

						void setName(QString);
						void setDescription(QString);

						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int Weight;
						unsigned int Size;

						QString Name;
						QString Description;

						bool IsDeleted;
	};

#endif
