#include "WindowFlights.h"

WindowFlights::WindowFlights(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[0-9\-: ]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butAdd);
    layoutContaner->addWidget(butGenerateTable);
    layoutContaner->addWidget(deleted);

    search->setPlaceholderText("Дата отправления");
    search->setValidator(validator);

    table->setEditTriggers(QTableWidget::NoEditTriggers);

    layout->addWidget(container);
    layout->addWidget(table);

    refreshTable();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли", "", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowFlights::~WindowFlights()
{
    if(validator){ delete validator; }

    if(table){ delete table; }

    if(butSearch){ delete butSearch; }
    if(butRefresh){ delete butRefresh; }
    if(butAdd){ delete butAdd; }
    if(butGenerateTable){ delete butGenerateTable; }
    if(search){ delete search; }
    if(deleted){ delete deleted; }

    if(layoutContaner){ delete layoutContaner; }

    if(container){ delete container; }

    if(layout){ delete layout; }

    if(gen){ delete gen; }
}

void WindowFlights::onClickSearch()
{
    QRegExp regExp("^[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}$");

    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по дате отправления не должно быть пустым!");
        return;
    }

    if(!regExp.exactMatch(search->text()))
    {
        QMessageBox::critical(this, "Ошибка", "Значение в поле поиска по дате отправление должно соответсвовать формату yyyy-MM-dd hh:mm:ss");
        return;
    }

    if(!QDateTime(QDateTime::fromString(search->text(), "yyyy-MM-dd hh:mm:ss")).isValid())
    {
        QMessageBox::critical(this, "Ошибка", "Дата введена некорректно");
        return;
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли", "", "", "", ""});

    requester->searchFlightsTrunc([this](FlightsTrunc flightsTrunc)
    {
        for(int counter = 0; counter < table->rowCount(); ++counter)
        {
            delete table->cellWidget(counter, 5);
            delete table->cellWidget(counter, 6);
            delete table->cellWidget(counter, 7);
            delete table->cellWidget(counter, 8);
        }

        table->setRowCount(1);
        table->setColumnCount(9);

        if(flightsTrunc.getFlightsId() == 0){ return; }

        if(flightsTrunc.getFlightsIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(flightsTrunc.getFlightsId())));
        table->setItem(0, 1, new QTableWidgetItem(flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
        table->setItem(0, 2, new QTableWidgetItem(flightsTrunc.getArrivalPoint()));
        table->setItem(0, 3, new QTableWidgetItem(QString::number(flightsTrunc.getFlightsLadder())));
        table->setItem(0, 4, new QTableWidgetItem(((flightsTrunc.getFlightsIsDeleted() == 1)? "Да" : "Нет")));

        table->setCellWidget(0, 5, new QPushButton("Удалить"));
        table->setCellWidget(0, 6, new QPushButton("Изменить"));
        table->setCellWidget(0, 7, new QPushButton("Удалить логически"));
        table->setCellWidget(0, 8, new QPushButton("Детали"));

        table->cellWidget(0, 5)->setProperty("Id", flightsTrunc.getFlightsId());

        table->cellWidget(0, 6)->setProperty("Id", flightsTrunc.getFlightsId());
        table->cellWidget(0, 6)->setProperty("IsDeleted", (flightsTrunc.getFlightsIsDeleted() == 1));

        table->cellWidget(0, 7)->setProperty("Id", flightsTrunc.getFlightsId());

        table->cellWidget(0, 8)->setProperty("Id", flightsTrunc.getFlightsId());
        table->cellWidget(0, 8)->setProperty("FlightsDepartureDate", flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
        {
            requester->deleteFlights([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Flights(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            Flights flights;
            bool okDialog = false;

            flights = CustomInputWidget::getFlights("Изменение рейса", okDialog, Host, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            flights.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("IsDeleted").toInt() == 1);
            qDebug() << flights.getIsDeleted();

            requester->setFlights([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Flights(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", "", 0, 0, 0, 0, false), flights);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterFlights([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Flights(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverFlights([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Flights(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
            });
        }

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 8)), &QPushButton::clicked, [this]()
        {
            requester->searchFlightsFull([this](FlightsFull flightsFull)
            {

                for(int counter = 0; counter < table->rowCount(); ++counter)
                {
                    delete table->cellWidget(counter, 5);
                    delete table->cellWidget(counter, 6);
                    delete table->cellWidget(counter, 7);
                    delete table->cellWidget(counter, 8);
                }

                table->clear();

                table->setHorizontalHeaderLabels(QStringList{"Id", "Дата прибытия", "Дата отправления", "Место отправления", "Место прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза самолета", "Максимальный вес груза самолета", "Максимум сидячих мест самолета", "Трап", "Логически удалено ли"});

                table->setRowCount(1);
                table->setColumnCount(12);

                table->setItem(0, 0, new QTableWidgetItem(QString::number(flightsFull.getFlightsId())));
                table->setItem(0, 1, new QTableWidgetItem(flightsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(0, 2, new QTableWidgetItem(flightsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(0, 3, new QTableWidgetItem(flightsFull.getDeparturePoint()));
                table->setItem(0, 4, new QTableWidgetItem(flightsFull.getArrivalPoint()));
                table->setItem(0, 5, new QTableWidgetItem(flightsFull.getAirplaneName()));
                table->setItem(0, 6, new QTableWidgetItem(flightsFull.getAirplaneDescription()));
                table->setItem(0, 7, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSizeCargo())));
                table->setItem(0, 8, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxWeightCargo())));
                table->setItem(0, 9, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSeatPlaces())));
                table->setItem(0, 10, new QTableWidgetItem(QString::number(flightsFull.getFlightsLadder())));
                table->setItem(0, 11, new QTableWidgetItem((flightsFull.getFlightsIsDeleted() == 1)? "Да" : "Нет"));

            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, FlightsFull(qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("Id").toInt(), "", qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("FlightsDepartureDate").toString(), "", "", "", "", 0, 0, 0, 0, false));
        });
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, FlightsTrunc(0, search->text(), "", 0, false));
}

void WindowFlights::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 5);
        delete table->cellWidget(counter, 6);
        delete table->cellWidget(counter, 7);
        delete table->cellWidget(counter, 8);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли", "", "", "", ""});

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveFlightsTrunc([this](QList<FlightsTrunc> flightsTrunc)
        {

            qDebug() << "G " << flightsTrunc.size();
            table->setRowCount(flightsTrunc.size());
            table->setColumnCount(9);

            for(int counter = 0; counter < flightsTrunc.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsId())));
                table->setItem(counter, 1, new QTableWidgetItem(flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(counter, 2, new QTableWidgetItem(flightsTrunc.at(counter).getArrivalPoint()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsLadder())));
                table->setItem(0, 4, new QTableWidgetItem(((flightsTrunc.at(counter).getFlightsIsDeleted() == 1)? "Да" : "Нет")));

                table->setCellWidget(counter, 5, new QPushButton("Удалить"));
                table->setCellWidget(counter, 6, new QPushButton("Изменить"));
                table->setCellWidget(counter, 7, new QPushButton("Удалить логически"));
                table->setCellWidget(counter, 8, new QPushButton("Детали"));

                table->cellWidget(counter, 5)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());

                table->cellWidget(counter, 6)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());
                table->cellWidget(counter, 6)->setProperty("IsDeleted", (flightsTrunc.at(counter).getFlightsIsDeleted() == 1));

                table->cellWidget(counter, 7)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());

                table->cellWidget(counter, 8)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());
                table->cellWidget(counter, 8)->setProperty("FlightsDepartureDate", flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Flights flights;
                    bool okDialog = false;

                    flights = CustomInputWidget::getFlights("Изменение рейса", okDialog, Host, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    flights.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("IsDeleted").toInt() == 1);

                    requester->setFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", 0, 0, 0, 0, false), flights);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt();
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    requester->searchFlightsFull([this](FlightsFull flightsFull)
                    {
                        for(int counter = 0; counter < table->rowCount(); ++counter)
                        {
                            delete table->cellWidget(counter, 5);
                            delete table->cellWidget(counter, 6);
                            delete table->cellWidget(counter, 7);
                            delete table->cellWidget(counter, 8);
                        }

                        table->clear();

                        table->setHorizontalHeaderLabels(QStringList{"Id", "Дата прибытия", "Дата отправления", "Место отправления", "Место прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза самолета", "Максимальный вес груза самолета", "Максимум сидячих мест самолета", "Трап", "Логически удалено ли"});

                        table->setRowCount(1);
                        table->setColumnCount(12);

                        table->setItem(0, 0, new QTableWidgetItem(QString::number(flightsFull.getFlightsId())));
                        table->setItem(0, 1, new QTableWidgetItem(flightsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss")));
                        table->setItem(0, 2, new QTableWidgetItem(flightsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                        table->setItem(0, 3, new QTableWidgetItem(flightsFull.getDeparturePoint()));
                        table->setItem(0, 4, new QTableWidgetItem(flightsFull.getArrivalPoint()));
                        table->setItem(0, 5, new QTableWidgetItem(flightsFull.getAirplaneName()));
                        table->setItem(0, 6, new QTableWidgetItem(flightsFull.getAirplaneDescription()));
                        table->setItem(0, 7, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSizeCargo())));
                        table->setItem(0, 8, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxWeightCargo())));
                        table->setItem(0, 9, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSeatPlaces())));
                        table->setItem(0, 10, new QTableWidgetItem(QString::number(flightsFull.getFlightsLadder())));
                        table->setItem(0, 11, new QTableWidgetItem((flightsFull.getFlightsIsDeleted() == 1)? "Да" : "Нет"));

                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, FlightsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("FlightsDepartureDate").toString(), "", "", "", "", 0, 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteFlightsTrunc([this](QList<FlightsTrunc> flightsTrunc)
        {

            table->setRowCount(flightsTrunc.size());
            table->setColumnCount(9);

            for(int counter = 0; counter < flightsTrunc.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsId())));
                table->setItem(counter, 1, new QTableWidgetItem(flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(counter, 2, new QTableWidgetItem(flightsTrunc.at(counter).getArrivalPoint()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsLadder())));
                table->setItem(0, 4, new QTableWidgetItem(((flightsTrunc.at(counter).getFlightsIsDeleted() == 1)? "Да" : "Нет")));

                table->setCellWidget(counter, 5, new QPushButton("Удалить"));
                table->setCellWidget(counter, 6, new QPushButton("Изменить"));
                table->setCellWidget(counter, 7, new QPushButton("Восстановить логически"));
                table->setCellWidget(counter, 8, new QPushButton("Детали"));

                table->cellWidget(counter, 5)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());

                table->cellWidget(counter, 6)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());
                table->cellWidget(counter, 6)->setProperty("IsDeleted", (flightsTrunc.at(counter).getFlightsIsDeleted() == 1));

                table->cellWidget(counter, 7)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());

                table->cellWidget(counter, 8)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());
                table->cellWidget(counter, 8)->setProperty("FlightsDepartureDate", flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Flights flights;
                    bool okDialog = false;

                    flights = CustomInputWidget::getFlights("Изменение рейса", okDialog, Host, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    flights.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("IsDeleted").toInt() == 1);

                    requester->setFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", 0, 0, 0, 0, false), flights);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverFlights([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Flights(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt();
                });

                qDebug() << "TEST2 " << qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("FlightsDepartureDate").toString();

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    requester->searchFlightsFull([this](FlightsFull flightsFull)
                    {
                        for(int counter = 0; counter < table->rowCount(); ++counter)
                        {
                            delete table->cellWidget(counter, 5);
                            delete table->cellWidget(counter, 6);
                            delete table->cellWidget(counter, 7);
                            delete table->cellWidget(counter, 8);
                        }

                        table->clear();

                        table->setHorizontalHeaderLabels(QStringList{"Id", "Дата прибытия", "Дата отправления", "Место отправления", "Место прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза самолета", "Максимальный вес груза самолета", "Максимум сидячих мест самолета", "Трап", "Логически удалено ли"});

                        table->setRowCount(1);
                        table->setColumnCount(12);

                        table->setItem(0, 0, new QTableWidgetItem(QString::number(flightsFull.getFlightsId())));
                        table->setItem(0, 1, new QTableWidgetItem(flightsFull.getFlightsArrivalDate().toString("yyyy-MM-dd hh:mm:ss")));
                        table->setItem(0, 2, new QTableWidgetItem(flightsFull.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                        table->setItem(0, 3, new QTableWidgetItem(flightsFull.getDeparturePoint()));
                        table->setItem(0, 4, new QTableWidgetItem(flightsFull.getArrivalPoint()));
                        table->setItem(0, 5, new QTableWidgetItem(flightsFull.getAirplaneName()));
                        table->setItem(0, 6, new QTableWidgetItem(flightsFull.getAirplaneDescription()));
                        table->setItem(0, 7, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSizeCargo())));
                        table->setItem(0, 8, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxWeightCargo())));
                        table->setItem(0, 9, new QTableWidgetItem(QString::number(flightsFull.getAirplaneMaxSeatPlaces())));
                        table->setItem(0, 10, new QTableWidgetItem(QString::number(flightsFull.getFlightsLadder())));
                        table->setItem(0, 11, new QTableWidgetItem((flightsFull.getFlightsIsDeleted() == 1)? "Да" : "Нет"));

                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, FlightsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("FlightsDepartureDate").toString(), "", "", "", "", 0, 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли", "", "", "", ""});
}

void WindowFlights::onClickRefresh(){ refreshTable(); }

void WindowFlights::onClickAdd()
{
    Flights flights;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    flights = CustomInputWidget::getFlights("Добавить рейс", okDialog, Host, this);
    //qDebug() << "DEBUG" << tickets.getBaggageAvailable();

    if(!okDialog){ return; }

    requester->addFlights([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, flights);
}

void WindowFlights::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteFlightsTrunc([this](QList<FlightsTrunc> flightsTrunc)
        {
            qDebug() << flightsTrunc.size();
            for(int counter = 0; counter < flightsTrunc.size(); ++counter){ gen->addLineTable(flightsTrunc.at(counter)); }

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
        requester->getActiveFlightsTrunc([this](QList<FlightsTrunc> flightsTrunc)
        {
            qDebug() << flightsTrunc.size();
            for(int counter = 0; counter < flightsTrunc.size(); ++counter){ gen->addLineTable(flightsTrunc.at(counter)); }

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
