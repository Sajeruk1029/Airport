#ifndef CLIENTFULL_H
#define CLIENTFULL_H


#include <QString>

class ClientFull
{
    public:
                    explicit ClientFull(unsigned int&, QString&, QString&, QString&, unsigned short&, unsigned int&, QString&, QString&, unsigned int&, bool&);
                    explicit ClientFull(unsigned int, QString, QString, QString, unsigned short, unsigned int, QString, QString, unsigned int, bool);
                    ClientFull(void);

                    unsigned int getClientId(void) const;
                    unsigned int getClientPassportNumber(void) const;
                    unsigned int getClientMoney(void) const;

                    unsigned short getClientPassportSeries(void) const;

                    QString getClientFirstName(void) const;
                    QString getClientLastName(void) const;
                    QString getClientPatronymic(void) const;
                    QString getAccountLogin(void) const;
                    QString getAccountPassword(void) const;

                    bool getClientIsDeleted(void) const;

                    void setClientId(unsigned int&);
                    void setClientPassportNumber(unsigned int&);
                    void setClientMoney(unsigned int&);

                    void setClientPassportSeries(unsigned short&);

                    void setClientFirstName(QString&);
                    void setClientLastName(QString&);
                    void setClientPatronymic(QString&);
                    void setAccountLogin(QString&);
                    void setAccountPassword(QString&);
                    void setClientIsDeleted(bool&);

                    void setClientId(unsigned int);
                    void setClientPassportNumber(unsigned int);
                    void setClientMoney(unsigned int);

                    void setClientPassportSeries(unsigned short);

                    void setClientFirstName(QString);
                    void setClientLastName(QString);
                    void setClientPatronymic(QString);
                    void setAccountLogin(QString);
                    void setAccountPassword(QString);
                    void setClientIsDeleted(bool);
    private:
                    unsigned int ClientId;
                    unsigned int ClientPassportNumber;
                    unsigned int ClientMoney;

                    unsigned short ClientPassportSeries;

                    QString ClientFirstName;
                    QString ClientLastName;
                    QString ClientPatronymic;
                    QString AccountLogin;
                    QString AccountPassword;

                    bool ClientIsDeleted;
};

#endif // CLIENTFULL_H
