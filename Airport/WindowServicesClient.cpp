#include "WindowServicesClient.h"

WindowServicesClient::WindowServicesClient(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"))), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
{
    setLayout(layout);

    container->setLayout(layoutContaner);

    layoutContaner->addWidget(search);
    layoutContaner->addWidget(butSearch);
    layoutContaner->addWidget(butRefresh);
    layoutContaner->addWidget(butGenerateTable);

    search->setPlaceholderText("Название");
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

WindowServicesClient::~WindowServicesClient()
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

void WindowServicesClient::onClickSearch()
{
    if(search->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Поле поиска по наименованию не должно быть пустым!");
        return;
    }

    table->clear();

    requester->searchServices([this](Services services)
    {
        table->setRowCount(1);
        table->setColumnCount(5);

				table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена"});

        if(services.getId() == 0){ return; }

        table->setItem(0, 0, new QTableWidgetItem(QString::number(services.getId())));
        table->setItem(0, 1, new QTableWidgetItem(services.getName()));
        table->setItem(0, 2, new QTableWidgetItem(services.getDescription()));
        table->setItem(0, 3, new QTableWidgetItem(QString::number(services.getPrice())));
        table->setItem(0, 4, new QTableWidgetItem((((services.getIsDeleted() == 1)? "Да" : "Нет"))));

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Services(0, search->text(), "", 0, false));
}

void WindowServicesClient::refreshTable()
{
    table->clear();

        requester->getActiveServices([this](QList<Services> services)
        {

            table->setRowCount(services.size());
            table->setColumnCount(5);

						table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена"});

            for(int counter = 0; counter < services.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(services.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(services.at(counter).getName()));
                table->setItem(counter, 2, new QTableWidgetItem(services.at(counter).getDescription()));
                table->setItem(counter, 3, new QTableWidgetItem(QString::number(services.at(counter).getPrice())));
                table->setItem(counter, 4, new QTableWidgetItem((((services.at(counter).getIsDeleted() == 1)? "Да" : "Нет"))));
            }

        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });

    table->setHorizontalHeaderLabels(QStringList{"Id", "Имя", "Описание", "Цена"});
}

void WindowServicesClient::onClickRefresh(){ refreshTable(); }

void WindowServicesClient::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Имя", "Описание", "Цена", "Логически удалено ли"});

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
