#include "WindowFlightsClient.h"

WindowFlightsClient::WindowFlightsClient(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[0-9\-: ]+$"))), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butGenerateTable);

    search->setPlaceholderText("Дата отправления");
    search->setValidator(validator);

    table->setEditTriggers(QTableWidget::NoEditTriggers);

    layout->addWidget(container);
    layout->addWidget(table);

		table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    refreshTable();

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowFlightsClient::~WindowFlightsClient()
{
    if(validator){ delete validator; }

    if(table){ delete table; }

    if(butSearch){ delete butSearch; }
    if(butRefresh){ delete butRefresh; }
    if(butGenerateTable){ delete butGenerateTable; }
    if(search){ delete search; }

    if(layoutContaner){ delete layoutContaner; }

    if(container){ delete container; }

    if(layout){ delete layout; }

    if(gen){ delete gen; }
}

void WindowFlightsClient::onClickSearch()
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

    requester->searchFlightsTrunc([this](FlightsTrunc flightsTrunc)
    {
        for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 4); }

        table->setRowCount(1);
        table->setColumnCount(5);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", ""});

        if(flightsTrunc.getFlightsId() == 0){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(flightsTrunc.getFlightsId())));
        table->setItem(0, 1, new QTableWidgetItem(flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
        table->setItem(0, 2, new QTableWidgetItem(flightsTrunc.getArrivalPoint()));
        table->setItem(0, 3, new QTableWidgetItem(QString::number(flightsTrunc.getFlightsLadder())));

        table->setCellWidget(0, 4, new QPushButton("Детали"));

        table->cellWidget(0, 4)->setProperty("Id", flightsTrunc.getFlightsId());
        table->cellWidget(0, 4)->setProperty("FlightsDepartureDate", flightsTrunc.getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 4)), &QPushButton::clicked, [this]()
        {
            requester->searchFlightsFull([this](FlightsFull flightsFull)
            {

                for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 5); }

                table->clear();

                table->setRowCount(1);
                table->setColumnCount(11);

                table->setHorizontalHeaderLabels(QStringList{"Id", "Дата прибытия", "Дата отправления", "Место отправления", "Место прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза самолета", "Максимальный вес груза самолета", "Максимум сидячих мест самолета", "Трап"});

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

            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, FlightsFull(qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("Id").toInt(), "", qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("FlightsDepartureDate").toString(), "", "", "", "", 0, 0, 0, 0, false));
        });
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, FlightsTrunc(0, search->text(), "", 0, false));
}

void WindowFlightsClient::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 4); }

    table->clear();

        requester->getActiveFlightsTrunc([this](QList<FlightsTrunc> flightsTrunc)
        {

            qDebug() << "G " << flightsTrunc.size();
            table->setRowCount(flightsTrunc.size());
            table->setColumnCount(5);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", ""});

            for(int counter = 0; counter < flightsTrunc.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsId())));
                table->setItem(counter, 1, new QTableWidgetItem(flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss")));
                table->setItem(counter, 2, new QTableWidgetItem(flightsTrunc.at(counter).getArrivalPoint()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(flightsTrunc.at(counter).getFlightsLadder())));

                table->setCellWidget(counter, 4, new QPushButton("Детали"));

                table->cellWidget(counter, 4)->setProperty("Id", flightsTrunc.at(counter).getFlightsId());
                table->cellWidget(counter, 4)->setProperty("FlightsDepartureDate", flightsTrunc.at(counter).getFlightsDepartureDate().toString("yyyy-MM-dd hh:mm:ss"));

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    requester->searchFlightsFull([this](FlightsFull flightsFull)
                    {
                        for(int counter = 0; counter < table->rowCount(); ++counter){ delete table->cellWidget(counter, 5); }

                        table->clear();

                        table->setRowCount(1);
                        table->setColumnCount(11);

                        table->setHorizontalHeaderLabels(QStringList{"Id", "Дата прибытия", "Дата отправления", "Место отправления", "Место прибытия", "Название самолета", "Описание самолета", "Максимальный размер груза самолета", "Максимальный вес груза самолета", "Максимум сидячих мест самолета", "Трап"});

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

                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, FlightsFull(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("FlightsDepartureDate").toString(), "", "", "", "", 0, 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });

    table->setHorizontalHeaderLabels(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", ""});
}

void WindowFlightsClient::onClickRefresh(){ refreshTable(); }

void WindowFlightsClient::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Время отбытия", "Место прибытия", "Трап", "Логически удалено ли"});

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
