#include "WindowCategoriesCargo.h"

WindowCategoriesCargo::WindowCategoriesCargo(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
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

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowCategoriesCargo::~WindowCategoriesCargo()
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

void WindowCategoriesCargo::onClickSearch()
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

    requester->searchCategoriesCargo([this](CategoriesCargo categoriesCargo)
    {
        table->setRowCount(1);
        table->setColumnCount(7);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});

        if(categoriesCargo.getId() == 0){ return; }

        if(categoriesCargo.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        qDebug() << categoriesCargo.getId();
        table->setItem(0, 0, new QTableWidgetItem(QString::number(categoriesCargo.getId())));
        table->setItem(0, 1, new QTableWidgetItem(categoriesCargo.getName()));
        table->setItem(0, 2, new QTableWidgetItem(categoriesCargo.getDescription()));
        table->setItem(0, 3, new QTableWidgetItem((((categoriesCargo.getIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 4, new QPushButton("Удалить"));
        table->setCellWidget(0, 5, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 6, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 6, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 4)->setProperty("Id", categoriesCargo.getId());

        table->cellWidget(0, 5)->setProperty("Id", categoriesCargo.getId());
        table->cellWidget(0, 5)->setProperty("IsDeleted", (categoriesCargo.getIsDeleted() == 1));

        table->cellWidget(0, 6)->setProperty("Id", categoriesCargo.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 4)), &QPushButton::clicked, [this]()
        {
            requester->deleteCategoriesCargo([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("Id").toInt(), "", "", false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            CategoriesCargo categoriesCargo;
            bool okDialog = false;

            categoriesCargo = CustomInputWidget::getCategoriesCargo("Изменение категории", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            categoriesCargo.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("IsDeleted").toInt() == 1);
            qDebug() << categoriesCargo.getIsDeleted();

            requester->setCategoriesCargo([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", "", false), categoriesCargo);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterCategoriesCargo([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", "", false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverCategoriesCargo([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", "", false));
            });
        }

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, CategoriesCargo(0, search->text(), "", false));
    }

void WindowCategoriesCargo::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 4);
        delete table->cellWidget(counter, 5);
        delete table->cellWidget(counter, 6);
    }

    table->clear();

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActiveCategoriesCargo([this](QList<CategoriesCargo> categoriesCargo)
        {

            table->setRowCount(categoriesCargo.size());
            table->setColumnCount(7);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < categoriesCargo.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(categoriesCargo.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(categoriesCargo.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(categoriesCargo.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem((((categoriesCargo.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 4, new QPushButton("Удалить"));
                table->setCellWidget(counter, 5, new QPushButton("Изменить"));
                table->setCellWidget(counter, 6, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 4)->setProperty("Id", categoriesCargo.at(counter).getId());

                table->cellWidget(counter, 5)->setProperty("Id", categoriesCargo.at(counter).getId());
                table->cellWidget(counter, 5)->setProperty("IsDeleted", (categoriesCargo.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 6)->setProperty("Id", categoriesCargo.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", "", false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    CategoriesCargo categoriesCargo;
                    bool okDialog = false;

                    categoriesCargo = CustomInputWidget::getCategoriesCargo("Изменение категории", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    categoriesCargo.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("IsDeleted").toInt() == 1);

                    requester->setCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", false), categoriesCargo);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }
    else
    {
        requester->getDeleteCategoriesCargo([this](QList<CategoriesCargo> categoriesCargo)
        {

            table->setRowCount(categoriesCargo.size());
            table->setColumnCount(7);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < categoriesCargo.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(categoriesCargo.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(categoriesCargo.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(categoriesCargo.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem((((categoriesCargo.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 4, new QPushButton("Удалить"));
                table->setCellWidget(counter, 5, new QPushButton("Изменить"));
                table->setCellWidget(counter, 6, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 4)->setProperty("Id", categoriesCargo.at(counter).getId());

                table->cellWidget(counter, 5)->setProperty("Id", categoriesCargo.at(counter).getId());
                table->cellWidget(counter, 5)->setProperty("IsDeleted", (categoriesCargo.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 6)->setProperty("Id", categoriesCargo.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deleteCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", "", false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    CategoriesCargo categoriesCargo;
                    bool okDialog = false;

                    categoriesCargo = CustomInputWidget::getCategoriesCargo("Изменение категории", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    categoriesCargo.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("IsDeleted").toInt() == 1);

                    requester->setCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", "", false), categoriesCargo);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverCategoriesCargo([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, CategoriesCargo(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", "", false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Логически удалено ли", "", "", ""});
}

void WindowCategoriesCargo::onClickRefresh(){ refreshTable(); }

void WindowCategoriesCargo::onClickAdd()
{
    CategoriesCargo categoriesCargo;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    categoriesCargo = CustomInputWidget::getCategoriesCargo("Добавить категорию груза", okDialog, this);

    if(!okDialog){ return; }

    requester->addCategoriesCargo([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, categoriesCargo);
}

void WindowCategoriesCargo::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(4);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Описание", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeleteCategoriesCargo([this](QList<CategoriesCargo> categoriesCargo)
        {
            qDebug() << categoriesCargo.size();
            for(int counter = 0; counter < categoriesCargo.size(); ++counter){ gen->addLineTable(categoriesCargo.at(counter)); }

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
        requester->getActiveCategoriesCargo([this](QList<CategoriesCargo> categoriesCargo)
        {
            qDebug() << categoriesCargo.size();
            for(int counter = 0; counter < categoriesCargo.size(); ++counter){ gen->addLineTable(categoriesCargo.at(counter)); }

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
