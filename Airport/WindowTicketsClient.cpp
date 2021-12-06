#include "WindowTicketsClient.h"

WindowTicketsClient::WindowTicketsClient(ClientFull clientFull, QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Купить билет пассажирский")), butAddCargo(new QPushButton("Купить билет на грузоперевозку")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QIntValidator(0, 9999999)), requester(new NetworkAPIRequester(host)), gen(nullptr), dataClientFull(clientFull), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butAdd);
    layoutContaner->addWidget(butAddCargo);
    layoutContaner->addWidget(butGenerateTable);

    search->setPlaceholderText("Id");
    search->setValidator(validator);

    table->setEditTriggers(QTableWidget::NoEditTriggers);

    layout->addWidget(container);
    layout->addWidget(table);

    refreshTable();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
    connect(butAddCargo, SIGNAL(clicked()), this, SLOT(onClickAddCargo()));
}

WindowTicketsClient::~WindowTicketsClient()
{
    if(validator){ delete validator; }

    if(table){ delete table; }

    if(butSearch){ delete butSearch; }
    if(butRefresh){ delete butRefresh; }
    if(butAdd){ delete butAdd; }
    if(butAddCargo){ delete butAddCargo; }
    if(butGenerateTable){ delete butGenerateTable; }
    if(search){ delete search; }

    if(layoutContaner){ delete layoutContaner; }

    if(container){ delete container; }

    if(layout){ delete layout; }

    if(gen){ delete gen; }
}

void WindowTicketsClient::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 11); }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", ""});

    requester->searchTicketsTrunc([this](TicketsTrunc ticketsTrunc)
    {
        table->setRowCount(1);
        table->setColumnCount(12);

        if(ticketsTrunc.getTicketsId() == 0){ return; }

        if((ticketsTrunc.getClientFirstName() != dataClientFull.getClientFirstName()) && (ticketsTrunc.getClientLastName() != dataClientFull.getClientLastName()) && (ticketsTrunc.getClientPatronymic() != dataClientFull.getClientPatronymic())){ return; }

        qDebug() << ticketsTrunc.getTicketsId();
        table->setItem(0, 0, new QTableWidgetItem(QString::number(ticketsTrunc.getTicketsId())));
        table->setItem(0, 1, new QTableWidgetItem(QString::number(ticketsTrunc.getTicketsPrice())));
        table->setItem(0, 2, new QTableWidgetItem(ticketsTrunc.getClientFirstName()));
        table->setItem(0, 3, new QTableWidgetItem(ticketsTrunc.getClientLastName()));
        table->setItem(0, 4, new QTableWidgetItem(ticketsTrunc.getClientPatronymic()));
        table->setItem(0, 5, new QTableWidgetItem(ticketsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
        table->setItem(0, 6, new QTableWidgetItem(ticketsTrunc.getArrivalPoint()));
        table->setItem(0, 7, new QTableWidgetItem(QString::number(ticketsTrunc.getFlightsLadder())));
        table->setItem(0, 8, new QTableWidgetItem((((ticketsTrunc.getTicketsBaggageAvailable() == 1)? "Да" : "Нет"))));
        table->setItem(0, 9, new QTableWidgetItem(ticketsTrunc.getBaggageName()));
        table->setItem(0, 10, new QTableWidgetItem(QString::number(ticketsTrunc.getTicketsSeatNumber())));

        table->setCellWidget(0, 11, new QPushButton("Детали"));

        table->cellWidget(0, 11)->setProperty("Id", ticketsTrunc.getTicketsId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 11)), &QPushButton::clicked, [this]()
        {
            requester->searchTicketsFull([this](TicketsFull ticketsFull)
            {
                for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 12); }

                table->clear();

                table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Серия паспорта", "Номер паспорта", "Дата отправления", "Дата прибытия", "Точка отбытия", "Точка прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза", "Максимальный вес груза", "Количество сидячих мест", "Трап", "Наличия багажа", "Наименование багажа", "Описание багажа", "Вес багажа", "Размер багажа", "Номер места"});

                table->setRowCount(1);
                table->setColumnCount(23);

                table->setItem(0, 0, new QTableWidgetItem(QString::number(ticketsFull.getTicketsId())));
                table->setItem(0, 1, new QTableWidgetItem(QString::number(ticketsFull.getTicketsPrice())));
                table->setItem(0, 2, new QTableWidgetItem(ticketsFull.getClientFirstName()));
                table->setItem(0, 3, new QTableWidgetItem(ticketsFull.getClientLastName()));
                table->setItem(0, 4, new QTableWidgetItem(ticketsFull.getClientPatronymic()));
                table->setItem(0, 5, new QTableWidgetItem(QString::number(ticketsFull.getClientPassportSeries())));
                table->setItem(0, 6, new QTableWidgetItem(QString::number(ticketsFull.getClientPassportNumber())));
                table->setItem(0, 7, new QTableWidgetItem(ticketsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(0, 8, new QTableWidgetItem(ticketsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(0, 9, new QTableWidgetItem(ticketsFull.getDeparturePoint()));
                table->setItem(0, 10, new QTableWidgetItem(ticketsFull.getArrivalPoint()));
                table->setItem(0, 11, new QTableWidgetItem(ticketsFull.getAirplaneName()));
                table->setItem(0, 12, new QTableWidgetItem(ticketsFull.getAirplaneDescription()));
                table->setItem(0, 13, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxSizeCargo())));
                table->setItem(0, 14, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxWeightCargo())));
                table->setItem(0, 15, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxSeatPlaces())));
                table->setItem(0, 16, new QTableWidgetItem(QString::number(ticketsFull.getFlightsLadder())));
                table->setItem(0, 17, new QTableWidgetItem((((ticketsFull.getTicketsBaggageAvailable() == 1)? "Да" : "Нет"))));
                table->setItem(0, 18, new QTableWidgetItem(ticketsFull.getBaggageName()));
                table->setItem(0, 19, new QTableWidgetItem(ticketsFull.getBaggageDescription()));
                table->setItem(0, 20, new QTableWidgetItem(QString::number(ticketsFull.getBaggageWeight())));
                table->setItem(0, 21, new QTableWidgetItem(QString::number(ticketsFull.getBaggageSize())));
                table->setItem(0, 22, new QTableWidgetItem(QString::number(ticketsFull.getTicketsSeatNumber())));

            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, TicketsFull(qobject_cast<QPushButton*>(table->cellWidget(0, 11))->property("Id").toInt(), 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false));
        });

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, TicketsTrunc(search->text().toInt(), 0, "", "", "", "", "", 0, false, "", 0, false));
}

void WindowTicketsClient::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 12); }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", ""});

        requester->getActiveTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {

            for(int counter = 0; counter < ticketsTrunc.size(); ++counter)
            {
                if((ticketsTrunc.at(counter).getClientFirstName() != dataClientFull.getClientFirstName()) && (ticketsTrunc.at(counter).getClientLastName() != dataClientFull.getClientLastName()) && (ticketsTrunc.at(counter).getClientPatronymic() != dataClientFull.getClientPatronymic()))
                {
                    ticketsTrunc.removeAt(counter);
                }
            }

            table->setRowCount(ticketsTrunc.size());
            table->setColumnCount(12);

            for(int counter = 0; counter < ticketsTrunc.size(); ++counter)
            {
                if((ticketsTrunc.at(counter).getClientFirstName() != dataClientFull.getClientFirstName()) && (ticketsTrunc.at(counter).getClientLastName() != dataClientFull.getClientLastName()) && (ticketsTrunc.at(counter).getClientPatronymic() != dataClientFull.getClientPatronymic())){ continue; }

                qDebug() << "DEBUG: " << ticketsTrunc.at(counter).getTicketsBaggageAvailable();

                table->setItem(counter, 0, new QTableWidgetItem(QString::number(ticketsTrunc.at(counter).getTicketsId())));
                table->setItem(counter, 1, new QTableWidgetItem(QString::number(ticketsTrunc.at(counter).getTicketsPrice())));
                table->setItem(counter, 2, new QTableWidgetItem(ticketsTrunc.at(counter).getClientFirstName()));
                table->setItem(counter, 3, new QTableWidgetItem(ticketsTrunc.at(counter).getClientLastName()));
                table->setItem(counter, 4, new QTableWidgetItem(ticketsTrunc.at(counter).getClientPatronymic()));
                table->setItem(counter, 5, new QTableWidgetItem(ticketsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(counter, 6, new QTableWidgetItem(ticketsTrunc.at(counter).getArrivalPoint()));
                table->setItem(counter, 7, new QTableWidgetItem(QString::number(ticketsTrunc.at(counter).getFlightsLadder())));
                table->setItem(counter, 8, new QTableWidgetItem((((ticketsTrunc.at(counter).getTicketsBaggageAvailable() == 1)? "Да" : "Нет"))));
                table->setItem(counter, 9, new QTableWidgetItem(ticketsTrunc.at(counter).getBaggageName()));
                table->setItem(counter, 10, new QTableWidgetItem(QString::number(ticketsTrunc.at(counter).getTicketsSeatNumber())));

                table->setCellWidget(counter, 11, new QPushButton("Детали"));

                table->cellWidget(counter, 11)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 11)), &QPushButton::clicked, [this, counter]()
                {
                        requester->searchTicketsFull([this](TicketsFull ticketsFull)
                        {
                            for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 11); }

                            table->clear();

                            table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Серия паспорта", "Номер паспорта", "Дата отправления", "Дата прибытия", "Точка отбытия", "Точка прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза", "Максимальный вес груза", "Количество сидячих мест", "Трап", "Наличия багажа", "Наименование багажа", "Описание багажа", "Вес багажа", "Размер багажа", "Номер места"});

                            //qDebug() << "DEBUG: " << ticketsFull.getBaggageName();
                            //qDebug() << "DEBUG: " << ticketsFull.getBaggageDescription();

                            table->setRowCount(1);
                            table->setColumnCount(23);

                            table->setItem(0, 0, new QTableWidgetItem(QString::number(ticketsFull.getTicketsId())));
                            table->setItem(0, 1, new QTableWidgetItem(QString::number(ticketsFull.getTicketsPrice())));
                            table->setItem(0, 2, new QTableWidgetItem(ticketsFull.getClientFirstName()));
                            table->setItem(0, 3, new QTableWidgetItem(ticketsFull.getClientLastName()));
                            table->setItem(0, 4, new QTableWidgetItem(ticketsFull.getClientPatronymic()));
                            table->setItem(0, 5, new QTableWidgetItem(QString::number(ticketsFull.getClientPassportSeries())));
                            table->setItem(0, 6, new QTableWidgetItem(QString::number(ticketsFull.getClientPassportNumber())));
                            table->setItem(0, 7, new QTableWidgetItem(ticketsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                            table->setItem(0, 8, new QTableWidgetItem(ticketsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss")));
                            table->setItem(0, 9, new QTableWidgetItem(ticketsFull.getDeparturePoint()));
                            table->setItem(0, 10, new QTableWidgetItem(ticketsFull.getArrivalPoint()));
                            table->setItem(0, 11, new QTableWidgetItem(ticketsFull.getAirplaneName()));
                            table->setItem(0, 12, new QTableWidgetItem(ticketsFull.getAirplaneDescription()));
                            table->setItem(0, 13, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxSizeCargo())));
                            table->setItem(0, 14, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxWeightCargo())));
                            table->setItem(0, 15, new QTableWidgetItem(QString::number(ticketsFull.getAirplaneMaxSeatPlaces())));
                            table->setItem(0, 16, new QTableWidgetItem(QString::number(ticketsFull.getFlightsLadder())));
                            table->setItem(0, 17, new QTableWidgetItem((((ticketsFull.getTicketsBaggageAvailable() == 1)? "Да" : "Нет"))));
                            table->setItem(0, 18, new QTableWidgetItem(ticketsFull.getBaggageName()));
                            table->setItem(0, 19, new QTableWidgetItem(ticketsFull.getBaggageDescription()));
                            table->setItem(0, 20, new QTableWidgetItem(QString::number(ticketsFull.getBaggageWeight())));
                            table->setItem(0, 21, new QTableWidgetItem(QString::number(ticketsFull.getBaggageSize())));
                            table->setItem(0, 22, new QTableWidgetItem(QString::number(ticketsFull.getTicketsSeatNumber())));

                        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                        {
                            QMessageBox::critical(this, "Ошибка", replyServer);
                        }, TicketsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 11))->property("Id").toInt(), 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false));
                        qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 11))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });

    table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", ""});
}

void WindowTicketsClient::onClickRefresh(){ refreshTable(); }

void WindowTicketsClient::onClickAdd()
{
    BaggageAndTicketsAndServices baggageAndTicketsAndServices;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    baggageAndTicketsAndServices = CustomInputWidget::getBaggageAndTicketsAndServices("Покупка пассажирского билета", okDialog, Host, dataClientFull.getClientId(), this);
    //qDebug() << "DEBUG" << tickets.getBaggageAvailable();

    if(!okDialog){ return; }
    qDebug() << "OK!1";

    qDebug() << "DEBUG: " << baggageAndTicketsAndServices.tickets.getPrice();

    requester->searchByIdClient([this, baggageAndTicketsAndServices](Client client)
    {

            qDebug() << "OK!2";

        if(client.getMoney() < baggageAndTicketsAndServices.tickets.getPrice())
        {
            qDebug() << baggageAndTicketsAndServices.tickets.getPrice();
            QMessageBox::critical(this, "Ошибка", "Это слишком дорого для вас!");
            return;
        }

            qDebug() << "OK!3";

        if(baggageAndTicketsAndServices.tickets.getBaggageAvailable())
        {
                qDebug() << "OK!4";

            requester->addBaggage([baggageAndTicketsAndServices, client, this](unsigned int id)
            {

                    qDebug() << "OK!5";

                    requester->addClientAndBaggage([this](bool success)
                    {

                    }, [this](unsigned errorCode, QString error, QString replyServer)
                    {
                        qDebug() << replyServer;

                    }, ClientAndBaggage(0, client.getId(), id, false));

                Tickets tickets = baggageAndTicketsAndServices.tickets;

                tickets.setBaggage(static_cast<const unsigned int>(id));

                requester->addTickets([baggageAndTicketsAndServices, client, this](unsigned int id)
                {
                        qDebug() << "OK!6";

                    Client client2 = client;
                    client2.setMoney(client.getMoney() - baggageAndTicketsAndServices.tickets.getPrice());

                    requester->setClient([this](bool success)
                    {

                            qDebug() << "OK!7";

                    }, [this](unsigned int errorCode, QString error, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, client2, client2);

                    QMessageBox::about(this, "Успех", "Билет успешно добавлен!");

                    for(int counter = 0; counter < baggageAndTicketsAndServices.services.size(); ++counter)
                    {

                            qDebug() << "OK!8";

                        requester->addTicketsAndServices([this](bool success)
                        {

                                qDebug() << "OK!9";

                        }, [this](unsigned int errorCode, QString error, QString replyServer)
                        {
                            QMessageBox::critical(this, "Ошибка", replyServer);
                        }, TicketsAndServices(0, baggageAndTicketsAndServices.services.at(counter).getId(), id, false));
                    }

                    refreshTable();

                }, [this](unsigned int errorCode, QString error, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, tickets);

            }, [this](unsigned int errorCode, QString error, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, baggageAndTicketsAndServices.baggage);
        }
        else
        {
                qDebug() << "OK!10";

            requester->addTickets([this, baggageAndTicketsAndServices, client](unsigned int id)
            {
                    qDebug() << "OK!11";

                Client client2 = client;
                client2.setMoney(client.getMoney() - baggageAndTicketsAndServices.tickets.getPrice());

                qDebug() << "OK!f " << client2.getId();
                    qDebug() << "V";

                requester->setClient([this](bool success)
                {
                    qDebug() << "OK!12";
                }, [this](unsigned int errorCode, QString error, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, client2, client2);


                for(int counter = 0; counter < baggageAndTicketsAndServices.services.size(); ++counter)
                {
                    requester->addTicketsAndServices([this](bool success)
                    {

                            qDebug() << "OK!13";

                    }, [this](unsigned int errorCode, QString error, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, TicketsAndServices(0, baggageAndTicketsAndServices.services.at(counter).getId(), id, false));
                }

                refreshTable();


            }, [this](unsigned int erroCode, QString error, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, baggageAndTicketsAndServices.tickets);
        }

    }, [this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);

    }, Client(baggageAndTicketsAndServices.tickets.getIdClient(), "", "", "", 0, 0, 0, 0, false));

//    return;

//    if(!okDialog){ return; }

//    requester->addTickets([this](bool success)
//    {
//        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
//        refreshTable();
//    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
//    {
//        QMessageBox::critical(this, "Ошибка", replyServer);
//    }, baggageAndTicketsAndServices.tickets);
}

void WindowTicketsClient::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(11);

    gen->addCaptionTable(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места"});

        requester->getActiveTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {
            qDebug() << ticketsTrunc.size();
            for(int counter = 0; counter < ticketsTrunc.size(); ++counter)
            {
                if((ticketsTrunc.at(counter).getClientFirstName() != dataClientFull.getClientFirstName()) && (ticketsTrunc.at(counter).getClientLastName() != dataClientFull.getClientLastName()) && (ticketsTrunc.at(counter).getClientPatronymic() != dataClientFull.getClientPatronymic())){ continue; }

                gen->addLineTable(ticketsTrunc.at(counter));
            }

            gen->saveHTMLFile();

            QMessageBox::about(this, "Успех", "Отчет успешно создан!");

            delete gen;
            gen = nullptr;

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            qDebug() << replyServer;
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
}

void WindowTicketsClient::onClickAddCargo()
{
    CargoAndTickets cargoAndTickets;
    bool ok = false;

    cargoAndTickets = CustomInputWidget::getCargoAndTickets("Покупка билета грузоперевозки", ok, Host, dataClientFull.getClientId(), this);

    if(!ok){ return; }

    requester->searchByIdClient([this, cargoAndTickets](Client client)
    {

        if(client.getMoney() < cargoAndTickets.tickets.getPrice())
        {
            QMessageBox::critical(this, "Ошибка", "Это слишком дорого для вас!");
            return;
        }

        client.setMoney(client.getMoney() - cargoAndTickets.tickets.getPrice());

        requester->addTickets([this, cargoAndTickets, client](unsigned int id)
        {

            Cargo cargo = cargoAndTickets.cargo;

            cargo.setIdTicket(static_cast<const int>(id));
            qDebug() << "r: " << cargo.getIdTicket();

            requester->addCargo([this, cargoAndTickets, client](unsigned int id)
            {

                requester->setClient([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Груз успешно добавлен");
                }, [this](unsigned int errorCode, QString error, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, client, client);

            }, [this](unsigned int errorCode, QString error, QString replyServer){
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, cargo);

        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, cargoAndTickets.tickets);

    }, [this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, Client(cargoAndTickets.tickets.getIdClient(), "", "", "", 0, 0, 0, 0, false));
}
