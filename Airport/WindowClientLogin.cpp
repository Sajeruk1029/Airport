#include "WindowClientLogin.h"

WindowClientLogin::WindowClientLogin(QString host) : layout(new QVBoxLayout()), layoutButs(new QHBoxLayout()), containerButs(new QWidget()), butReg(new QPushButton("Регистрация")), butLogin(new QPushButton("Вход")), login(new QLineEdit()), password(new QLineEdit()), requester(new NetworkAPIRequester(host)), windowControlPanelClient(nullptr), windowClientReg(nullptr), Host(host)
{
    setTitle("Вход клиента");

    layout->setAlignment(Qt::AlignHCenter);
    layoutButs->setAlignment(Qt::AlignHCenter);

    login->setPlaceholderText("Логин");
    password->setPlaceholderText("Пароль");

    login->setMaximumWidth(200);
    password->setMaximumWidth(200);

    login->setMaxLength(30);
    password->setMaxLength(30);

    containerButs->setMaximumHeight(50);

    password->setEchoMode(QLineEdit::EchoMode::Password);

    containerButs->setLayout(layoutButs);

    layoutButs->addWidget(butLogin);
    layoutButs->addWidget(butReg);

    layout->addWidget(login);
    layout->addWidget(password);
    layout->addWidget(containerButs);

    setLayout(layout);

    connect(butLogin, SIGNAL(clicked()), this, SLOT(clickButLogin()));
    connect(butReg, SIGNAL(clicked()), this, SLOT(clickButReg()));
}

WindowClientLogin::~WindowClientLogin()
{
    if(login){ delete login; }
    if(password){ delete password; }

    if(butLogin){ delete butLogin; }
    if(butReg){ delete butReg; }

    if(layoutButs){ delete layoutButs; }

    if(containerButs){ delete containerButs; }

    if(layout){ delete layout; }

    if(requester){ delete requester; }

    if(windowControlPanelClient){ delete windowControlPanelClient; }
    if(windowClientReg){ delete windowClientReg; }
}

void WindowClientLogin::clickButLogin()
{
    requester->searchByLoginClientFull([this](ClientFull clientFull)
    {
        if((clientFull.getClientId() == 0) || (clientFull.getClientIsDeleted() == true))
        {
            QMessageBox::critical(this, "Ошибка", "Нет такого аккаунта!");
        }
        else
        {
            if(clientFull.getAccountPassword() == QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex())
            {
                QMessageBox::about(this, "Успех", "Вход успешен!");

                windowControlPanelClient = new WindowControlPanelClient(clientFull, Host);
                windowControlPanelClient->show();
                this->close();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Нет такого аккаунта!");
            }
        }
    }, [this](unsigned int codeError, QString errorLine, QString serverReply)
    {
        QMessageBox::critical(this, "Error", serverReply);
    }, ClientFull(0, "", "", "", 0, 0, login->text(), "", 0, false));

    //QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1)).length();
}

void WindowClientLogin::clickButReg()
{
    windowClientReg = new WindowClientReg(Host);
    windowClientReg->show();
    this->close();
}

