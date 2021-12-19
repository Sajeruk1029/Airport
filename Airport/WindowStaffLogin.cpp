#include "WindowStaffLogin.h"

WindowStaffLogin::WindowStaffLogin(QString host) : layout(new QVBoxLayout()), layoutButs(new QHBoxLayout()), containerButs(new QWidget()), butReg(new QPushButton("Регистрация")), butLogin(new QPushButton("Вход")), login(new QLineEdit()), password(new QLineEdit()), requester(new NetworkAPIRequester(host)), windowStaffReg(nullptr), windowControlPanelStaff(nullptr), Host(host)
{
    setTitle("Вход сотрудника");

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

WindowStaffLogin::~WindowStaffLogin()
{
    if(login){ delete login; }
    if(password){ delete password; }

    if(butLogin){ delete butLogin; }
    if(butReg){ delete butReg; }

    if(layoutButs){ delete layoutButs; }

    if(containerButs){ delete containerButs; }

    if(layout){ delete layout; }

    if(requester){ delete requester; }

    if(windowStaffReg){ delete windowStaffReg; }

    if(windowControlPanelStaff){ delete windowControlPanelStaff; }
}

void WindowStaffLogin::clickButLogin()
{
    requester->searchByLoginStaffFull([this](StaffFull staffFull)
    {
        if((staffFull.getStaffId() == 0) || (staffFull.getStaffIsDeleted() == true))
        {
            QMessageBox::critical(this, "Ошибка", "Нет такого аккаунта!");
        }
        else
        {
            if(staffFull.getAccountPassword() == QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex())
            {
                QMessageBox::about(this, "Успех", "Вход успешен!");

                windowControlPanelStaff = new WindowControlPanelStaff(staffFull, Host);
                windowControlPanelStaff->show();
                this->close();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Нет такого аккаунта!");
            }
        }
    }, [this](unsigned int codeError, QString errorLine, QString serverReply)
    {
				if(codeError == QNetworkReply::HostNotFoundError)
				{
					QMessageBox::critical(this, "Ошибка", "Хост недоступен!");
				}
				else
				{
								QMessageBox::critical(this, "Ошибка", errorLine);
				}

				qDebug() << serverReply;

    }, StaffFull(0, "", "", "", "", 0, 0, 0, "", login->text(), "", ""));

    //QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1)).length();
}

void WindowStaffLogin::clickButReg()
{
    windowStaffReg = new WindowStaffReg(Host);
    windowStaffReg->show();
    this->close();
}
