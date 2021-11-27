#include "WindowClientReg.h"

WindowClientReg::WindowClientReg() : layout(new QVBoxLayout()), layoutButs(new QHBoxLayout()), containerButs(new QWidget()), butReg(new QPushButton("Регистрация")), firstName(new QLineEdit()), lastName(new QLineEdit()), patronymic(new QLineEdit()), passportSeries(new QLineEdit()), passportNumber(new QLineEdit()), money(new QLineEdit()), login(new QLineEdit()), password(new QLineEdit()), requester(new NetworkAPIRequester("http://localhost/")), passportSeriesValidator(new QIntValidator(0, 9999)), passportNumberValidator(new QIntValidator(0, 999999)), textValidator(new QRegExpValidator(QRegExp("^[A-zА-я]+$"))), passwordValidator(new QRegExpValidator(QRegExp("^[A-z0-9]+$")))
{
    setTitle("Регистрация клиента");

    layout->setAlignment(Qt::AlignHCenter);
    layoutButs->setAlignment(Qt::AlignHCenter);

    firstName->setPlaceholderText("Имя");
    lastName->setPlaceholderText("Фамилия");
    patronymic->setPlaceholderText("Отчество");
    passportSeries->setPlaceholderText("Серия паспорта");
    passportNumber->setPlaceholderText("Номер паспорта");
    money->setPlaceholderText("Денеги");
    login->setPlaceholderText("Логин");
    password->setPlaceholderText("Пароль");

    firstName->setMaximumWidth(300);
    lastName->setMaximumWidth(300);
    patronymic->setMaximumWidth(300);
    passportSeries->setMaximumWidth(300);
    passportNumber->setMaximumWidth(300);
    money->setMaximumWidth(300);
    login->setMaximumWidth(300);
    password->setMaximumWidth(300);

    firstName->setMaxLength(30);
    lastName->setMaxLength(30);
    patronymic->setMaxLength(30);
    passportSeries->setMaxLength(4);
    passportNumber->setMaxLength(6);
    login->setMaxLength(30);
    password->setMaxLength(30);

    firstName->setValidator(textValidator);
    lastName->setValidator(textValidator);
    patronymic->setValidator(textValidator);
    login->setValidator(passwordValidator);
    password->setValidator(passwordValidator);
    money->setValidator(passportNumberValidator);

    passportSeries->setValidator(passportSeriesValidator);
    passportNumber->setValidator(passportNumberValidator);

    containerButs->setMaximumHeight(50);

    password->setEchoMode(QLineEdit::EchoMode::Password);

    containerButs->setLayout(layoutButs);

    layoutButs->addWidget(butReg);

    layout->addWidget(firstName);
    layout->addWidget(lastName);
    layout->addWidget(patronymic);
    layout->addWidget(passportSeries);
    layout->addWidget(passportNumber);
    layout->addWidget(money);
    layout->addWidget(login);
    layout->addWidget(password);
    layout->addWidget(containerButs);

    setLayout(layout);

    connect(butReg, SIGNAL(clicked()), this, SLOT(clickButReg()));
}

WindowClientReg::~WindowClientReg()
{
    if(passportSeriesValidator){ delete passportSeriesValidator; }
    if(passportNumberValidator){ delete passportNumberValidator; }
    if(textValidator){ delete textValidator; }
    if(passwordValidator){ delete passwordValidator; }

    if(firstName){ delete firstName; }
    if(lastName){ delete lastName; }
    if(patronymic){ delete patronymic; }
    if(passportSeries){ delete passportSeries; }
    if(passportNumber){ delete passportNumber; }
    if(money){ delete money; }
    if(login){ delete login; }
    if(password){ delete password; }

    if(butReg){ delete butReg; }

    if(layoutButs){ delete layoutButs; }

    if(containerButs){ delete containerButs; }

    if(layout){ delete layout; }

    if(requester){ delete requester; }
}

void WindowClientReg::clickButReg()
{
    if(firstName->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Имя не должено быть пустым!");
        return;
    }

    if(lastName->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Фамилия не должена быть пустой!");
        return;
    }

    if(passportSeries->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Серия паспорта не должена быть пустой!");
        return;
    }

    if(passportNumber->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Номер паспорта не должен быть пустым!");
        return;
    }

    if(passportSeries->text().length() < 4)
    {
        QMessageBox::critical(this, "Ошибка", "Серия паспорта не должена быть меньше 4 цифр!");
        return;
    }

    if(passportNumber->text().length() < 6)
    {
        QMessageBox::critical(this, "Ошибка", "Номер паспорта не должен быть меньше 6 цифр!");
        return;
    }

    if(money->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Деньги не должены быть пустыми!");
        return;
    }

    if(login->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Логин не должен быть пустым!");
        return;
    }

    if(password->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Пароль не должен быть пустым!");
        return;
    }

    if(password->text().length() < 8)
    {
        QMessageBox::critical(this, "Ошибка", "Пароль не должен быть менее 8 символов!");
        return;
    }

    requester->addAccounts([this](unsigned int id)
    {

        requester->addClient([this](unsigned int id)
        {
            QMessageBox::about(this, "Успех", "Клиент успешно зарегистрирован!");
        }, [this](unsigned int errorCode, QString error, QString replyServer)
        {
            QMessageBox::critical(this, "Ошибка", replyServer);
        }, Client(0, firstName->text(), lastName->text(), patronymic->text(), passportSeries->text().toInt(), passportNumber->text().toInt(), id, money->text().toInt(), false));

    },[this](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(this, "Ошибка", replyServer);
        qDebug() << QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex().size();
    }, Accounts(0, login->text(), QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex(), false));
}
