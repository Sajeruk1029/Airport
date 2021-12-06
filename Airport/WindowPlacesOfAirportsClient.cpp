#include "WindowPlacesOfAirportsClient.h"

WindowPlacesOfAirportsClient::WindowPlacesOfAirportsClient(QString host) : layout(new QVBoxLayout()), layoutContaner(new QHBoxLayout()), container(new QWidget()), search(new QLineEdit()), butSearch(new QPushButton("Поиск")), butRefresh(new QPushButton("Обновить")), butGenerateTable(new QPushButton("Отчет")), table(new QTableWidget()), validator(new QRegExpValidator(QRegExp("^[A-zА-я0-9 ]+$"))), requester(new NetworkAPIRequester(host)), gen(nullptr), Host(host)
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

    refreshTable();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома"});

    connect(butSearch, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(butRefresh, SIGNAL(clicked()), this, SLOT(onClickRefresh()));
    connect(butGenerateTable, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));
}

WindowPlacesOfAirportsClient::~WindowPlacesOfAirportsClient()
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

void WindowPlacesOfAirportsClient::onClickSearch()
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

    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома"});

    requester->searchPlacesOfAirports([this](PlacesOfAirports placesOfAirports)
    {
        table->setRowCount(1);
        table->setColumnCount(5);

        if(placesOfAirports.getId() == 0){ return; }

        qDebug() << placesOfAirports.getId();

        table->setItem(0, 0, new QTableWidgetItem(QString::number(placesOfAirports.getId())));
        table->setItem(0, 1, new QTableWidgetItem(placesOfAirports.getCountry()));
        table->setItem(0, 2, new QTableWidgetItem(placesOfAirports.getCity()));
        table->setItem(0, 3, new QTableWidgetItem(placesOfAirports.getStreet()));
        table->setItem(0, 4, new QTableWidgetItem(QString::number(placesOfAirports.getHouseNumber())));

        }, [this](unsigned int errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, PlacesOfAirports(0, search->text().split(' ').at(0), search->text().split(' ').at(1), search->text().split(' ').at(2), 0, false));
}

void WindowPlacesOfAirportsClient::refreshTable()
{
    table->clear();

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома"});

        requester->getActivePlacesOfAirports([this](QList<PlacesOfAirports> placesOfAirports)
        {

            table->setRowCount(placesOfAirports.size());
            table->setColumnCount(5);

            for(int counter = 0; counter < placesOfAirports.size(); ++counter)
            {
                table->setItem(counter, 0, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getId())));
                table->setItem(counter, 1, new QTableWidgetItem(placesOfAirports.at(counter).getCountry()));
                table->setItem(counter, 2, new QTableWidgetItem(placesOfAirports.at(counter).getCity()));
                table->setItem(counter, 3, new QTableWidgetItem(placesOfAirports.at(counter).getStreet()));
                table->setItem(counter, 4, new QTableWidgetItem(QString::number(placesOfAirports.at(counter).getHouseNumber())));

            }
        }, [this](unsigned char errorCode, QString errorLine, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        });

    table->setHorizontalHeaderLabels(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома"});
}

void WindowPlacesOfAirportsClient::onClickRefresh(){ refreshTable(); }

void WindowPlacesOfAirportsClient::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Сохранение отчета...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    gen->createHTMLFile(5);

    gen->addCaptionTable(QStringList{"Id", "Страна", "Город", "Улица", "Номер дома", "Логически удалено ли", "", "", ""});

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
