#include "WindowPlacesOfAirports.h"

WindowPlacesOfAirports::WindowPlacesOfAirports(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9 ]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butAdd);
    layoutContaner->addWidget(butGenerateTable);
    layoutContaner->addWidget(deleted);

    search->setPlaceholderText("Название");
    search->setValidator(validator);

    table->setEditTriggers(QTableWidget::NoEditTriggers);

    layout->addWidget(container);
    layout->addWidget(table);

    refreshTable();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowPlacesOfAirports::~WindowPlacesOfAirports()
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

void WindowPlacesOfAirports::onClickSearch()
{
    QRegExp regExp("^[A-zА-я0-9]+ [A-zА-я0-9]+ [A-zА-я0-9]+$");

    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по стране, городу и улице не должно быть пустым!");
        return;
    }

    if(!regExp.exactMatch(search->text()))
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска должно содержать значение вида: Страна Город Улица");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 6);
        delete table->cellWidget(counter, 7);
        delete table->cellWidget(counter, 8);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});

    requester->searchPlacesOfAirports([this](PlacesOfAirports placesOfAirports)
    {
        table->setRowCount(1);
        table->setColumnCount(9);

        if(placesOfAirports.getId() == 0){ return; }

        if(placesOfAirports.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        qDebug() << placesOfAirports.getId();

        table->setItem(0, 0, new QTableWidgetItem(QString::number(placesOfAirports.getId())));
        table->setItem(0, 1, new QTableWidgetItem(placesOfAirports.getCountry()));
        table->setItem(0, 2, new QTableWidgetItem(placesOfAirports.getCity()));
        table->setItem(0, 3, new QTableWidgetItem(placesOfAirports.getStreet()));
        table->setItem(0, 4, new QTableWidgetItem(QString::number(placesOfAirports.getHouseNumber())));
        table->setItem(0, 5, new QTableWidgetItem((((placesOfAirports.getIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 6, new QPushButton("Удалить"));
        table->setCellWidget(0, 7, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 8, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 8, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 6)->setProperty("Id", placesOfAirports.getId());

        table->cellWidget(0, 7)->setProperty("Id", placesOfAirports.getId());
        table->cellWidget(0, 7)->setProperty("IsDeleted", (placesOfAirports.getIsDeleted() == 1));

        table->cellWidget(0, 8)->setProperty("Id", placesOfAirports.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
        {
            requester->deletePlacesOfAirports([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", "", "", 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            PlacesOfAirports placesOfAirport;
            bool okDialog = false;

            placesOfAirport = CustomInputWidget::getPlacesOfAirport("Изменение аэропорта", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            placesOfAirport.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("IsDeleted").toInt() == 1);
            qDebug() << placesOfAirport.getIsDeleted();

            requester->setPlacesOfAirports([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", "", 0, false), placesOfAirport);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 8)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterPlacesOfAirports([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("Id").toInt(), "", "", "", 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 8)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverPlacesOfAirports([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("Id").toInt(), "", "", "", 0, false));
            });
        }

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, PlacesOfAirports(0, search->text().split(' ').at(0), search->text().split(' ').at(1), search->text().split(' ').at(2), 0, false));
    }

void WindowPlacesOfAirports::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 6);
        delete table->cellWidget(counter, 7);
        delete table->cellWidget(counter, 8);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActivePlacesOfAirports([this](QList<PlacesOfAirports> placesOfAirports)
        {

            table->setRowCount(placesOfAirports.size());
            table->setColumnCount(9);

            for(int counter = 0; counter < placesOfAirports.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(placesOfAirports.at(counter).getCountry()));
                table->setItem(counter, 2, new QTableWidgetItem(placesOfAirports.at(counter).getCity()));
                table->setItem(counter, 3, new QTableWidgetItem(placesOfAirports.at(counter).getStreet()));
                table->setItem(counter, 4, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getHouseNumber())));
                table->setItem(counter, 5, new QTableWidgetItem((((placesOfAirports.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 6, new QPushButton("Удалить"));
                table->setCellWidget(counter, 7, new QPushButton("Изменить"));
                table->setCellWidget(counter, 8, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 6)->setProperty("Id", placesOfAirports.at(counter).getId());

                table->cellWidget(counter, 7)->setProperty("Id", placesOfAirports.at(counter).getId());
                table->cellWidget(counter, 7)->setProperty("IsDeleted", (placesOfAirports.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 8)->setProperty("Id", placesOfAirports.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deletePlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    PlacesOfAirports placesOfAirports;
                    bool okDialog = false;

                    placesOfAirports = CustomInputWidget::getPlacesOfAirport("Изменение аэропорта", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    placesOfAirports.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("IsDeleted").toInt() == 1);

                    requester->setPlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", "", 0, false), placesOfAirports);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterPlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", "", "", 0, false));
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
        requester->getDeletePlacesOfAirports([this](QList<PlacesOfAirports> placesOfAirports)
        {

            table->setRowCount(placesOfAirports.size());
            table->setColumnCount(9);

            for(int counter = 0; counter < placesOfAirports.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(placesOfAirports.at(counter).getCountry()));
                table->setItem(counter, 2, new QTableWidgetItem(placesOfAirports.at(counter).getCity()));
                table->setItem(counter, 3, new QTableWidgetItem(placesOfAirports.at(counter).getStreet()));
                table->setItem(counter, 4, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getHouseNumber())));
                table->setItem(counter, 5, new QTableWidgetItem((((placesOfAirports.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 6, new QPushButton("Удалить"));
                table->setCellWidget(counter, 7, new QPushButton("Изменить"));
                table->setCellWidget(counter, 8, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 6)->setProperty("Id", placesOfAirports.at(counter).getId());

                table->cellWidget(counter, 7)->setProperty("Id", placesOfAirports.at(counter).getId());
                table->cellWidget(counter, 7)->setProperty("IsDeleted", (placesOfAirports.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 8)->setProperty("Id", placesOfAirports.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deletePlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    PlacesOfAirports placesOfAirports;
                    bool okDialog = false;

                    placesOfAirports = CustomInputWidget::getPlacesOfAirport("Изменение аэропорта", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    placesOfAirports.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("IsDeleted").toInt() == 1);

                    requester->setPlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", "", 0, false), placesOfAirports);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverPlacesOfAirports([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, PlacesOfAirports(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", "", "", 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});
}

void WindowPlacesOfAirports::onClickRefresh(){ refreshTable(); }

void WindowPlacesOfAirports::onClickAdd()
{
    PlacesOfAirports placesOfAirports;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    placesOfAirports = CustomInputWidget::getPlacesOfAirport("Добавить аэропорт", okDialog, this);

    if(!okDialog){ return; }

    requester->addPlacesOfAirports([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, placesOfAirports);
}

void WindowPlacesOfAirports::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeletePlacesOfAirports([this](QList<PlacesOfAirports> placesOfAirports)
        {
            qDebug() << placesOfAirports.size();
            for(int counter = 0; counter < placesOfAirports.size(); ++counter){ gen->addLineTable(placesOfAirports.at(counter)); }

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
        requester->getActivePlacesOfAirports([this](QList<PlacesOfAirports> placesOfAirport)
        {
            qDebug() << placesOfAirport.size();
            for(int counter = 0; counter < placesOfAirport.size(); ++counter){ gen->addLineTable(placesOfAirport.at(counter)); }

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
