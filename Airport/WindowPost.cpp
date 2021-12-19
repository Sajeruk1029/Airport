#include "WindowPost.h"

WindowPost::WindowPost(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butAdd(new QPushButton("Добавить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), deleted(new QCheckBox("Удаленные")), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
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

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butAdd, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowPost::~WindowPost()
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

void WindowPost::onClickSearch()
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

    requester->searchPost([this](Post post)
    {
        table->setRowCount(1);
        table->setColumnCount(7);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Зарплата", "Логически удалено ли", "", "", ""});

        if(post.getId() == 0){ return; }

        if(post.getIsDeleted() != (deleted->checkState() == Qt::CheckState::Checked)){ return; }

        qDebug() << post.getId();
        table->setItem(0, 0, new QTableWidgetItem(QString::number(post.getId())));
        table->setItem(0, 1, new QTableWidgetItem(post.getName()));
        table->setItem(0, 2, new QTableWidgetItem(QString::number(post.getSalary())));
        table->setItem(0, 3, new QTableWidgetItem((((post.getIsDeleted() == 1)? "Да" : "Нет"))));

        table->setCellWidget(0, 4, new QPushButton("Удалить"));
        table->setCellWidget(0, 5, new QPushButton("Изменить"));

        if(deleted->checkState() == Qt::CheckState::Checked){ table->setCellWidget(0, 6, new QPushButton("Восстановить логически")); }
        else{ table->setCellWidget(0, 6, new QPushButton("Удалить логически")); }

        table->cellWidget(0, 4)->setProperty("Id", post.getId());

        table->cellWidget(0, 5)->setProperty("Id", post.getId());
        table->cellWidget(0, 5)->setProperty("IsDeleted", (post.getIsDeleted() == 1));

        table->cellWidget(0, 6)->setProperty("Id", post.getId());

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 4)), &QPushButton::clicked, [this]()
        {
            requester->deletePost([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Post(qobject_cast<QPushButton*>(table->cellWidget(0, 4))->property("Id").toInt(), "", 0, false));
        });

        connect(qobject_cast<QPushButton*>(table->cellWidget(0, 5)), &QPushButton::clicked, [this]()
        {
            //QString name = "";
            Post post;
            bool okDialog = false;

            post = CustomInputWidget::getPost("Изменение должности", okDialog, this);

            if(!okDialog){ return; }

            //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

            //if((okDialog) && name.isEmpty())
            //{
                //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                //return;
            //}

            post.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("IsDeleted").toInt() == 1);
            qDebug() << post.getIsDeleted();

            requester->setPost([this](bool success)
            {
                QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                refreshTable();
            }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
            {
                QMessageBox::critical(this, "Ошибка", replyServer);
            }, Post(qobject_cast<QPushButton*>(table->cellWidget(0, 5))->property("Id").toInt(), "", 0, false), post);
        });

        if(deleted->checkState() != Qt::CheckState::Checked)
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
            {
                requester->logicalDeleterPost([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Post(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", 0, false));
            });
        }
        else
        {
            connect(qobject_cast<QPushButton*>(table->cellWidget(0, 6)), &QPushButton::clicked, [this]()
            {
                requester->logicalRecoverPost([this](bool success)
                {
                    QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");


                    refreshTable();
                }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                {
                    QMessageBox::critical(this, "Ошибка", replyServer);
                }, Post(qobject_cast<QPushButton*>(table->cellWidget(0, 6))->property("Id").toInt(), "", 0, false));
            });
        }

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Post(0, search->text(), 0, false));
    }

void WindowPost::refreshTable()
{
    for(int counter = 0; counter < table->rowCount(); ++counter)
    {
        delete table->cellWidget(counter, 4);
        delete table->cellWidget(counter, 5);
        delete table->cellWidget(counter, 6);
    }

    table->clear();

    if(deleted->checkState() != Qt::CheckState::Checked)
    {
        requester->getActivePost([this](QList<Post> post)
        {

            table->setRowCount(post.size());
            table->setColumnCount(7);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Зарплата", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < post.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(post.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(post.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(QString::number(post.at(counter).getSalary())));
                table->setItem(counter, 3, new QTableWidgetItem((((post.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 4, new QPushButton("Удалить"));
                table->setCellWidget(counter, 5, new QPushButton("Изменить"));
                table->setCellWidget(counter, 6, new QPushButton("Удалить логически"));

                table->cellWidget(counter, 4)->setProperty("Id", post.at(counter).getId());

                table->cellWidget(counter, 5)->setProperty("Id", post.at(counter).getId());
                table->cellWidget(counter, 5)->setProperty("IsDeleted", (post.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 6)->setProperty("Id", post.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deletePost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Post post;
                    bool okDialog = false;

                    post = CustomInputWidget::getPost("Изменение должности", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    post.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("IsDeleted").toInt() == 1);

                    requester->setPost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", 0, false), post);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalDeleterPost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", 0, false));
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
        requester->getDeletePost([this](QList<Post> post)
        {

            table->setRowCount(post.size());
            table->setColumnCount(7);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Зарплата", "Логически удалено ли", "", "", ""});

            for(int counter = 0; counter < post.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(post.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(post.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(QString::number(post.at(counter).getSalary())));
                table->setItem(counter, 3, new QTableWidgetItem((((post.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));

                table->setCellWidget(counter, 4, new QPushButton("Удалить"));
                table->setCellWidget(counter, 5, new QPushButton("Изменить"));
                table->setCellWidget(counter, 6, new QPushButton("Восстановить логически"));

                table->cellWidget(counter, 4)->setProperty("Id", post.at(counter).getId());

                table->cellWidget(counter, 5)->setProperty("Id", post.at(counter).getId());
                table->cellWidget(counter, 5)->setProperty("IsDeleted", (post.at(counter).getIsDeleted() == 1));

                table->cellWidget(counter, 6)->setProperty("Id", post.at(counter).getId());

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 4)), &QPushButton::clicked, [this, counter]()
                {
                    requester->deletePost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Удаление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 4))->property("Id").toInt(), "", 0, false));
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 5)), &QPushButton::clicked, [this, counter]()
                {
                    //QString name = "";
                    Post post;
                    bool okDialog = false;

                    post = CustomInputWidget::getPost("Изменение должности", okDialog, this);

                    if(!okDialog){ return; }

                    //name = QInputDialog::getText(this, "Изменение авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

                    //if((okDialog) && name.isEmpty())
                    //{
                        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
                        //return;
                    //}

                    post.setIsDeleted(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("IsDeleted").toInt() == 1);

                    requester->setPost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Изменение прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 5))->property("Id").toInt(), "", 0, false), post);
                });

                connect(qobject_cast<QPushButton*>(table->cellWidget(counter, 6)), &QPushButton::clicked, [this, counter]()
                {
                    requester->logicalRecoverPost([this](bool success)
                    {
                        QMessageBox::about(this, "Успех", "Логическое восстановление прошло успешно!");
                        refreshTable();
                    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
                    {
                        QMessageBox::critical(this, "Ошибка", replyServer);
                    }, Post(qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt(), "", 0, false));
                    qDebug() << qobject_cast<QPushButton*>(table->cellWidget(counter, 6))->property("Id").toInt();
                });
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });
    }

    //table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Зарплата", "Логически удалено ли", "", "", ""});
}

void WindowPost::onClickRefresh(){ refreshTable(); }

void WindowPost::onClickAdd()
{
    Post post;
    bool okDialog = false;

    //name = QInputDialog::getText(this, "Добавить авиакомпании", "Наименование авиакомпании", QLineEdit::Normal, QString(), &okDialog);

    //if((!okDialog) && name.isEmpty())
    //{
        //QMessageBox::critical(this, "Ошибка", "Наименование авиакомпании не может быть пустым!");
        //return;
    //}

    post = CustomInputWidget::getPost("Добавить должность", okDialog, this);

    if(!okDialog){ return; }

    requester->addPost([this](bool success)
    {
        QMessageBox::about(this, "Успех", "Добавление прошло успешно!");
        refreshTable();
    }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, post);
}

void WindowPost::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Зарплата", "Логически удалено ли"});

    if(deleted->checkState() == Qt::CheckState::Checked)
    {
        requester->getDeletePost([this](QList<Post> post)
        {
            qDebug() << post.size();
            for(int counter = 0; counter < post.size(); ++counter){ gen->addLineTable(post.at(counter)); }

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
        requester->getActivePost([this](QList<Post> post)
        {
            qDebug() << post.size();
            for(int counter = 0; counter < post.size(); ++counter){ gen->addLineTable(post.at(counter)); }

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
