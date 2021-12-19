#include "WindowProfile.h"

WindowProfile::WindowProfile(StaffFull staffFull, QString host) : layout(new QVBoxLayout()), contaynerLayout(new QGridLayout()), contayner(new QWidget()), lineHintFirstName(new QLabel("Имя")), lineHintLastName(new QLabel("Фамилия")), lineHintPatronymic(new QLabel("Отчество")), lineHintPostName(new QLabel("Должность")), lineHintPassportSeries(new QLabel("Серия паспорта")), lineHintPassportNumber(new QLabel("Номер паспорта")), lineHintEducation(new QLabel("Образование")), lineHintLogin(new QLabel("Логин")), lineHintMoney(nullptr), lineFirstName(new QLineEdit()), lineLastName(new QLineEdit()), linePatronymic(new QLineEdit()), linePostName(new QLineEdit()), linePassportSeries(new QLineEdit()), linePassportNumber(new QLineEdit()), lineEducation(new QLineEdit()), lineLogin(new QLineEdit()), lineMoney(nullptr), butEnterPassword(new QPushButton("Ввести пароль")), butSave(new QPushButton("Сохранить")), butGenerateHTML(new QPushButton("Экспорт")), butEnterPost(new QPushButton("Выбрать должность")), requster(new NetworkAPIRequester(host)), gen(nullptr), validator(new QRegExpValidator(QRegExp("^[A-zА-я]+$"))), validatorPassportSeries(new QIntValidator(0, 9999)), validatorPassportNumber(new QIntValidator(0, 999999)), dataStaffFull(staffFull), dataClientFull(ClientFull()), staff(Staff(staffFull.getStaffId(), staffFull.getStaffFirstName(), staffFull.getStaffLastName(), staffFull.getStaffPatronymic(), 0, staffFull.getStaffPassportSeries(), staffFull.getStaffPassportNumber(), 0, staffFull.getStaffEducation(), staffFull.getStaffIsDeleted())), client(Client()), isStaff(true), Host(host)
{
    setLayout(layout);

    contayner->setLayout(contaynerLayout);

    contaynerLayout->addWidget(lineHintFirstName, 0, 0);
    contaynerLayout->addWidget(lineHintLastName, 1, 0);
    contaynerLayout->addWidget(lineHintPatronymic, 2, 0);
    contaynerLayout->addWidget(lineHintPostName, 3, 0);
    contaynerLayout->addWidget(butEnterPost, 4, 0);
    contaynerLayout->addWidget(lineHintPassportSeries, 5, 0);
    contaynerLayout->addWidget(lineHintPassportNumber, 6, 0);
    contaynerLayout->addWidget(lineHintEducation, 7, 0);
    contaynerLayout->addWidget(lineHintLogin, 8, 0);
    contaynerLayout->addWidget(butEnterPassword, 9, 0);
    contaynerLayout->addWidget(butGenerateHTML, 10, 0);
    contaynerLayout->addWidget(butSave, 11, 0);

    contaynerLayout->addWidget(lineFirstName, 0, 1);
    contaynerLayout->addWidget(lineLastName, 1, 1);
    contaynerLayout->addWidget(linePatronymic, 2, 1);
    contaynerLayout->addWidget(linePostName, 3, 1);
    contaynerLayout->addWidget(linePassportSeries, 5, 1);
    contaynerLayout->addWidget(linePassportNumber, 6, 1);
    contaynerLayout->addWidget(lineEducation, 7, 1);
    contaynerLayout->addWidget(lineLogin, 8, 1);

    lineFirstName->setPlaceholderText("Имя");
    lineLastName->setPlaceholderText("Фамилия");
    linePatronymic->setPlaceholderText("Отчество");
    linePostName->setPlaceholderText("Должность");
    linePassportSeries->setPlaceholderText("Серия паспорта");
    linePassportNumber->setPlaceholderText("Номер паспорта");
    lineEducation->setPlaceholderText("Образование");
    lineLogin->setPlaceholderText("Логин");

    linePostName->setReadOnly(true);

    lineFirstName->setValidator(validator);
    lineLastName->setValidator(validator);
    linePatronymic->setValidator(validator);
    linePostName->setValidator(validator);
    lineEducation->setValidator(validator);
    lineLogin->setValidator(validator);

    linePassportSeries->setValidator(validatorPassportSeries);
    linePassportNumber->setValidator(validatorPassportNumber);

    lineFirstName->setMaxLength(30);
    lineLastName->setMaxLength(30);
    linePatronymic->setMaxLength(30);
    linePostName->setMaxLength(30);
    lineEducation->setMaxLength(200);
    lineLogin->setMaxLength(30);

    linePassportNumber->setMaxLength(6);
    linePassportSeries->setMaxLength(4);

    layout->addWidget(contayner);

    lineFirstName->setText(dataStaffFull.getStaffFirstName());
    lineLastName->setText(dataStaffFull.getStaffLastName());
    linePatronymic->setText(dataStaffFull.getStaffPatronymic());
    linePostName->setText(dataStaffFull.getPostName());
    linePassportSeries->setText(QString::number(dataStaffFull.getStaffPassportSeries()));
    linePassportNumber->setText(QString::number(dataStaffFull.getStaffPassportNumber()));
    lineEducation->setText(dataStaffFull.getStaffEducation());
    lineLogin->setText(dataStaffFull.getAccountLogin());

    connect(butEnterPassword, SIGNAL(clicked()), this, SLOT(onClickEnterPassword()));
    connect(butEnterPost, SIGNAL(clicked()), this, SLOT(onClickEnterPost()));
    connect(butSave, SIGNAL(clicked()), this, SLOT(onClickSave()));
    connect(butGenerateHTML, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));

    requster->searchAccounts([this](Accounts accounts)
    {
        staff.setAccount(accounts.getId());
    }, [this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, Accounts(0, dataStaffFull.getAccountLogin(), "", false));

    requster->searchPost([this](Post post)
    {
        staff.setPost(post.getId());
    }, [this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, Post(0, dataStaffFull.getPostName(), 0, false));
}

WindowProfile::WindowProfile(ClientFull clientFull, QString host) : layout(new QVBoxLayout()), contaynerLayout(new QGridLayout()), contayner(new QWidget()), lineHintFirstName(new QLabel("Имя")), lineHintLastName(new QLabel("Фамилия")), lineHintPatronymic(new QLabel("Отчество")), lineHintPostName(nullptr), lineHintPassportSeries(new QLabel("Серия паспорта")), lineHintPassportNumber(new QLabel("Номер паспорта")), lineHintEducation(nullptr), lineHintLogin(new QLabel("Логин")), lineHintMoney(new QLabel("Количество денег")), lineFirstName(new QLineEdit()), lineLastName(new QLineEdit()), linePatronymic(new QLineEdit()), linePostName(nullptr), linePassportSeries(new QLineEdit()), linePassportNumber(new QLineEdit()), lineEducation(nullptr), lineLogin(new QLineEdit()), lineMoney(new QLineEdit()), butEnterPassword(new QPushButton("Ввести пароль")), butSave(new QPushButton("Сохранить")), butGenerateHTML(new QPushButton("Экспорт")), butEnterPost(new QPushButton(nullptr)), requster(new NetworkAPIRequester(host)), gen(nullptr), validator(new QRegExpValidator(QRegExp("^[A-zА-я]+$"))), validatorPassportSeries(new QIntValidator(0, 9999)), validatorPassportNumber(new QIntValidator(0, 999999)), dataStaffFull(StaffFull()), dataClientFull(clientFull), staff(Staff()), client(Client(clientFull.getClientId(), clientFull.getClientFirstName(), clientFull.getClientLastName(), clientFull.getClientPatronymic(), clientFull.getClientPassportSeries(), clientFull.getClientPassportNumber(), 0, clientFull.getClientMoney(), clientFull.getClientIsDeleted())), isStaff(false), Host(host)
{
    setLayout(layout);

    contayner->setLayout(contaynerLayout);

    contaynerLayout->addWidget(lineHintFirstName, 0, 0);
    contaynerLayout->addWidget(lineHintLastName, 1, 0);
    contaynerLayout->addWidget(lineHintPatronymic, 2, 0);
    contaynerLayout->addWidget(lineHintPassportSeries, 3, 0);
    contaynerLayout->addWidget(lineHintPassportNumber, 4, 0);
    contaynerLayout->addWidget(lineHintMoney, 5, 0);
    contaynerLayout->addWidget(lineHintLogin, 6, 0);
    contaynerLayout->addWidget(butEnterPassword, 7, 0);
    contaynerLayout->addWidget(butGenerateHTML, 18, 0);
    contaynerLayout->addWidget(butSave, 9, 0);

    contaynerLayout->addWidget(lineFirstName, 0, 1);
    contaynerLayout->addWidget(lineLastName, 1, 1);
    contaynerLayout->addWidget(linePatronymic, 2, 1);
    contaynerLayout->addWidget(linePassportSeries, 3, 1);
    contaynerLayout->addWidget(linePassportNumber, 4, 1);
    contaynerLayout->addWidget(lineMoney, 5, 1);
    contaynerLayout->addWidget(lineLogin, 6, 1);

    lineFirstName->setPlaceholderText("Имя");
    lineLastName->setPlaceholderText("Фамилия");
    linePatronymic->setPlaceholderText("Отчество");
    linePassportSeries->setPlaceholderText("Серия паспорта");
    linePassportNumber->setPlaceholderText("Номер паспорта");
    lineMoney->setPlaceholderText("Количество денег");
    lineLogin->setPlaceholderText("Логин");

    lineFirstName->setValidator(validator);
    lineLastName->setValidator(validator);
    linePatronymic->setValidator(validator);
    lineMoney->setValidator(validatorPassportNumber);
    lineLogin->setValidator(validator);

    linePassportSeries->setValidator(validatorPassportSeries);
    linePassportNumber->setValidator(validatorPassportNumber);

    lineFirstName->setMaxLength(30);
    lineLastName->setMaxLength(30);
    linePatronymic->setMaxLength(30);
    lineLogin->setMaxLength(30);
    lineMoney->setMaxLength(6);

    linePassportNumber->setMaxLength(6);
    linePassportSeries->setMaxLength(4);

    layout->addWidget(contayner);

    lineFirstName->setText(dataClientFull.getClientFirstName());
    lineLastName->setText(dataClientFull.getClientLastName());
    linePatronymic->setText(dataClientFull.getClientPatronymic());
    linePassportSeries->setText(QString::number(dataClientFull.getClientPassportSeries()));
    linePassportNumber->setText(QString::number(dataClientFull.getClientPassportNumber()));
    lineMoney->setText(QString::number(dataClientFull.getClientMoney()));
    lineLogin->setText(dataClientFull.getAccountLogin());

    connect(butEnterPassword, SIGNAL(clicked()), this, SLOT(onClickEnterPassword()));
    connect(butEnterPost, SIGNAL(clicked()), this, SLOT(onClickEnterPost()));
    connect(butSave, SIGNAL(clicked()), this, SLOT(onClickSave()));
    connect(butGenerateHTML, SIGNAL(clicked()), this, SLOT(onClickGeneratedHTML()));

    requster->searchAccounts([this](Accounts accounts)
    {
        client.setAccount(accounts.getId());
        qDebug() << accounts.getId();
    }, [this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
    }, Accounts(0, dataClientFull.getAccountLogin(), "", false));
}

WindowProfile::~WindowProfile()
{
    if(lineHintFirstName){ delete lineHintFirstName; }
    if(lineHintLastName){ delete lineHintLastName; }
    if(lineHintPatronymic){ delete lineHintPatronymic; }
    if(lineHintPostName){ delete lineHintPostName; }
    if(lineHintPassportSeries){ delete lineHintPassportSeries; }
    if(lineHintPassportNumber){ delete lineHintPassportNumber; }
    if(lineHintEducation){ delete lineHintEducation; }
    if(lineHintLogin){ delete lineHintLogin; }
    if(lineHintMoney){ delete lineHintMoney; }
    if(lineFirstName){ delete lineFirstName; }
    if(lineLastName){ delete lineLastName; }
    if(linePatronymic){ delete linePatronymic; }
    if(linePostName){ delete linePostName; }
    if(linePassportSeries){ delete linePassportSeries; }
    if(linePassportNumber){ delete linePassportNumber; }
    if(lineEducation){ delete lineEducation; }
    if(lineLogin){ delete lineLogin; }
    if(lineMoney){ delete lineMoney; }
    if(butEnterPassword){ delete butEnterPassword; }
    if(butSave){ delete butSave; }
    if(butGenerateHTML){ delete butGenerateHTML; }
    if(butEnterPost){ delete butEnterPost; }
    if(validator){ delete validator; }
    if(validatorPassportSeries){ delete validatorPassportSeries; }
    if(validatorPassportNumber){ delete validatorPassportNumber; }
    if(contaynerLayout){ delete contaynerLayout; }
    if(contayner){ delete contayner; }
    if(layout){ delete layout; }
    if(gen){ delete gen; }
    if(requster){ delete requster; }
}

void WindowProfile::onClickSave()
{
    if(isStaff)
    {
        if(lineFirstName->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Имя не должно быть пустым!");
            return;
        }

        if(lineLastName->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Фамилия не должна быть пустой!");
            return;
        }

        if(linePatronymic->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Отчество не должно быть пустым!");
            return;
        }

        if(linePassportSeries->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Серия паспорта не должна быть пустой!");
            return;
        }

        if(linePassportNumber->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Номер паспорта не должен быть пустым!");
            return;
        }

        if(lineEducation->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Образование не должно быть пустым!");
            return;
        }

        if(lineLogin->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Логин не должен быть пустым!");
            return;
        }

        staff.setFirstName(lineFirstName->text());
        staff.setLastName(lineLastName->text());
        staff.setPatronymic(linePatronymic->text());
        staff.setPassportSeries(linePassportSeries->text().toInt());
        staff.setPassportNumber(linePassportNumber->text().toInt());
        staff.setEducation(lineEducation->text());

        requster->setStaff([this](bool success)
        {
            QMessageBox::about(this, "Успех", "Данные сотрудника успешно изменены");

            linePostName->setText(dataStaffFull.getPostName());

            dataStaffFull.setStaffFirstName(staff.getFirstName());
            dataStaffFull.setStaffLastName(staff.getLastName());
            dataStaffFull.setStaffPatronymic(staff.getPatronymic());
            dataStaffFull.setStaffPassportSeries(staff.getPassportSeries());
            dataStaffFull.setStaffPassportNumber(staff.getPassportNumber());
            dataStaffFull.setStaffEducation(staff.getEducation());

        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, staff, staff);

        requster->setAccounts([this](bool success)
        {
            QMessageBox::about(this, "Успех", "Данные аккаунта успешно изменены");

            dataStaffFull.setAccountLogin(lineLogin->text());

        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Accounts(staff.getAccount(), "", "", false), Accounts(0, lineLogin->text(), dataStaffFull.getAccountPassword(), false));
    }
    else
    {
        if(lineFirstName->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Имя не должно быть пустым!");
            return;
        }

        if(lineLastName->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Фамилия не должна быть пустой!");
            return;
        }

        if(linePatronymic->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Отчество не должно быть пустым!");
            return;
        }

        if(linePassportSeries->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Серия паспорта не должна быть пустой!");
            return;
        }

        if(linePassportNumber->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Номер паспорта не должен быть пустым!");
            return;
        }

        if(lineMoney->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Количество денег не должно быть пустым!");
            return;
        }

        if(lineLogin->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка", "Логин не должен быть пустым!");
            return;
        }

        client.setFirstName(lineFirstName->text());
        client.setLastName(lineLastName->text());
        client.setPatronymic(linePatronymic->text());
        client.setPassportSeries(linePassportSeries->text().toInt());
        client.setPassportNumber(linePassportNumber->text().toInt());
        client.setMoney(lineMoney->text().toInt());

        requster->setClient([this](bool success)
        {
            QMessageBox::about(this, "Успех", "Данные клиента успешно изменены");

            dataClientFull.setClientFirstName(client.getFirstName());
            dataClientFull.setClientLastName(client.getLastName());
            dataClientFull.setClientPatronymic(client.getPatronymic());
            dataClientFull.setClientPassportSeries(client.getPassportSeries());
            dataClientFull.setClientPassportNumber(client.getPassportNumber());
            dataClientFull.setClientMoney(client.getMoney());

        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, client, client);

        requster->setAccounts([this](bool success)
        {
            QMessageBox::about(this, "Успех", "Данные аккаунта успешно изменены");

            dataClientFull.setAccountLogin(lineLogin->text());
        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Accounts(client.getAccount(), "", "", false), Accounts(0, lineLogin->text(), dataClientFull.getAccountPassword(), false));
    }
}

void WindowProfile::onClickEnterPassword()
{
    QString password = "";
    bool ok = false;

    password = CustomInputWidget::getPassword("Изменение пароля", ok, isStaff, this);

    if(!ok){ return; }

    if(isStaff)
    {
        dataStaffFull.setAccountPassword(static_cast<QString>(password));
    }
    else
    {
        dataClientFull.setAccountPassword(static_cast<QString>(password));
    }
}

void WindowProfile::onClickGeneratedHTML()
{
    QString path = "";

    path = QFileDialog::getSaveFileUrl(this, "Экспорт данных...", QDir::home().path(), "HTML (*.html)").path();

    if(path.isEmpty()){ return; }

    gen = new HTMLGenerator(path);

    if(isStaff)
    {
        gen->createHTMLFile(12);
        gen->addCaptionTable(QStringList{"Id", "Имя", "Фамилия", "Отчество", "Наименование должности", "Зарплата", "Серия паспорта", "Номер паспорта", "Образование", "Логин", "Пароль", "Логически удален ли"});
        gen->addLineTable(dataStaffFull);
    }
    else
    {
        gen->createHTMLFile(10);
        gen->addCaptionTable(QStringList{"Id", "Имя", "Фамилия", "Отчество", "Серия паспорта", "Номер паспорта", "Логин", "Пароль", "Количество денег", "Логически удален ли"});
        gen->addLineTable(dataClientFull);
    }

    gen->saveHTMLFile();

		QMessageBox::about(this, "Успех", "Отчет успешно создан!");

    delete gen;
    gen = nullptr;
}

void WindowProfile::onClickEnterPost()
{
    Post post;
    bool ok = false;

    post = CustomInputWidget::getPost("Изменение должности", ok, Host, this);

    if(!ok){ return; }

    dataStaffFull.setPostName(post.getName());
    staff.setPost(post.getId());
}
