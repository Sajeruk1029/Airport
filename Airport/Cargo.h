#ifndef CARGO_H
#define CARGO_H

	#include <QString>

	class Cargo
	{
		public:
                        explicit Cargo(unsigned int&, unsigned int&, unsigned int&, QString&, unsigned int&, unsigned int&, bool&);
                        explicit Cargo(unsigned int, unsigned int, unsigned int, QString, unsigned int, unsigned int, bool);
						Cargo(void);

						unsigned int getId(void) const;
						unsigned int getIdCategory(void) const;
						unsigned int getWeight(void) const;
						unsigned int getIdTicket(void) const;
						unsigned int getSize(void) const;

						QString getDescription(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setIdCategory(unsigned int&);
						void setWeight(unsigned int&);
						void setIdTicket(unsigned int&);
						void setSize(unsigned int&);
						void setDescription(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setIdCategory(unsigned int);
						void setWeight(unsigned int);
						void setIdTicket(unsigned int);
						void setSize(unsigned int);
						void setDescription(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int IdCategory;
						unsigned int Weight;
						unsigned int IdTicket;
						unsigned int Size;

						QString Description;

						bool IsDeleted;
	};

#endif
