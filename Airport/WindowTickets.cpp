#include "WindowTickets.h"

WindowTickets::WindowTickets(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить билет пассажира")), butAddCargo(new QPushButton("Добавить билет груза")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QIntValidator(0, 9999999)), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butAdd);
    layoutContaner->addWidget(butAddCargo);
    layoutContaner->addWidget(butGenerateTable);
    layoutContaner->addWidget(deleted);

    search->setPlaceholderText("Id");
    search->setValidator(validator);

    table->setEditTriggers(QTableWidget::NoEditTriggers);

    layout->addWidget(container);
    layout->addWidget(table);

		table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    refreshTable();

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
    connect(butAddCargo, SIGNAL(clicked()), this, SLOT(onClickAddCargo()));
}

WindowTickets::~WindowTickets()
{
    if(validator){ delete validator; }

    if(table){ delete table; }

    if(butSearch){ delete butSearch; }
    if(butRefresh){ delete butRefresh; }
    if(butAdd){ delete butAdd; }
    if(butAddCargo){ delete butAddCargo; }
    if(butGenerateTable){ delete butGenerateTable; }
    if(search){ delete search; }
    if(deleted){ delete deleted; }

    if(layoutContaner){ delete layoutContaner; }

    if(container){ delete container; }

    if(layout){ delete layout; }

    if(gen){ delete gen; }
}

void WindowTickets::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 12);
        delete table->cellWidget(counter, 13);
        delete table->cellWidget(counter, 14);
        delete table->cellWidget(counter, 15);
    }

    table->clear();

    requester->searchTicketsTrunc([this](TicketsTrunc ticketsTrunc)
    {
        table->setRowCount(1);
        table->setColumnCount(16);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", "Логически удалено ли", "", "", "", ""});

        if(ticketsTrunc.getTicketsId() == 0){ return; }

        if(ticketsTrunc.getTicketsIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

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
        table->setItem(0, 11, new QTableWidgetItem((((ticketsTrunc.getTicketsIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 12, new QPushButton("Удалить"));
        table->setCellWidget(0, 13, new QPushButton("Изменить"));
        table->setCellWidget(0, 14, new QPushButton("Удалить логически"));
        table->setCellWidget(0, 15, new QPushButton("Детали"));

        table->cellWidget(0, 12)->setProperty("Id", ticketsTrunc.getTicketsId());

        table->cellWidget(0, 13)->setProperty("Id", ticketsTrunc.getTicketsId());
        table->cellWidget(0, 13)->setProperty("IsDeleted", (ticketsTrunc.getTicketsIsDeleted() == 1));

        table->cellWidget(0, 14)->setProperty("Id", ticketsTrunc.getTicketsId());

        table->cellWidget(0, 15)->setProperty("Id", ticketsTrunc.getTicketsId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 12)), &QPushButton::clicked, [this]()
        {
            requester->deleteTickets([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(0, 12))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 13)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            BaggageAndTicketsAndServices baggageAndTicketsAndServices;
            bool okDialog = false;

            baggageAndTicketsAndServices = CustomInputWidget::getBaggageAndTicketsAndServices("Изменение билета", okDialog, Host, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            baggageAndTicketsAndServices.tickets.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 13))->property("IsDeleted").toInt() == 1);
            qDebug() << baggageAndTicketsAndServices.tickets.getIsDeleted();

            requester->setTickets([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(0, 13))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false), baggageAndTicketsAndServices.tickets);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 14)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterTickets([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(0, 14))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 14)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverTickets([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(0, 14))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
            });
        }

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 15)), &QPushButton::clicked, [this]()
        {
            requester->searchTicketsFull([this](TicketsFull ticketsFull)
            {
                for(int counter = 0; counter < table->rowCount(); ++counter)
                {
                    delete table->cellWidget(counter, 12);
                    delete table->cellWidget(counter, 13);
                    delete table->cellWidget(counter, 14);
                    delete table->cellWidget(counter, 15);
                }

                table->clear();

                table->setRowCount(1);
                table->setColumnCount(24);

                table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Серия паспорта", "Номер паспорта", "Дата отправления", "Дата прибытия", "Точка отбытия", "Точка прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза", "Максимальный вес груза", "Количество сидячих мест", "Трап", "Наличия багажа", "Наименование багажа", "Описание багажа", "Вес багажа", "Размер багажа", "Номер места", "Логически удалено ли"});

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
                table->setItem(0, 23, new QTableWidgetItem((((ticketsFull.getTicketsIsDeleted() == 1)? "Да" : "Нет"))));
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, TicketsFull(qobject_cast<QPushButton*>(table->cellWidget(0, 15))->property("Id").toInt(), 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false));
        });

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, TicketsTrunc(search->text().toInt(), 0, "", "", "", "", "", 0, false, "", 0, false));
}

void WindowTickets::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 12);
        delete table->cellWidget(counter, 13);
        delete table->cellWidget(counter, 14);
        delete table->cellWidget(counter, 15);
    }

    table->clear();

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {

            table->setRowCount(ticketsTrunc.size());
            table->setColumnCount(16);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", "Логически удалено ли", "", "", "", ""});

            for(int counter = 0; counter < ticketsTrunc.size(); ++counter)
            {
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
                table->setItem(counter, 11, new QTableWidgetItem((((ticketsTrunc.at(counter).getTicketsIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 12, new QPushButton("Удалить"));
                table->setCellWidget(counter, 13, new QPushButton("Изменить"));
                table->setCellWidget(counter, 14, new QPushButton("Удалить логически"));
                table->setCellWidget(counter, 15, new QPushButton("Детали"));

                table->cellWidget(counter, 12)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                table->cellWidget(counter, 13)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());
                table->cellWidget(counter, 13)->setProperty("IsDeleted", (ticketsTrunc.at(counter).getTicketsIsDeleted() == 1));

                table->cellWidget(counter, 14)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                table->cellWidget(counter, 15)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 12)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 12))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 13)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    BaggageAndTicketsAndServices baggageAndTicketsAndServices;
                    bool okDialog = false;

                    baggageAndTicketsAndServices = CustomInputWidget::getBaggageAndTicketsAndServices("Изменение билета", okDialog, Host, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    baggageAndTicketsAndServices.tickets.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 13))->property("IsDeleted").toInt() == 1);

                    requester->setTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 13))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false), baggageAndTicketsAndServices.tickets);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 14)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 14))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 14))->property("Id").toInt();
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 15)), &QPushButton::clicked, [this, counter]()
                {
                        requester->searchTicketsFull([this](TicketsFull ticketsFull)
                        {
                            for(int counter = 0; counter < table->rowCount(); ++counter)
                            {
                                delete table->cellWidget(counter, 12);
                                delete table->cellWidget(counter, 13);
                                delete table->cellWidget(counter, 14);
                                delete table->cellWidget(counter, 15);
                            }

                            table->clear();

                            table->setRowCount(1);
                            table->setColumnCount(24);

                            table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Серия паспорта", "Номер паспорта", "Дата отправления", "Дата прибытия", "Точка отбытия", "Точка прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза", "Максимальный вес груза", "Количество сидячих мест", "Трап", "Наличия багажа", "Наименование багажа", "Описание багажа", "Вес багажа", "Размер багажа", "Номер места", "Логически удалено ли"});

                            //qDebug() << "DEBUG: " << ticketsFull.getBaggageName();
                            //qDebug() << "DEBUG: " << ticketsFull.getBaggageDescription();

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
                            table->setItem(0, 23, new QTableWidgetItem((((ticketsFull.getTicketsIsDeleted() == 1)? "Да" : "Нет"))));

                        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                        {
                            QMessageBox::critical(this, "Ошибка", replyServer);
                        }, TicketsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 15))->property("Id").toInt(), 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false));
                        qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 15))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {

            table->setRowCount(ticketsTrunc.size());
            table->setColumnCount(16);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", "Логически удалено ли", "", "", "", ""});

            for(int counter = 0; counter < ticketsTrunc.size(); ++counter)
            {
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
                table->setItem(counter, 11, new QTableWidgetItem((((ticketsTrunc.at(counter).getTicketsIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 12, new QPushButton("Удалить"));
                table->setCellWidget(counter, 13, new QPushButton("Изменить"));
                table->setCellWidget(counter, 14, new QPushButton("Восстановить логически"));
                table->setCellWidget(counter, 15, new QPushButton("Детали"));

                table->cellWidget(counter, 12)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                table->cellWidget(counter, 13)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());
                table->cellWidget(counter, 13)->setProperty("IsDeleted", (ticketsTrunc.at(counter).getTicketsIsDeleted() == 1));

                table->cellWidget(counter, 14)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                table->cellWidget(counter, 15)->setProperty("Id", ticketsTrunc.at(counter).getTicketsId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 12)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 12))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 13)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    BaggageAndTicketsAndServices baggageAndTicketsAndServices;
                    bool okDialog = false;

                    baggageAndTicketsAndServices = CustomInputWidget::getBaggageAndTicketsAndServices("Изменение билета", okDialog, Host, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    baggageAndTicketsAndServices.tickets.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 13))->property("IsDeleted").toInt() == 1);

                    requester->setTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 13))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false), baggageAndTicketsAndServices.tickets);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 14)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverTickets([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Tickets(qobject_cast<QPushButton*>(table->cellWidget(counter, 14))->property("Id").toInt(), 0, 0, 0, 0, false, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 14))->property("Id").toInt();
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 15)), &QPushButton::clicked, [this, counter]()
                {
                    requester->searchTicketsFull([this](TicketsFull ticketsFull)
                    {
                        for(int counter = 0; counter < table->rowCount(); ++counter)
                        {
                            delete table->cellWidget(counter, 12);
                            delete table->cellWidget(counter, 13);
                            delete table->cellWidget(counter, 14);
                            delete table->cellWidget(counter, 15);
                        }

                        table->clear();

                        table->setRowCount(1);
                        table->setColumnCount(24);

                        table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Серия паспорта", "Номер паспорта", "Дата отправления", "Дата прибытия", "Точка отбытия", "Точка прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза", "Максимальный вес груза", "Количество сидячих мест", "Трап", "Наличия багажа", "Наименование багажа", "Описание багажа", "Вес багажа", "Размер багажа", "Номер места", "Логически удалено ли"});

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
                        table->setItem(0, 23, new QTableWidgetItem((((ticketsFull.getTicketsIsDeleted() == 1)? "Да" : "Нет"))));

                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, TicketsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 15))->property("Id").toInt(), 0, "", "", "", 0, 0, "", "", "", "", "", "", 0, 0, 0, 0, false, "", "", 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 15))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", "Логически удалено ли", "", "", "", ""});
}

void WindowTickets::onClickRefresh(){ refreshTable(); }

void WindowTickets::onClickAdd()
{
    BaggageAndTicketsAndServices baggageAndTicketsAndServices;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    baggageAndTicketsAndServices = CustomInputWidget::getBaggageAndTicketsAndServices("Добавить билет", okDialog, Host, this);
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

void WindowTickets::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(12);

    gen->addCaptionTable(QStringList{"Id", "Цена билета", "Имя клиента", "Фамилия клиента", "Отчество клиента", "Дата отправления", "Точка прибытия", "Трап", "Наличия багажа", "Наименование багажа", "Номер места", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {
            qDebug() << ticketsTrunc.size();
            for(int counter = 0; counter < ticketsTrunc.size(); ++counter){ gen->addLineTable(ticketsTrunc.at(counter)); }

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
    else
    {
        requester->getActiveTicketsTrunc([this](QList<TicketsTrunc> ticketsTrunc)
        {
            qDebug() << ticketsTrunc.size();
            for(int counter = 0; counter < ticketsTrunc.size(); ++counter){ gen->addLineTable(ticketsTrunc.at(counter)); }

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
}

void WindowTickets::onClickAddCargo()
{
    CargoAndTickets cargoAndTickets;
    bool ok = false;

    cargoAndTickets = CustomInputWidget::getCargoAndTickets("Добавление груза", ok, Host, this);

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
