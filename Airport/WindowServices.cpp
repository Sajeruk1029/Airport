#include "WindowServices.h"

WindowServices::WindowServices() : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester("http://localhost/")), gen(nullptr)
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

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowServices::~WindowServices()
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

void WindowServices::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 5);
        delete table->cellWidget(counter, 6);
        delete table->cellWidget(counter, 7);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли", "", "", ""});

    requester->searchServices([this](Services services)
    {
        table->setRowCount(1);
        table->setColumnCount(8);

        if(services.getId() == 0){ return; }

        if(services.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(services.getId())));
        table->setItem(0, 1, new QTableWidgetItem(services.getName()));
        table->setItem(0, 2, new QTableWidgetItem(services.getDescription()));
        table->setItem(0, 3, new QTableWidgetItem(QString::number(services.getPrice())));
        table->setItem(0, 4, new QTableWidgetItem((((services.getIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 5, new QPushButton("Удалить"));
        table->setCellWidget(0, 6, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 7, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 7, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 5)->setProperty("Id", services.getId());

        table->cellWidget(0, 6)->setProperty("Id", services.getId());
        table->cellWidget(0, 6)->setProperty("IsDeleted", (services.getIsDeleted() == 1));

        table->cellWidget(0, 7)->setProperty("Id", services.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
        {
            requester->deleteServices([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Services(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", "", 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            Services services;
            bool okDialog = false;

            services = CustomInputWidget::getServices("Изменение услуги", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            services.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("IsDeleted").toInt() == 1);
            qDebug() << services.getIsDeleted();

            requester->setServices([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Services(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", "", 0, false), services);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterServices([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Services(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverServices([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Services(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", 0, false));
            });
        }

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Services(0, search->text(), "", 0, false));
    }

void WindowServices::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 5);
        delete table->cellWidget(counter, 6);
        delete table->cellWidget(counter, 7);
    }

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли", "", "", ""});

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveServices([this](QList<Services> services)
        {

            table->setRowCount(services.size());
            table->setColumnCount(8);

            for(int counter = 0; counter < services.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(services.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(services.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(services.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(services.at(counter).getPrice())));
                table->setItem(counter, 4, new QTableWidgetItem((((services.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 5, new QPushButton("Удалить"));
                table->setCellWidget(counter, 6, new QPushButton("Изменить"));
                table->setCellWidget(counter, 7, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 5)->setProperty("Id", services.at(counter).getId());

                table->cellWidget(counter, 6)->setProperty("Id", services.at(counter).getId());
                table->cellWidget(counter, 6)->setProperty("IsDeleted", (services.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 7)->setProperty("Id", services.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Services services;
                    bool okDialog = false;

                    services = CustomInputWidget::getServices("Изменение услуги", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    services.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("IsDeleted").toInt() == 1);

                    requester->setServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", 0, false), services);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteServices([this](QList<Services> services)
        {

            table->setRowCount(services.size());
            table->setColumnCount(8);

            for(int counter = 0; counter < services.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(services.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(services.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(services.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(services.at(counter).getPrice())));
                table->setItem(counter, 4, new QTableWidgetItem((((services.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 5, new QPushButton("Удалить"));
                table->setCellWidget(counter, 6, new QPushButton("Изменить"));
                table->setCellWidget(counter, 7, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 5)->setProperty("Id", services.at(counter).getId());

                table->cellWidget(counter, 6)->setProperty("Id", services.at(counter).getId());
                table->cellWidget(counter, 6)->setProperty("IsDeleted", (services.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 7)->setProperty("Id", services.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Services services;
                    bool okDialog = false;

                    services = CustomInputWidget::getServices("Изменение услуги", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    services.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("IsDeleted").toInt() == 1);

                    requester->setServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", 0, false), services);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverServices([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Services(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли", "", "", ""});
}

void WindowServices::onClickRefresh(){ refreshTable(); }

void WindowServices::onClickAdd()
{
    Services services;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    services = CustomInputWidget::getServices("Добавить услугу", okDialog, this);

    if(!okDialog){ return; }

    requester->addServices([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, services);
}

void WindowServices::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteServices([this](QList<Services> services)
        {
            qDebug() << services.size();
            for(int counter = 0; counter < services.size(); ++counter){ gen->addLineTable(services.at(counter)); }

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
        requester->getActiveServices([this](QList<Services> services)
        {
            qDebug() << services.size();
            for(int counter = 0; counter < services.size(); ++counter){ gen->addLineTable(services.at(counter)); }

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
