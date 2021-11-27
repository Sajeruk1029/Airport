#ifndef POST_H
#define POST_H

	#include <QString>

	class Post
	{
		public:
                        explicit Post(unsigned int&, QString&, unsigned int&, bool&);
                        explicit Post(unsigned int, QString, unsigned int, bool);
						Post();

						unsigned getId(void) const;
						unsigned getSalary(void) const;

						QString getName(void) const;

						bool getIsDeleted(void) const;

						void setId(unsigned int&);
						void setSalary(unsigned int&);
						void setName(QString&);
						void setIsDeleted(bool&);

						void setId(unsigned int);
						void setSalary(unsigned int);
						void setName(QString);
						void setIsDeleted(bool);
		private:
						unsigned int Id;
						unsigned int Salary;

						QString Name;

						bool IsDeleted;
	};

#endif
