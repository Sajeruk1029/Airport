#include "WindowAirplane.h"

WindowAirplane::WindowAirplane(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
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

		table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    refreshTable();

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowAirplane::~WindowAirplane()
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

void WindowAirplane::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 7);
        delete table->cellWidget(counter, 8);
        delete table->cellWidget(counter, 9);
    }

    table->clear();

    requester->searchAirplane([this](Airplane airplane)
    {
        table->setRowCount(1);
        table->setColumnCount(10);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли", "", "", ""});

        if(airplane.getId() == 0){ return; }

        if(airplane.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(airplane.getId())));
        table->setItem(0, 1, new QTableWidgetItem(airplane.getName()));
        table->setItem(0, 2, new QTableWidgetItem(airplane.getDescription()));
        table->setItem(0, 3, new QTableWidgetItem(QString::number(airplane.getMaxSizeCargo())));
        table->setItem(0, 4, new QTableWidgetItem(QString::number(airplane.getMaxWeightCargo())));
        table->setItem(0, 5, new QTableWidgetItem(QString::number(airplane.getMaxSeatPlaces())));
        table->setItem(0, 6, new QTableWidgetItem((((airplane.getIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 7, new QPushButton("Удалить"));
        table->setCellWidget(0, 8, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 9, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 9, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 7)->setProperty("Id", airplane.getId());

        table->cellWidget(0, 8)->setProperty("Id", airplane.getId());
        table->cellWidget(0, 8)->setProperty("IsDeleted", (airplane.getIsDeleted() == 1));

        table->cellWidget(0, 9)->setProperty("Id", airplane.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 7)), &QPushButton::clicked, [this]()
        {
            requester->deleteAirplane([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(0, 7))->property("Id").toInt(), "", "", 0, 0, 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 8)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            Airplane airplane;
            bool okDialog = false;

            airplane = CustomInputWidget::getAirplane("Изменение самолета", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            airplane.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("IsDeleted").toInt() == 1);
            qDebug() << airplane.getIsDeleted();

            requester->setAirplane([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(0, 8))->property("Id").toInt(), "", "", 0, 0, 0, false), airplane);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 9)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterAirplane([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(0, 9))->property("Id").toInt(), "", "", 0, 0, 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 9)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverAirplane([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(0, 9))->property("Id").toInt(), "", "", 0, 0, 0, false));
            });
        }

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Airplane(0, search->text(), "", 0, 0, 0, false));
    }

void WindowAirplane::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 7);
        delete table->cellWidget(counter, 8);
        delete table->cellWidget(counter, 9);
    }

    table->clear();

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveAirplane([this](QList<Airplane> airplane)
        {
            table->setRowCount(airplane.size());
            table->setColumnCount(10);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < airplane.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(airplane.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(airplane.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(airplane.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxSizeCargo())));
                table->setItem(counter, 4, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxWeightCargo())));
                table->setItem(counter, 5, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxSeatPlaces())));
                table->setItem(counter, 6, new QTableWidgetItem((((airplane.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 7, new QPushButton("Удалить"));
                table->setCellWidget(counter, 8, new QPushButton("Изменить"));
                table->setCellWidget(counter, 9, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 7)->setProperty("Id", airplane.at(counter).getId());

                table->cellWidget(counter, 8)->setProperty("Id", airplane.at(counter).getId());
                table->cellWidget(counter, 8)->setProperty("IsDeleted", (airplane.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 9)->setProperty("Id", airplane.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, 0, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Airplane airplane;
                    bool okDialog = false;

                    airplane = CustomInputWidget::getAirplane("Изменение самолета", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    airplane.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("IsDeleted").toInt() == 1);

                    requester->setAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", "", 0, 0, 0, false), airplane);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 9)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 9))->property("Id").toInt(), "", "", 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 9))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteAirplane([this](QList<Airplane> airplane)
        {

            table->setRowCount(airplane.size());
            table->setColumnCount(10);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < airplane.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(airplane.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(airplane.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(airplane.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxSizeCargo())));
                table->setItem(counter, 4, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxWeightCargo())));
                table->setItem(counter, 5, new QTableWidgetItem(QString::number(airplane.at(counter).getMaxSeatPlaces())));
                table->setItem(counter, 6, new QTableWidgetItem((((airplane.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 7, new QPushButton("Удалить"));
                table->setCellWidget(counter, 8, new QPushButton("Изменить"));
                table->setCellWidget(counter, 9, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 7)->setProperty("Id", airplane.at(counter).getId());

                table->cellWidget(counter, 8)->setProperty("Id", airplane.at(counter).getId());
                table->cellWidget(counter, 8)->setProperty("IsDeleted", (airplane.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 9)->setProperty("Id", airplane.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 7)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 7))->property("Id").toInt(), "", "", 0, 0, 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 8)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Airplane airplane;
                    bool okDialog = false;

                    airplane = CustomInputWidget::getAirplane("Изменение самолета", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    airplane.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("IsDeleted").toInt() == 1);

                    requester->setAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 8))->property("Id").toInt(), "", "", 0, 0, 0, false), airplane);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 9)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverAirplane([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Airplane(qobject_cast<QPushButton*>(table->cellWidget(counter, 9))->property("Id").toInt(), "", "", 0, 0, 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 9))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли", "", "", ""});
}

void WindowAirplane::onClickRefresh(){ refreshTable(); }

void WindowAirplane::onClickAdd()
{
    Airplane airplane;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    airplane = CustomInputWidget::getAirplane("Добавить самолет", okDialog, this);

    if(!okDialog){ return; }

    requester->addAirplane([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, airplane);
}

void WindowAirplane::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(7);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Описание", "Максимальный размер груза", "Максимальный вес груза", "Масимум сидячих мест", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteAirplane([this](QList<Airplane> airplane)
        {
            qDebug() << airplane.size();
            for(int counter = 0; counter < airplane.size(); ++counter){ gen->addLineTable(airplane.at(counter)); }

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
        requester->getActiveAirplane([this](QList<Airplane> airplane)
        {
            qDebug() << airplane.size();
            for(int counter = 0; counter < airplane.size(); ++counter){ gen->addLineTable(airplane.at(counter)); }

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
