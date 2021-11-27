#ifndef NETWORKAPIREQUESTER_H
#define NETWORKAPIREQUESTER_H

	#include <QObject>

	#include <QNetworkRequest>
	#include <QNetworkAccessManager>
	#include <QNetworkReply>

	#include <QJsonObject>
	#include <QJsonArray>
	#include <QJsonValue>
	#include <QJsonDocument>

	#include <QString>
	#include <QByteArray>

	#include <QList>

	#include <QVariant>
	#include <QUrl>
	#include <QUrlQuery>

	#include <QEventLoop>

    #include <QTimer>
    #include <QTime>

    #include <functional>

	#include "Accounts.h"
    #include "AirCompany.h"
    #include "AirCompanyAndAirplane.h"
    #include "AirCompanyAndServices.h"
    #include "Airplane.h"
    #include "Baggage.h"
    #include "Cargo.h"
    #include "CategoriesCargo.h"
    #include "Client.h"
    #include "ClientAndBaggage.h"
    #include "Flights.h"
    #include "PlacesOfAirports.h"
    #include "Post.h"
    #include "Services.h"
    #include "Staff.h"
    #include "Tickets.h"
    #include "TicketsAndServices.h"

    #include "AirCompanyAndAirplaneFull.h"
    #include "AirCompanyAndAirplaneTrunc.h"
    #include "AirCompanyAndServicesFull.h"
    #include "AirCompanyAndServicesTrunc.h"
    #include "CargoFull.h"
    #include "CargoTrunc.h"
    #include "ClientAndBaggageFull.h"
    #include "ClientAndBaggageTrunc.h"
    #include "FlightsFull.h"
    #include "FlightsTrunc.h"
    #include "StaffFull.h"
    #include "StaffTrunc.h"
    #include "TicketsAndServicesFull.h"
    #include "TicketsAndServicesTrunc.h"
    #include "TicketsFull.h"
    #include "TicketsTrunc.h"
    #include "ClientFull.h"

	class NetworkAPIRequester : public QObject
	{
		Q_OBJECT

			public:
                            explicit NetworkAPIRequester(QString);
                            ~NetworkAPIRequester(void);

                            void getAllAccounts(const std::function<void(QList<Accounts>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAccounts(const std::function<void(QList<Accounts>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAccounts(const std::function<void(QList<Accounts>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAccounts(const std::function<void(Accounts)>, const std::function<void(unsigned int, QString, QString)>, Accounts);
                            void setAccounts(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Accounts, Accounts);
                            void deleteAccounts(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Accounts);
                            void logicalRecoverAccounts(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Accounts);
                            void logicalDeleterAccounts(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Accounts);
                            void addAccounts(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Accounts);

                            //---Accounts

                            void getAllAirCompany(const std::function<void(QList<AirCompany>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompany(const std::function<void(QList<AirCompany>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompany(const std::function<void(QList<AirCompany>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirCompany(const std::function<void(AirCompany)>, const std::function<void(unsigned int, QString, QString)>, AirCompany);
                            void setAirCompany(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompany, AirCompany);
                            void deleteAirCompany(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompany);
                            void logicalRecoverAirCompany(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompany);
                            void logicalDeleterAirCompany(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompany);
                            void addAirCompany(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, AirCompany);

                            //---AirCompany

                            void getAllAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndAirplane(const std::function<void(QList<AirCompanyAndAirplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            //void searchAirCompanyAndAirplane(const std::function<void(AirCompanyAndAirplane)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane);
                            void setAirCompanyAndAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane, AirCompanyAndAirplane);
                            void deleteAirCompanyAndAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane);
                            void logicalRecoverAirCompanyAndAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane);
                            void logicalDeleterAirCompanyAndAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane);
                            void addAirCompanyAndAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplane);

                            //---AirCompanyAndAirplane

                            void getAllAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndServices(const std::function<void(QList<AirCompanyAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            //void searchAirCompanyAndServices(const std::function<void(AirCompanyAndServices)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices);
                            void setAirCompanyAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices, AirCompanyAndServices);
                            void deleteAirCompanyAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices);
                            void logicalRecoverAirCompanyAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices);
                            void logicalDeleterAirCompanyAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices);
                            void addAirCompanyAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServices);

                            //---AirCompanyAndServices

                            void getAllAirplane(const std::function<void(QList<Airplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirplane(const std::function<void(QList<Airplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirplane(const std::function<void(QList<Airplane>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirplane(const std::function<void(Airplane)>, const std::function<void(unsigned int, QString, QString)>, Airplane);
                            void setAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Airplane, Airplane);
                            void deleteAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Airplane);
                            void logicalRecoverAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Airplane);
                            void logicalDeleterAirplane(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Airplane);
                            void addAirplane(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Airplane);

                            //---Airplane

                            void getAllBaggage(const std::function<void(QList<Baggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteBaggage(const std::function<void(QList<Baggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveBaggage(const std::function<void(QList<Baggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchBaggage(const std::function<void(Baggage)>, const std::function<void(unsigned int, QString, QString)>, Baggage);
                            void setBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Baggage, Baggage);
                            void deleteBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Baggage);
                            void logicalRecoverBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Baggage);
                            void logicalDeleterBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Baggage);
                            void addBaggage(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Baggage);

                            //---Baggage

                            void getAllCargo(const std::function<void(QList<Cargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteCargo(const std::function<void(QList<Cargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveCargo(const std::function<void(QList<Cargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchCargo(const std::function<void(Cargo)>, const std::function<void(unsigned int, QString, QString)>, Cargo);
                            void setCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Cargo, Cargo);
                            void deleteCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Cargo);
                            void logicalRecoverCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Cargo);
                            void logicalDeleterCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Cargo);
                            void addCargo(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Cargo);

                            //---Cargo

                            void getAllCategoriesCargo(const std::function<void(QList<CategoriesCargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteCategoriesCargo(const std::function<void(QList<CategoriesCargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveCategoriesCargo(const std::function<void(QList<CategoriesCargo>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchCategoriesCargo(const std::function<void(CategoriesCargo)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo);
                            void setCategoriesCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo, CategoriesCargo);
                            void deleteCategoriesCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo);
                            void logicalRecoverCategoriesCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo);
                            void logicalDeleterCategoriesCargo(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo);
                            void addCategoriesCargo(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, CategoriesCargo);

                            //---CategoriesCargo

                            void getAllClient(const std::function<void(QList<Client>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteClient(const std::function<void(QList<Client>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveClient(const std::function<void(QList<Client>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchClient(const std::function<void(Client)>, const std::function<void(unsigned int, QString, QString)>, Client);
                            void setClient(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Client, Client);
                            void deleteClient(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Client);
                            void logicalRecoverClient(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Client);
                            void logicalDeleterClient(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Client);
                            void addClient(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Client);

                            //---Client

                            void getAllClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveClientAndBaggage(const std::function<void(QList<ClientAndBaggage>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchClientAndBaggage(const std::function<void(ClientAndBaggage)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage);
                            void setClientAndBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage, ClientAndBaggage);
                            void deleteClientAndBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage);
                            void logicalRecoverClientAndBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage);
                            void logicalDeleterClientAndBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage);
                            void addClientAndBaggage(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggage);

                            //---ClientAndBaggage

                            void getAllFlights(const std::function<void(QList<Flights>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteFlights(const std::function<void(QList<Flights>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveFlights(const std::function<void(QList<Flights>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchFlights(const std::function<void(Flights)>, const std::function<void(unsigned int, QString, QString)>, Flights);
                            void setFlights(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Flights, Flights);
                            void deleteFlights(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Flights);
                            void logicalRecoverFlights(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Flights);
                            void logicalDeleterFlights(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Flights);
                            void addFlights(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Flights);

                            //---Flights

                            void getAllPlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeletePlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActivePlacesOfAirports(const std::function<void(QList<PlacesOfAirports>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchPlacesOfAirports(const std::function<void(PlacesOfAirports)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports);
                            void setPlacesOfAirports(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports, PlacesOfAirports);
                            void deletePlacesOfAirports(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports);
                            void logicalRecoverPlacesOfAirports(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports);
                            void logicalDeleterPlacesOfAirports(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports);
                            void addPlacesOfAirports(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, PlacesOfAirports);

                            //---PlacesOfAirports

                            void getAllPost(const std::function<void(QList<Post>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeletePost(const std::function<void(QList<Post>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActivePost(const std::function<void(QList<Post>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchPost(const std::function<void(Post)>, const std::function<void(unsigned int, QString, QString)>, Post);
                            void setPost(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Post, Post);
                            void deletePost(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Post);
                            void logicalRecoverPost(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Post);
                            void logicalDeleterPost(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Post);
                            void addPost(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Post);

                            //---Post

                            void getAllServices(const std::function<void(QList<Services>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteServices(const std::function<void(QList<Services>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveServices(const std::function<void(QList<Services>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchServices(const std::function<void(Services)>, const std::function<void(unsigned int, QString, QString)>, Services);
                            void setServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Services, Services);
                            void deleteServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Services);
                            void logicalRecoverServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Services);
                            void logicalDeleterServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Services);
                            void addServices(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Services);

                            //---Services

                            void getAllStaff(const std::function<void(QList<Staff>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteStaff(const std::function<void(QList<Staff>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveStaff(const std::function<void(QList<Staff>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchStaff(const std::function<void(Staff)>, const std::function<void(unsigned int, QString, QString)>, Staff);
                            void setStaff(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Staff, Staff);
                            void deleteStaff(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Staff);
                            void logicalRecoverStaff(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Staff);
                            void logicalDeleterStaff(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Staff);
                            void addStaff(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Staff);

                            //---Staff

                            void getAllTickets(const std::function<void(QList<Tickets>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTickets(const std::function<void(QList<Tickets>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTickets(const std::function<void(QList<Tickets>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchTickets(const std::function<void(Tickets)>, const std::function<void(unsigned int, QString, QString)>, Tickets);
                            void setTickets(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Tickets, Tickets);
                            void deleteTickets(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Tickets);
                            void logicalRecoverTickets(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Tickets);
                            void logicalDeleterTickets(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, Tickets);
                            void addTickets(const std::function<void(unsigned int)>, const std::function<void(unsigned int, QString, QString)>, Tickets);

                            //---Tickets

                            void getAllTicketsAndServices(const std::function<void(QList<TicketsAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTicketsAndServices(const std::function<void(QList<TicketsAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTicketsAndServices(const std::function<void(QList<TicketsAndServices>)>, const std::function<void(unsigned int, QString, QString)>);
                            //void searchTicketsAndServices(const std::function<void(TicketsAndServices)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices);
                            void setTicketsAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices, TicketsAndServices);
                            void deleteTicketsAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices);
                            void logicalRecoverTicketsAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices);
                            void logicalDeleterTicketsAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices);
                            void addTicketsAndServices(const std::function<void(bool)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServices);

                            //---TicketsAndServices

                            void getAllAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndAirplaneFull(const std::function<void(QList<AirCompanyAndAirplaneFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirCompanyAndAirplaneFull(const std::function<void(AirCompanyAndAirplaneFull)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplaneFull);

                            //---AirCompanyAndAirplaneFull

                            void getAllAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndAirplaneTrunc(const std::function<void(QList<AirCompanyAndAirplaneTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirCompanyAndAirplaneTrunc(const std::function<void(AirCompanyAndAirplaneTrunc)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndAirplaneTrunc);

                            //---AirCompanyAndAirplaneTrunc

                            void getAllAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndServicesFull(const std::function<void(QList<AirCompanyAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirCompanyAndServicesFull(const std::function<void(AirCompanyAndServicesFull)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServicesFull);

                            //---AirCompanyAndServicesFull

                            void getAllAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveAirCompanyAndServicesTrunc(const std::function<void(QList<AirCompanyAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchAirCompanyAndServicesTrunc(const std::function<void(AirCompanyAndServicesTrunc)>, const std::function<void(unsigned int, QString, QString)>, AirCompanyAndServicesTrunc);

                            //---AirCompanyAndServicesTrunc

                            void getAllCargoFull(const std::function<void(QList<CargoFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteCargoFull(const std::function<void(QList<CargoFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveCargoFull(const std::function<void(QList<CargoFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchCargoFull(const std::function<void(CargoFull)>, const std::function<void(unsigned int, QString, QString)>, CargoFull);

                            //---CargoFull

                            void getAllCargoTrunc(const std::function<void(QList<CargoTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteCargoTrunc(const std::function<void(QList<CargoTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveCargoTrunc(const std::function<void(QList<CargoTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchCargoTrunc(const std::function<void(CargoTrunc)>, const std::function<void(unsigned int, QString, QString)>, CargoTrunc);

                            //---CargoTrunc

                            void getAllClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveClientAndBaggageFull(const std::function<void(QList<ClientAndBaggageFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchClientAndBaggageFull(const std::function<void(ClientAndBaggageFull)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggageFull);

                            //---ClientAndBaggageFull

                            void getAllClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveClientAndBaggageTrunc(const std::function<void(QList<ClientAndBaggageTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchClientAndBaggageTrunc(const std::function<void(ClientAndBaggageTrunc)>, const std::function<void(unsigned int, QString, QString)>, ClientAndBaggageTrunc);

                            //---ClientAndBaggageTrunc

                            void getAllFlightsFull(const std::function<void(QList<FlightsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteFlightsFull(const std::function<void(QList<FlightsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveFlightsFull(const std::function<void(QList<FlightsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchFlightsFull(const std::function<void(FlightsFull)>, const std::function<void(unsigned int, QString, QString)>, FlightsFull);

                            //---FlightsFull

                            void getAllFlightsTrunc(const std::function<void(QList<FlightsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteFlightsTrunc(const std::function<void(QList<FlightsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveFlightsTrunc(const std::function<void(QList<FlightsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchFlightsTrunc(const std::function<void(FlightsTrunc)>, const std::function<void(unsigned int, QString, QString)>, FlightsTrunc);

                            //---FlightsTrunc

                            void getAllStaffFull(const std::function<void(QList<StaffFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteStaffFull(const std::function<void(QList<StaffFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveStaffFull(const std::function<void(QList<StaffFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchStaffFull(const std::function<void(StaffFull)>, const std::function<void(unsigned int, QString, QString)>, StaffFull);
                            void searchByLoginStaffFull(const std::function<void(StaffFull)>, const std::function<void(unsigned int, QString, QString)>, StaffFull);

                            //---StaffFull

                            void getAllStaffTrunc(const std::function<void(QList<StaffTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteStaffTrunc(const std::function<void(QList<StaffTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveStaffTrunc(const std::function<void(QList<StaffTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchStaffTrunc(const std::function<void(StaffTrunc)>, const std::function<void(unsigned int, QString, QString)>, StaffTrunc);

                            //---StaffTrunc

                            void getAllTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTicketsAndServicesFull(const std::function<void(QList<TicketsAndServicesFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchTicketsAndServicesFull(const std::function<void(TicketsAndServicesFull)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServicesFull);

                            //---TicketsAndServicesFull

                            void getAllTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTicketsAndServicesTrunc(const std::function<void(QList<TicketsAndServicesTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchTicketsAndServicesTrunc(const std::function<void(TicketsAndServicesTrunc)>, const std::function<void(unsigned int, QString, QString)>, TicketsAndServicesTrunc);

                            //---TicketsAndServicesTrunc

                            void getAllTicketsFull(const std::function<void(QList<TicketsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTicketsFull(const std::function<void(QList<TicketsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTicketsFull(const std::function<void(QList<TicketsFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchTicketsFull(const std::function<void(TicketsFull)>, const std::function<void(unsigned int, QString, QString)>, TicketsFull);

                            //---TicketsFull

                            void getAllTicketsTrunc(const std::function<void(QList<TicketsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteTicketsTrunc(const std::function<void(QList<TicketsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveTicketsTrunc(const std::function<void(QList<TicketsTrunc>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchTicketsTrunc(const std::function<void(TicketsTrunc)>, const std::function<void(unsigned int, QString, QString)>, TicketsTrunc);

                            //---TicketsTrunc

                            void getAllClientFull(const std::function<void(QList<ClientFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getDeleteClientFull(const std::function<void(QList<ClientFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void getActiveClientFull(const std::function<void(QList<ClientFull>)>, const std::function<void(unsigned int, QString, QString)>);
                            void searchClientFull(const std::function<void(ClientFull)>, const std::function<void(unsigned int, QString, QString)>, ClientFull);
                            void searchByLoginClientFull(const std::function<void(ClientFull)>, const std::function<void(unsigned int, QString, QString)>, ClientFull);

                            //---ClientFull

							unsigned char getErrno(void) const;

							QString getErrnoLine(void) const;

							void setErrno(unsigned char);
							void setErrorLine(QString);
							void setErrnoState(unsigned char, QString);
			private:
							QNetworkAccessManager *networkAccessManager;

                            QString url;
                            QString errorLine;

                            unsigned char error;
	};

#endif
