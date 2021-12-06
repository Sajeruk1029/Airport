#include "WindowAirCompany.h"

WindowAirCompany::WindowAirCompany(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
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

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Логически удалено ли", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowAirCompany::~WindowAirCompany()
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

void WindowAirCompany::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 3);
        delete table->cellWidget(counter, 4);
        delete table->cellWidget(counter, 5);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Логически удалено ли", "", "", ""});

    requester->searchAirCompany([this](AirCompany airCompany)
    {
        table->setRowCount(1);
        table->setColumnCount(6);

        if(airCompany.getId() == 0){ return; }

        if(airCompany.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(airCompany.getId())));
        table->setItem(0, 1, new QTableWidgetItem(airCompany.getName()));
        table->setItem(0, 2, new QTableWidgetItem((airCompany.getIsDeleted() == 1)? "Да" : "Нет"));

        table->setCellWidget(0, 3, new QPushButton("Удалить"));
        table->setCellWidget(0, 4, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 5, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 5, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 3)->setProperty("Id", airCompany.getId());

        table->cellWidget(0, 4)->setProperty("Id", airCompany.getId());
        table->cellWidget(0, 4)->setProperty("IsDeleted", airCompany.getIsDeleted() == 1);

        table->cellWidget(0, 5)->setProperty("Id", airCompany.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 3)), &QPushButton::clicked, [this]()
        {
            requester->deleteAirCompany([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(0, 3))->property("Id").toInt(), "", false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 4)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            AirCompany airCompany;
            bool okDialog = false;

            airCompany = CustomInputWidget::getAirCompany("Изменение авиакомпании", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            airCompany.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("IsDeleted").toInt() == 1);
            qDebug() << airCompany.getIsDeleted();

            requester->setAirCompany([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("Id").toInt(), "", false), airCompany);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterAirCompany([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverAirCompany([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", false));
            });
        }

    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, AirCompany(0, search->text(), false));
}

void WindowAirCompany::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 3);
        delete table->cellWidget(counter, 4);
        delete table->cellWidget(counter, 5);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Логически удалено ли", "", "", ""});

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveAirCompany([this](QList<AirCompany> airCompanies)
        {

            table->setRowCount(airCompanies.size());
            table->setColumnCount(6);

            for(int counter = 0; counter < airCompanies.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(airCompanies.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(airCompanies.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem((((airCompanies.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 3, new QPushButton("Удалить"));
                table->setCellWidget(counter, 4, new QPushButton("Изменить"));
                table->setCellWidget(counter, 5, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 3)->setProperty("Id", airCompanies.at(counter).getId());

                table->cellWidget(counter, 4)->setProperty("Id", airCompanies.at(counter).getId());
                table->cellWidget(counter, 4)->setProperty("IsDeleted", (airCompanies.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 5)->setProperty("Id", airCompanies.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 3)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteAirCompany([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 3))->property("Id").toInt(), "", false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    AirCompany airCompany;
                    bool okDialog = false;

                    airCompany = CustomInputWidget::getAirCompany("Изменение авиакомпании", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    airCompany.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("IsDeleted").toInt() == 1);

                    requester->setAirCompany([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", false), airCompany);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterAirCompany([this, counter](bool success)
                    {
                        //qDebug() << counter;
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", false));
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteAirCompany([this](QList<AirCompany> airCompanies)
        {

            table->setRowCount(airCompanies.size());
            table->setColumnCount(6);

            for(int counter = 0; counter < airCompanies.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(airCompanies.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(airCompanies.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem((((airCompanies.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 3, new QPushButton("Удалить"));
                table->setCellWidget(counter, 4, new QPushButton("Изменить"));
                table->setCellWidget(counter, 5, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 3)->setProperty("Id", airCompanies.at(counter).getId());

                table->cellWidget(counter, 4)->setProperty("Id", airCompanies.at(counter).getId());
                table->cellWidget(counter, 4)->setProperty("IsDeleted", (airCompanies.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 5)->setProperty("Id", airCompanies.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 3)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteAirCompany([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 3))->property("Id").toInt(), "", false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    AirCompany airCompany;
                    bool okDialog = false;

                    airCompany = CustomInputWidget::getAirCompany("Изменение авиакомпании", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    airCompany.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("IsDeleted").toInt() == 1);

                    requester->setAirCompany([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", false), airCompany);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverAirCompany([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, AirCompany(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Логически удалено ли", "", "", ""});
}

void WindowAirCompany::onClickRefresh(){ refreshTable(); }

void WindowAirCompany::onClickAdd()
{
    AirCompany airCompany;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    airCompany = CustomInputWidget::getAirCompany("Добавить авиакомпанию", okDialog, this);

    if(!okDialog){ return; }

    requester->addAirCompany([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, airCompany);
}

void WindowAirCompany::onClickGeneratedHTML()
{    
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(3);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteAirCompany([this](QList<AirCompany> airCompanies)
        {
            qDebug() << airCompanies.size();
            for(int counter = 0; counter < airCompanies.size(); ++counter){ gen->addLineTable(airCompanies.at(counter)); }

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
        requester->getActiveAirCompany([this](QList<AirCompany> airCompanies)
        {
            qDebug() << airCompanies.size();
            for(int counter = 0; counter < airCompanies.size(); ++counter){ gen->addLineTable(airCompanies.at(counter)); }

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
