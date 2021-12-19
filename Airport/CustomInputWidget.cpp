#include "CustomInputWidget.h"

CustomInputWidget::CustomInputWidget(){}

Accounts CustomInputWidget::getAccounts(QString title, bool staff, bool &ok, QWidget *parent)
{
    Accounts account(0, "", "", false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *login = nullptr;
    QLineEdit *password = nullptr;

    QValidator *validator = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-z0-9]+$"));

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    login = new QLineEdit();
    password = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    login->setPlaceholderText("Логин");
    password->setPlaceholderText("Пароль");

    login->setMaxLength(30);
    password->setMaxLength(30);

    password->setEchoMode(QLineEdit::EchoMode::Password);

    login->setValidator(validator);
    password->setValidator(validator);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(login);
    layout->addWidget(password);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&account, &login, &password, &staff, &dialog, &parent, &ok]()
            {
                if(login->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                    return;
                }

                if(password->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                    return;
                }

                if(password->text().size() < 8)
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                    return;
                }

                account.setLogin(login->text());

                account.setPassword((staff)? (QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex()) : QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&account, &login, &password, &staff, &dialog, &parent, &ok]()
            {
                if(login->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                    return;
                }

                if(password->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                    return;
                }

                if(password->text().size() < 8)
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                    return;
                }

                account.setLogin(login->text());

                account.setPassword((staff)? (QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex()) : QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete login;
    delete password;

    delete layout;

    delete dialog;

    delete validator;

    return account;
}
QString CustomInputWidget::getPassword(QString title, bool &ok, bool staff, QWidget *parent)
{
    QString password = "";

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *passwordLine = nullptr;

    QValidator *validator = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-z0-9]+$"));

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    passwordLine = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    passwordLine->setPlaceholderText("Пароль");

    passwordLine->setMaxLength(30);

    passwordLine->setEchoMode(QLineEdit::EchoMode::Password);

    passwordLine->setValidator(validator);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(passwordLine);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&password, &passwordLine, &staff, &dialog, &parent, &ok]()
            {
                if(passwordLine->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                    return;
                }

                if(passwordLine->text().size() < 8)
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                    return;
                }

                password = ((staff)? (QCryptographicHash::hash(passwordLine->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex()) : QCryptographicHash::hash(passwordLine->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&password, &passwordLine, &staff, &dialog, &parent, &ok]()
            {
                if(passwordLine->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                    return;
                }

                if(passwordLine->text().size() < 8)
                {
                    QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                    return;
                }

                password = ((staff)? (QCryptographicHash::hash(passwordLine->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex()) : QCryptographicHash::hash(passwordLine->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete passwordLine;

    delete layout;

    delete dialog;

    delete validator;

    return password;
}
AirCompany CustomInputWidget::getAirCompany(QString title, bool &ok, QWidget *parent)
{
    AirCompany airCompany(0, "", false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;

    QValidator *validator = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");

    name->setMaxLength(50);

    name->setValidator(validator);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&airCompany, &name, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должно быть пустым!");
                    return;
                }

                airCompany.setName(name->text());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&airCompany, &name, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должен быть пустым!");
                    return;
                }

                airCompany.setName(name->text());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;

    delete layout;

    delete dialog;

    delete validator;

    return airCompany;
}
AirCompanyAndAirplane CustomInputWidget::getAirCompanyAndAirplane(QString title, bool &ok, QString url, QWidget *parent)
{
    AirCompanyAndAirplane airCompanyAndAirplane(0, 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QComboBox *airCompany = nullptr;
    QComboBox *airplane = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    airCompany = new QComboBox();
    airplane = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    airCompany->setPlaceholderText("Авиакомпания");
    airplane->setPlaceholderText("Самолет");

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(airCompany);
    layout->addWidget(airplane);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveAirCompany([&parent, &title, &airCompany](QList<AirCompany> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            airCompany->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveAirplane([&parent, &title, &airplane](QList<Airplane> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            airplane->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&airCompanyAndAirplane, &airCompany, &airplane, &dialog, &parent, &ok]()
            {
                if(airCompany->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Авиакомпания должна быть выбрана!");
                    return;
                }

                if(airplane->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Самолет должен быть выбран!");
                    return;
                }

                airCompanyAndAirplane.setIdAirCompany(airCompany->currentData().toInt());
                airCompanyAndAirplane.setIdAirplane(airplane->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&airCompanyAndAirplane, &airCompany, &airplane, &dialog, &parent, &ok]()
            {
            if(airCompany->count() == 0)
            {
                QMessageBox::critical(parent, "Ошибка", "Авиакомпания должна быть выбрана!");
                return;
            }

            if(airplane->count() == 0)
            {
                QMessageBox::critical(parent, "Ошибка", "Самолет должен быть выбран!");
                return;
            }

            airCompanyAndAirplane.setIdAirCompany(airCompany->currentData().toInt());
            airCompanyAndAirplane.setIdAirplane(airplane->currentData().toInt());


                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete airCompany;
    delete airplane;

    delete layout;

    delete dialog;

    return airCompanyAndAirplane;
}
AirCompanyAndServices CustomInputWidget::getAirCompanyAndServices(QString title, bool &ok, QString url, QWidget *parent)
{
    AirCompanyAndServices airCompanyAndService(0, 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QComboBox *airCompany = nullptr;
    QComboBox *service = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    airCompany = new QComboBox();
    service = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    airCompany->setPlaceholderText("Авиакомпания");
    service->setPlaceholderText("Услуга");

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(airCompany);
    layout->addWidget(service);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveAirCompany([&parent, &title, &airCompany](QList<AirCompany> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            airCompany->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveServices([&parent, &title, &service](QList<Services> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            service->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&airCompanyAndService, &airCompany, &service, &dialog, &parent, &ok]()
            {
                if(airCompany->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Авиакомпания должна быть выбрана!");
                    return;
                }

                if(service->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Услуга Должна быть выбрана!");
                    return;
                }

                airCompanyAndService.setIdAirCompany(airCompany->currentData().toInt());
                airCompanyAndService.setIdService(service->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&airCompanyAndService, &airCompany, &service, &dialog, &parent, &ok]()
            {
            if(airCompany->count() == 0)
            {
                QMessageBox::critical(parent, "Ошибка", "Авиакомпания должна быть выбрана!");
                return;
            }

            if(service->count() == 0)
            {
                QMessageBox::critical(parent, "Ошибка", "Услуга Должна быть выбрана!");
                return;
            }

            airCompanyAndService.setIdAirCompany(airCompany->currentData().toInt());
            airCompanyAndService.setIdService(service->currentData().toInt());


                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete airCompany;
    delete service;

    delete layout;

    delete dialog;

    return airCompanyAndService;
}
Airplane CustomInputWidget::getAirplane(QString title, bool &ok, QWidget *parent)
{
    Airplane airplane(0, "", "", 0, 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;
    QLineEdit *description = nullptr;
    QLineEdit *maxSizeCargo = nullptr;
    QLineEdit *maxWeightCargo = nullptr;
    QLineEdit *maxSeatPlaces = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();
    description = new QLineEdit();
    maxSizeCargo = new QLineEdit();
    maxWeightCargo = new QLineEdit();
    maxSeatPlaces = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");
    description->setPlaceholderText("Описание");
    maxSizeCargo->setPlaceholderText("Максимальный размер груза");
    maxWeightCargo->setPlaceholderText("Максимальный вес груза");
    maxSeatPlaces->setPlaceholderText("Количество сидячих мест");

    name->setMaxLength(30);
    description->setMaxLength(100);

    name->setValidator(validator);
    description->setValidator(validator);

    maxSizeCargo->setValidator(validatorNumbers);
    maxWeightCargo->setValidator(validatorNumbers);
    maxSeatPlaces->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);
    layout->addWidget(description);
    layout->addWidget(maxSizeCargo);
    layout->addWidget(maxWeightCargo);
    layout->addWidget(maxSeatPlaces);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&airplane, &name, &description, &maxSizeCargo, &maxWeightCargo, &maxSeatPlaces, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(maxSizeCargo->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Максимальный размер груза не должен быть пустым!");
                    return;
                }

                if(maxWeightCargo->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Максиманый вес груза не должен быть пустым!");
                    return;
                }

                if(maxSeatPlaces->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Количество сидячих мест не должено быть пустым!");
                    return;
                }

                airplane.setName(name->text());
                airplane.setDescription(description->text());
                airplane.setMaxSizeCargo(maxSizeCargo->text().toInt());
                airplane.setMaxWeightCargo(maxWeightCargo->text().toInt());
                airplane.setMaxSeatPlaces(maxSeatPlaces->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&airplane, &name, &description, &maxSizeCargo, &maxWeightCargo, &maxSeatPlaces, &dialog, &parent, &ok]()
            {
            if(name->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                return;
            }

            if(description->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                return;
            }

            if(maxSizeCargo->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Максимальный размер груза не должен быть пустым!");
                return;
            }

            if(maxWeightCargo->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Максиманый вес груза не должен быть пустым!");
                return;
            }

            if(maxSeatPlaces->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Количество сидячих мест не должено быть пустым!");
                return;
            }

            airplane.setName(name->text());
            airplane.setDescription(description->text());
            airplane.setMaxSizeCargo(maxSizeCargo->text().toInt());
            airplane.setMaxWeightCargo(maxWeightCargo->text().toInt());
            airplane.setMaxSeatPlaces(maxSeatPlaces->text().toInt());

            dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;
    delete description;
    delete maxSizeCargo;
    delete maxWeightCargo;
    delete maxSeatPlaces;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    return airplane;
}
Baggage CustomInputWidget::getBaggage(QString title, bool &ok, QWidget *parent)
{
    Baggage baggage(0, "", "", 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;
    QLineEdit *description = nullptr;
    QLineEdit *size = nullptr;
    QLineEdit *weight = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();
    description = new QLineEdit();
    size = new QLineEdit();
    weight = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");
    description->setPlaceholderText("Описание");
    size->setPlaceholderText("Размер багажа");
    weight->setPlaceholderText("Вес багажа");

    name->setMaxLength(30);
    description->setMaxLength(100);

    description->setMinimumHeight(200);

    name->setValidator(validator);
    description->setValidator(validator);

    size->setValidator(validatorNumbers);
    weight->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);
    layout->addWidget(description);
    layout->addWidget(size);
    layout->addWidget(weight);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&baggage, &name, &description, &size, &weight, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(size->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Размер груза не должен быть пустым!");
                    return;
                }

                if(weight->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                    return;
                }

                baggage.setName(name->text());
                baggage.setDescription(description->text());
                baggage.setSize(size->text().toInt());
                baggage.setWeight(weight->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&baggage, &name, &description, &size, &weight, &dialog, &parent, &ok]()
            {
            if(name->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                return;
            }

            if(description->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                return;
            }

            if(size->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Размер багажа не должен быть пустым!");
                return;
            }

            if(weight->text().isEmpty())
            {
                QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                return;
            }

            baggage.setName(name->text());
            baggage.setDescription(description->text());
            baggage.setSize(size->text().toInt());
            baggage.setWeight(weight->text().toInt());

            dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;
    delete description;
    delete size;
    delete weight;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    return baggage;
}
CargoAndTickets CustomInputWidget::getCargoAndTickets(QString title, bool &ok, QString url, QWidget *parent)
{
    Cargo cargo(0, 0, 0, "", 0, 0, false);
    Tickets tickets(0, 0, 0, 0, 0, false, 0, false);
    CargoAndTickets cargoAndTickets;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *description = nullptr;
    QLineEdit *size = nullptr;
    QLineEdit *weight = nullptr;

    QComboBox *category = nullptr;
    //QComboBox *tickets = nullptr;
    QComboBox *client = nullptr;
    QComboBox *flights = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    description = new QLineEdit();
    size = new QLineEdit();
    weight = new QLineEdit();

    category = new QComboBox();
    client = new QComboBox();
    flights = new QComboBox();
    //tickets = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    category->setPlaceholderText("Категория груза");
    description->setPlaceholderText("Описание");
    size->setPlaceholderText("Размер груза");
    weight->setPlaceholderText("Вес груза");
    //tickets->setPlaceholderText("Id билета");
    client->setPlaceholderText("Id клиента");
    flights->setPlaceholderText("Id рейса");

    description->setMaxLength(100);

    description->setValidator(validator);

    size->setValidator(validatorNumbers);
    weight->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(category);
    layout->addWidget(description);
    layout->addWidget(size);
    layout->addWidget(weight);
    //layout->addWidget(tickets);
    layout->addWidget(client);
    layout->addWidget(flights);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveCategoriesCargo([&parent, &title, &category](QList<CategoriesCargo> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            category->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

//    requester->getActiveTickets([&parent, &title, &tickets](QList<Tickets> list)
//    {
//        for(int counter = 0; counter < list.size(); ++counter)
//        {
//            tickets->addItem(QString::number(list.at(counter).getId()), list.at(counter).getId());
//        }

//    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
//    {
//        QMessageBox::critical(parent, title, replyServer);
//    });

    requester->getActiveClient([&parent, &title, &client](QList<Client> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            client->addItem(list.at(counter).getFirstName().append(" ").append(list.at(counter).getLastName()).append(" ").append(list.at(counter).getPatronymic()), list.at(counter).getId());
        }

        client->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveFlights([&parent, &title, &flights](QList<Flights> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            flights->addItem(list.at(counter).getDepartureDate().toString("yyyy-MM-dd hh:mm:ss").append(" ").append(list.at(counter).getArrivalPoint()), list.at(counter).getId());
        }

        flights->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&cargo, &tickets, &cargoAndTickets, &category, &description, &size, &weight, &client, &flights, &dialog, &parent, &ok]()
            {
                if(category->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Категория Должна быть выбрана!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(size->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Размер груза не должен быть пустым!");
                    return;
                }

                if(weight->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                    return;
                }

//                if(tickets->count() == 0)
//                {
//                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
//                    return;
//                }

                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                cargo.setIdCategory(category->currentData().toInt());
                cargo.setDescription(description->text());
                cargo.setSize(size->text().toInt());
                cargo.setWeight(weight->text().toInt());
                cargo.setIdTicket(0);

                tickets.setPrice(tickets.getPrice() + cargo.getSize() * 1.5);
                tickets.setPrice(tickets.getPrice() + cargo.getWeight() * 1.5);
                tickets.setBaggageAvailable(false);
                tickets.setId(0);
                tickets.setFlights(flights->currentData().toInt());
                tickets.setIdClient(client->currentData().toInt());
                tickets.setSeatNumber(0);
                tickets.setIsDeleted(false);

                cargoAndTickets.cargo = cargo;
                cargoAndTickets.tickets = tickets;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&cargo, &tickets, &cargoAndTickets, &category, &description, &size, &weight, &client, &flights, &dialog, &parent, &ok]()
            {
                if(category->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Категория Должна быть выбрана!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(size->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Размер груза не должен быть пустым!");
                    return;
                }

                if(weight->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                    return;
                }

//                if(tickets->count() == 0)
//                {
//                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
//                    return;
//                }

                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                cargo.setIdCategory(category->currentData().toInt());
                cargo.setDescription(description->text());
                cargo.setSize(size->text().toInt());
                cargo.setWeight(weight->text().toInt());
                cargo.setIdTicket(0);

                tickets.setPrice(tickets.getPrice() + cargo.getSize() * 1.5);
                tickets.setPrice(tickets.getPrice() + cargo.getWeight() * 1.5);
                tickets.setBaggageAvailable(false);
                tickets.setId(0);
                tickets.setFlights(flights->currentData().toInt());
                tickets.setIdClient(client->currentData().toInt());
                tickets.setSeatNumber(0);
                tickets.setIsDeleted(false);

                cargoAndTickets.cargo = cargo;
                cargoAndTickets.tickets = tickets;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete description;
    delete size;
    delete weight;
    delete category;
    //delete tickets;
    delete flights;
    delete client;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    delete requester;

    return cargoAndTickets;
}
CargoAndTickets CustomInputWidget::getCargoAndTickets(QString title, bool &ok, QString url, unsigned int idClient, QWidget *parent)
{
    Cargo cargo(0, 0, 0, "", 0, 0, false);
    Tickets tickets(0, 0, idClient, 0, 0, false, 0, false);
    CargoAndTickets cargoAndTickets;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *description = nullptr;
    QLineEdit *size = nullptr;
    QLineEdit *weight = nullptr;

    QComboBox *category = nullptr;
    //QComboBox *tickets = nullptr;
    QComboBox *flights = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    description = new QLineEdit();
    size = new QLineEdit();
    weight = new QLineEdit();

    category = new QComboBox();
    flights = new QComboBox();
    //tickets = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    category->setPlaceholderText("Категория груза");
    description->setPlaceholderText("Описание");
    size->setPlaceholderText("Размер груза");
    weight->setPlaceholderText("Вес груза");
    //tickets->setPlaceholderText("Id билета");
    flights->setPlaceholderText("Id рейса");

    description->setMaxLength(100);

    description->setValidator(validator);

    size->setValidator(validatorNumbers);
    weight->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(category);
    layout->addWidget(description);
    layout->addWidget(size);
    layout->addWidget(weight);
    //layout->addWidget(tickets);
    layout->addWidget(flights);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveCategoriesCargo([&parent, &title, &category](QList<CategoriesCargo> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            category->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

//    requester->getActiveTickets([&parent, &title, &tickets](QList<Tickets> list)
//    {
//        for(int counter = 0; counter < list.size(); ++counter)
//        {
//            tickets->addItem(QString::number(list.at(counter).getId()), list.at(counter).getId());
//        }

//    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
//    {
//        QMessageBox::critical(parent, title, replyServer);
//    });

    requester->getActiveFlights([&parent, &title, &flights](QList<Flights> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            flights->addItem(list.at(counter).getDepartureDate().toString("yyyy-MM-dd hh:mm:ss").append(" ").append(list.at(counter).getArrivalPoint()), list.at(counter).getId());
        }

        flights->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&cargo, &tickets, &cargoAndTickets, &category, &description, &size, &weight, &flights, &dialog, &parent, &ok]()
            {
                if(category->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Категория Должна быть выбрана!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(size->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Размер груза не должен быть пустым!");
                    return;
                }

                if(weight->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                    return;
                }

//                if(tickets->count() == 0)
//                {
//                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
//                    return;
//                }


                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                cargo.setIdCategory(category->currentData().toInt());
                cargo.setDescription(description->text());
                cargo.setSize(size->text().toInt());
                cargo.setWeight(weight->text().toInt());
                cargo.setIdTicket(0);

                tickets.setPrice(tickets.getPrice() + cargo.getSize() * 1.5);
                tickets.setPrice(tickets.getPrice() + cargo.getWeight() * 1.5);
                tickets.setBaggageAvailable(false);
                tickets.setId(0);
                tickets.setFlights(flights->currentData().toInt());
                tickets.setSeatNumber(0);
                tickets.setIsDeleted(false);

                cargoAndTickets.cargo = cargo;
                cargoAndTickets.tickets = tickets;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&cargo, &tickets, &cargoAndTickets, &category, &description, &size, &weight, &flights, &dialog, &parent, &ok]()
            {
                if(category->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Категория Должна быть выбрана!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(size->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Размер груза не должен быть пустым!");
                    return;
                }

                if(weight->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Вес багажа не должен быть пустым!");
                    return;
                }

//                if(tickets->count() == 0)
//                {
//                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
//                    return;
//                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                cargo.setIdCategory(category->currentData().toInt());
                cargo.setDescription(description->text());
                cargo.setSize(size->text().toInt());
                cargo.setWeight(weight->text().toInt());
                cargo.setIdTicket(0);

                tickets.setPrice(tickets.getPrice() + cargo.getSize() * 1.5);
                tickets.setPrice(tickets.getPrice() + cargo.getWeight() * 1.5);
                tickets.setBaggageAvailable(false);
                tickets.setId(0);
                tickets.setFlights(flights->currentData().toInt());
                tickets.setSeatNumber(0);
                tickets.setIsDeleted(false);

                cargoAndTickets.cargo = cargo;
                cargoAndTickets.tickets = tickets;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete description;
    delete size;
    delete weight;
    delete category;
    //delete tickets;
    delete flights;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    delete requester;

    return cargoAndTickets;
}
CategoriesCargo CustomInputWidget::getCategoriesCargo(QString title, bool &ok, QWidget *parent)
{
    CategoriesCargo categoriesCargo(0, "", "", false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;
    QLineEdit *description = nullptr;

    QValidator *validator = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-z0-9]+$"));

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();
    description = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");
    description->setPlaceholderText("Описание");

    name->setMaxLength(30);
    description->setMaxLength(100);

    name->setValidator(validator);
    description->setValidator(validator);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);
    layout->addWidget(description);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&categoriesCargo, &name, &description, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                categoriesCargo.setName(name->text());
                categoriesCargo.setDescription(description->text());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&categoriesCargo, &name, &description, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                categoriesCargo.setName(name->text());
                categoriesCargo.setDescription(description->text());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;
    delete description;

    delete layout;

    delete dialog;

    delete validator;

    return categoriesCargo;
}
ClientAndAccounts CustomInputWidget::getClientAndAccounts(QString title, bool &ok, bool withAccount, QWidget *parent)
{
    Client client(0, "", "", "", 0, 0, 0, 0, false);
    Accounts accounts(0, "", "", false);
    ClientAndAccounts clientAndAccounts;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *firstName = nullptr;
    QLineEdit *lastName = nullptr;
    QLineEdit *patronymic = nullptr;
    QLineEdit *passportSeries = nullptr;
    QLineEdit *passportNumber = nullptr;
    QLineEdit *login = nullptr;
    QLineEdit *password = nullptr;
    QLineEdit *money = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorFLP = nullptr;
    QValidator *validatorSeriesPassport = nullptr;
    QValidator *validatorNumberPassport = nullptr;
    QValidator *validatorMoney = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    if(withAccount)
    {
        validator = new QRegExpValidator(QRegExp("^[A-z0-9]+$"));
    }

    validatorFLP = new QRegExpValidator(QRegExp("^[А-я]+$"));
    validatorSeriesPassport = new QIntValidator(0, 9999);
    validatorNumberPassport = new QIntValidator(0, 999999);
    validatorMoney = new QIntValidator(0, 9999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    firstName = new QLineEdit();
    lastName = new QLineEdit();
    patronymic = new QLineEdit();
    passportSeries = new QLineEdit();
    passportNumber = new QLineEdit();

    if(withAccount)
    {
        login = new QLineEdit();
        password = new QLineEdit();
    }

    money = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    firstName->setPlaceholderText("Имя");
    lastName->setPlaceholderText("Фамилия");
    patronymic->setPlaceholderText("Отчество");
    passportSeries->setPlaceholderText("Серия паспорта");
    passportNumber->setPlaceholderText("Номер паспорта");

    if(withAccount)
    {
        login->setPlaceholderText("Логин");
        password->setPlaceholderText("Пароль");
    }

    money->setPlaceholderText("Количество денег");

    firstName->setMaxLength(30);
    lastName->setMaxLength(30);
    patronymic->setMaxLength(30);
    passportSeries->setMaxLength(4);
    passportNumber->setMaxLength(6);

    if(withAccount)
    {
        login->setMaxLength(30);
        password->setMaxLength(30);
    }

    if(withAccount)
    {
        password->setEchoMode(QLineEdit::EchoMode::Password);
    }

    firstName->setValidator(validatorFLP);
    lastName->setValidator(validatorFLP);
    patronymic->setValidator(validatorFLP);
    passportSeries->setValidator(validatorSeriesPassport);
    passportNumber->setValidator(validatorNumberPassport);

    if(withAccount)
    {
        login->setValidator(validator);
        password->setValidator(validator);
    }

    money->setValidator(validatorMoney);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(firstName);
    layout->addWidget(lastName);
    layout->addWidget(patronymic);
    layout->addWidget(passportSeries);
    layout->addWidget(passportNumber);

    if(withAccount)
    {
        layout->addWidget(login);
        layout->addWidget(password);
    }

    layout->addWidget(money);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&client, &withAccount, &firstName, &lastName, &patronymic, &passportSeries, &passportNumber, &login, &password, &money, &accounts, &clientAndAccounts, &dialog, &parent, &ok]()
            {
                if(firstName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Имя не должено быть пустым!");
                    return;
                }

                if(lastName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Фамилия не Должна быть пустой!");
                    return;
                }

                if(patronymic->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Отчество не должено быть пустым!");
                    return;
                }

                if(passportSeries->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Серия паспорта не Должна быть пустой!");
                    return;
                }

                if(passportNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер паспорта не должен быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    if(login->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                        return;
                    }

                    if(password->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                        return;
                    }

                    if(password->text().size() < 8)
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                        return;
                    }
                }

                if(money->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Количество денег не должено быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    accounts.setLogin(login->text());
                    accounts.setPassword(QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());
                }

                client.setFirstName(firstName->text());
                client.setLastName(lastName->text());
                client.setPatronymic(patronymic->text());
                client.setPassportSeries(passportSeries->text().toInt());
                client.setPassportNumber(passportNumber->text().toInt());
                client.setAccount(0);
                client.setMoney(money->text().toInt());

                clientAndAccounts.accounts = accounts;
                clientAndAccounts.client = client;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&client, &withAccount, &firstName, &lastName, &patronymic, &passportSeries, &passportNumber, &login, &password, &money, &accounts, &clientAndAccounts, &dialog, &parent, &ok]()
            {
                if(firstName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Имя не должено быть пустым!");
                    return;
                }

                if(lastName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Фамилия не Должна быть пустой!");
                    return;
                }

                if(patronymic->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Отчество не должено быть пустым!");
                    return;
                }

                if(passportSeries->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Серия паспорта не Должна быть пустой!");
                    return;
                }

                if(passportNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер паспорта не должен быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    if(login->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                        return;
                    }

                    if(password->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                        return;
                    }

                    if(password->text().size() < 8)
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                        return;
                    }
                }

                if(money->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Количество денег не должено быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    accounts.setLogin(login->text());
                    accounts.setPassword(QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordClient", QCryptographicHash::Sha1).toHex()).toHex());
                }

                client.setFirstName(firstName->text());
                client.setLastName(lastName->text());
                client.setPatronymic(patronymic->text());
                client.setPassportSeries(passportSeries->text().toInt());
                client.setPassportNumber(passportNumber->text().toInt());
                client.setAccount(0);
                client.setMoney(money->text().toInt());

                clientAndAccounts.accounts = accounts;
                clientAndAccounts.client = client;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete firstName;
    delete lastName;
    delete patronymic;
    delete passportSeries;
    delete passportNumber;

    if(withAccount)
    {
        delete login;
        delete password;
    }

    delete money;

    delete layout;

    delete dialog;

    if(withAccount)
    {
        delete validator;
    }

    delete validatorFLP;
    delete validatorMoney;
    delete validatorNumberPassport;
    delete validatorSeriesPassport;

    return clientAndAccounts;
}
ClientAndBaggage CustomInputWidget::getClientAndBaggage(QString title, bool &ok, QString url, QWidget *parent)
{
    ClientAndBaggage clientAndBaggage(0, 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QComboBox *client = nullptr;
    QComboBox *baggage = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    client = new QComboBox();
    baggage = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    client->setPlaceholderText("Клиент");
    baggage->setPlaceholderText("Багаж");

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(client);
    layout->addWidget(baggage);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveClient([&parent, &title, &client](QList<Client> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            client->addItem(list.at(counter).getFirstName().append(" ").append(list.at(counter).getLastName()).append(" ").append(list.at(counter).getLastName()), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveBaggage([&parent, &title, &baggage](QList<Baggage> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            baggage->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&clientAndBaggage, &client, &baggage, &dialog, &parent, &ok]()
            {
                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Клиент должн быть выбран!");
                    return;
                }

                if(baggage->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                    return;
                }

                clientAndBaggage.setIdClient(client->currentData().toInt());
                clientAndBaggage.setIdBaggage(baggage->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&clientAndBaggage, &client, &baggage, &dialog, &parent, &ok]()
            {
                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Клиент должн быть выбран!");
                    return;
                }

                if(baggage->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                    return;
                }

                clientAndBaggage.setIdClient(client->currentData().toInt());
                clientAndBaggage.setIdBaggage(baggage->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete client;
    delete baggage;

    delete layout;

    delete dialog;

    return clientAndBaggage;
}
Flights CustomInputWidget::getFlights(QString title, bool &ok, QString url, QWidget *parent)
{
    Flights flights(0, QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss"), QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss"), 0, 0, 0, 9, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QDateTimeEdit *arrivalDate = nullptr;
    QDateTimeEdit *departureDate = nullptr;

    QLineEdit *ladder = nullptr;

    QComboBox *arrivalPoint;
    QComboBox *departurePoint;
    QComboBox *airplane;

    QValidator *validator = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    validator = new QIntValidator(0, 9999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    ladder = new QLineEdit();

    arrivalPoint = new QComboBox();
    departurePoint = new QComboBox();
    airplane = new QComboBox();

    arrivalDate = new QDateTimeEdit();
    departureDate = new QDateTimeEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    arrivalPoint->setPlaceholderText("Точка отбытия");
    departurePoint->setPlaceholderText("Точка прития");
    ladder->setPlaceholderText("Номер трапа");

    ladder->setValidator(validator);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(arrivalDate);
    layout->addWidget(departureDate);
    layout->addWidget(departurePoint);
    layout->addWidget(arrivalPoint);
    layout->addWidget(airplane);
    layout->addWidget(ladder);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActivePlacesOfAirports([&parent, &title, &departurePoint, &arrivalPoint](QList<PlacesOfAirports> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            departurePoint->addItem(list.at(counter).getCountry().append(" ").append(list.at(counter).getCity()).append(" ").append(list.at(counter).getStreet()), list.at(counter).getId());
            arrivalPoint->addItem(list.at(counter).getCountry().append(" ").append(list.at(counter).getCity()).append(" ").append(list.at(counter).getStreet()), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveAirplane([&parent, &title, &airplane](QList<Airplane> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            airplane->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&flights, &arrivalDate, &departureDate, &departurePoint, &arrivalPoint, &airplane, &ladder, &dialog, &parent, &ok]()
            {
                if(departurePoint->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия должна быть выбрана!");
                    return;
                }

                if(arrivalPoint->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия должна быть выбрана!");
                    return;
                }

                if(arrivalPoint->currentIndex() == departurePoint->currentIndex())
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия не должна быть такая же, как точка прибытия!");
                    return;
                }

                if(airplane->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Самолет должен быть выбран!");
                    return;
                }

                if(ladder->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Трап не должен быть пустым!");
                    return;
                }

                flights.setArrivalDate(arrivalDate->dateTime());
                flights.setDepartureDate(departureDate->dateTime());
                flights.setDeparturePoint(departurePoint->currentData().toInt());
                flights.setArrivalPoint(arrivalPoint->currentData().toInt());
                flights.setAirplane(airplane->currentData().toInt());
                flights.setLadder(ladder->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&flights, &arrivalDate, &departureDate, &departurePoint, &arrivalPoint, &airplane, &ladder, &dialog, &parent, &ok]()
            {
                if(departurePoint->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия должна быть выбрана!");
                    return;
                }

                if(arrivalPoint->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия должна быть выбрана!");
                    return;
                }

                if(arrivalPoint->currentIndex() == departurePoint->currentIndex())
                {
                    QMessageBox::critical(parent, "Ошибка", "Точка отбытия не должна быть такая же, как точка прибытия!");
                    return;
                }

                if(airplane->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Самолет должен быть выбран!");
                    return;
                }

                if(ladder->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Трап не должен быть пустым!");
                    return;
                }

                flights.setArrivalDate(arrivalDate->dateTime());
                flights.setDepartureDate(departureDate->dateTime());
                flights.setDeparturePoint(departurePoint->currentData().toInt());
                flights.setArrivalPoint(arrivalPoint->currentData().toInt());
                flights.setAirplane(airplane->currentData().toInt());
                flights.setLadder(ladder->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete arrivalDate;
    delete departureDate;
    delete departurePoint;
    delete arrivalPoint;
    delete airplane;
    delete ladder;

    delete layout;

    delete dialog;

    delete validator;

    delete requester;

    return flights;
}
PlacesOfAirports CustomInputWidget::getPlacesOfAirport(QString title, bool &ok, QWidget *parent)
{
    PlacesOfAirports placesOfAirports(0, "", "", "", 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *country = nullptr;
    QLineEdit *city = nullptr;
    QLineEdit *street = nullptr;
    QLineEdit *numberHouse = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    country = new QLineEdit();
    city = new QLineEdit();
    street = new QLineEdit();
    numberHouse = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    country->setPlaceholderText("Страна");
    city->setPlaceholderText("Город");
    street->setPlaceholderText("Улица");
    numberHouse->setPlaceholderText("Номер дома");

    country->setMaxLength(50);
    city->setMaxLength(50);
    street->setMaxLength(50);

    country->setValidator(validator);
    city->setValidator(validator);
    street->setValidator(validator);

    numberHouse->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(country);
    layout->addWidget(city);
    layout->addWidget(street);
    layout->addWidget(numberHouse);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&placesOfAirports, &country, &city, &street, &numberHouse, &dialog, &parent, &ok]()
            {
                if(country->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Страна не должена быть пустой!");
                    return;
                }

                if(city->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Город не должен быть пустым!");
                    return;
                }

                if(street->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Улица не должена быть пустой!");
                    return;
                }

                if(numberHouse->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер дома не должен быть пустым!");
                    return;
                }

                placesOfAirports.setCountry(country->text());
                placesOfAirports.setCity(city->text());
                placesOfAirports.setStreet(street->text());
                placesOfAirports.setHouseNumber(numberHouse->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&placesOfAirports, &country, &city, &street, &numberHouse, &dialog, &parent, &ok]()
            {
                if(country->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Страна не должена быть пустой!");
                    return;
                }

                if(city->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Город не должен быть пустым!");
                    return;
                }

                if(street->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Улица не должена быть пустой!");
                    return;
                }

                if(numberHouse->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер дома не должен быть пустым!");
                    return;
                }

                placesOfAirports.setCountry(country->text());
                placesOfAirports.setCity(city->text());
                placesOfAirports.setStreet(street->text());
                placesOfAirports.setHouseNumber(numberHouse->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete country;
    delete city;
    delete street;
    delete numberHouse;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    return placesOfAirports;
}
Post CustomInputWidget::getPost(QString title, bool &ok, QWidget *parent)
{
    Post post(0, "", 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;
    QLineEdit *salary = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorSalary = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я]+$"));
    validatorSalary = new QIntValidator(0, 9999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();
    salary = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");
    salary->setPlaceholderText("Зарплата");

    name->setMaxLength(30);

    name->setValidator(validator);
    salary->setValidator(validatorSalary);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);
    layout->addWidget(salary);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&post, &name, &salary, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должно быть пустым!");
                    return;
                }

                if(salary->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Зарплата не должна быть пустой!");
                    return;
                }

                post.setName(name->text());
                post.setSalary(salary->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&post, &name, &salary, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должно быть пустым!");
                    return;
                }

                if(salary->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Зарплата не должна быть пустой!");
                    return;
                }

                post.setName(name->text());
                post.setSalary(salary->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;
    delete salary;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorSalary;

    return post;
}
Post CustomInputWidget::getPost(QString title, bool &ok, QString url, QWidget *parent)
{
    Post post(0, "", 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QComboBox *postList = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    postList = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    postList->setPlaceholderText("Наименование");

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(postList);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    requester = new NetworkAPIRequester(url);

    requester->getActivePost([&postList](QList<Post> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            postList->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

        postList->setCurrentIndex(0);
    }, [&parent](unsigned int errorCode, QString error, QString replyServer)
    {
       QMessageBox::critical(parent, "Ошибка", replyServer);
    });

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&post, &postList, &dialog, &parent, &ok]()
            {
                if(postList->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Должность должна быть выбрана!ы");
                    return;
                }

                post.setId(postList->currentData().toInt());
                post.setName(postList->currentText());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&post, &postList, &dialog, &parent, &ok]()
            {
                if(postList->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Должность должна быть выбрана!");
                    return;
                }

                post.setId(postList->currentData().toInt());
                post.setName(postList->currentText());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete postList;

    delete layout;

    delete dialog;

    return post;
}
Services CustomInputWidget::getServices(QString title, bool &ok, QWidget *parent)
{
    Services services(0, "", "", 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *name = nullptr;
    QLineEdit *description = nullptr;
    QLineEdit *price = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    name = new QLineEdit();
    description = new QLineEdit();
    price = new QLineEdit();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    name->setPlaceholderText("Наименование");
    description->setPlaceholderText("Описание");
    price->setPlaceholderText("Цена");

    name->setMaxLength(30);
    description->setMaxLength(100);

    name->setValidator(validator);
    description->setValidator(validator);

    price->setValidator(validatorNumbers);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(name);
    layout->addWidget(description);
    layout->addWidget(price);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&services, &name, &description, &price, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(price->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Цена не должена быть пустой!");
                    return;
                }

                services.setName(name->text());
                services.setDescription(description->text());
                services.setPrice(price->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&services, &name, &description, &price, &dialog, &parent, &ok]()
            {
                if(name->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Наименование не должено быть пустым!");
                    return;
                }

                if(description->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                    return;
                }

                if(price->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Цена не должена быть пустой!");
                    return;
                }

                services.setName(name->text());
                services.setDescription(description->text());
                services.setPrice(price->text().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete name;
    delete description;
    delete price;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    return services;
}
StaffAndAccounts CustomInputWidget::getStaffAndAccounts(QString title, bool &ok, QString url, bool withAccount, QWidget *parent)
{
    Accounts accounts(0, "", "", false);
    Staff staff(0, "", "", "", 0, 0, 0, 0, "", false);
    StaffAndAccounts staffAndAccounts;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QLineEdit *firstName = nullptr;
    QLineEdit *lastName = nullptr;
    QLineEdit *patronymic = nullptr;
    QLineEdit *passportSeries = nullptr;
    QLineEdit *passportNumber = nullptr;
    QLineEdit *login = nullptr;
    QLineEdit *password = nullptr;
    QLineEdit *education = nullptr;

    QComboBox *post = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorFLP = nullptr;
    QValidator *validatorSeriesPassport = nullptr;
    QValidator *validatorNumberPassport = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester;

    if(withAccount)
    {
        validator = new QRegExpValidator(QRegExp("^[A-z0-9]+$"));
    }

    validatorFLP = new QRegExpValidator(QRegExp("^[А-я]+$"));
    validatorSeriesPassport = new QIntValidator(0, 9999);
    validatorNumberPassport = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    firstName = new QLineEdit();
    lastName = new QLineEdit();
    patronymic = new QLineEdit();
    passportSeries = new QLineEdit();
    passportNumber = new QLineEdit();

    if(withAccount)
    {
        login = new QLineEdit();
        password = new QLineEdit();
    }

    education = new QLineEdit();

    education->setMinimumHeight(200);

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    firstName->setPlaceholderText("Имя");
    lastName->setPlaceholderText("Фамилия");
    patronymic->setPlaceholderText("Отчество");
    passportSeries->setPlaceholderText("Серия паспорта");
    passportNumber->setPlaceholderText("Номер паспорта");

    if(withAccount)
    {
        login->setPlaceholderText("Логин");
        password->setPlaceholderText("Пароль");
    }

    education->setPlaceholderText("Образование");

    firstName->setMaxLength(30);
    lastName->setMaxLength(30);
    patronymic->setMaxLength(30);
    education->setMaxLength(200);
    passportSeries->setMaxLength(4);
    passportNumber->setMaxLength(6);

    if(withAccount)
    {
        login->setMaxLength(30);
        password->setMaxLength(30);
    }


    if(withAccount)
    {
        password->setEchoMode(QLineEdit::EchoMode::Password);
    }

    firstName->setValidator(validatorFLP);
    lastName->setValidator(validatorFLP);
    patronymic->setValidator(validatorFLP);
    passportSeries->setValidator(validatorSeriesPassport);
    passportNumber->setValidator(validatorNumberPassport);

    if(withAccount)
    {
        login->setValidator(validator);
        password->setValidator(validator);
    }

    education->setValidator(validatorFLP);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(firstName);
    layout->addWidget(lastName);
    layout->addWidget(patronymic);
    layout->addWidget(passportSeries);
    layout->addWidget(passportNumber);

    if(withAccount)
    {
        layout->addWidget(login);
        layout->addWidget(password);
    }

    layout->addWidget(education);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActivePost([&post](QList<Post> list)
    {

        for(int counter = 0; counter < list.size(); ++counter)
        {
            post->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    }, [&parent](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, "Ошибка", replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&staff, &withAccount, &firstName, &lastName, &patronymic, &post, &passportSeries, &passportNumber, &login, &password, &education, &accounts, &staffAndAccounts, &dialog, &parent, &ok]()
            {
                if(firstName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Имя не должено быть пустым!");
                    return;
                }

                if(lastName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Фамилия не Должна быть пустой!");
                    return;
                }

                if(patronymic->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Отчество не должено быть пустым!");
                    return;
                }

                if(post->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Должность должена быть выбрана!");
                    return;
                }

                if(passportSeries->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Серия паспорта не Должна быть пустой!");
                    return;
                }

                if(passportNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер паспорта не должен быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    if(login->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                        return;
                    }

                    if(password->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                        return;
                    }

                    if(password->text().size() < 8)
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                        return;
                    }
                }

                if(education->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Образование не должено быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    accounts.setLogin(login->text());
                    accounts.setPassword(QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex());
                }

                staff.setFirstName(firstName->text());
                staff.setLastName(lastName->text());
                staff.setPatronymic(patronymic->text());
                staff.setPassportSeries(passportSeries->text().toInt());
                staff.setPassportNumber(passportNumber->text().toInt());
                staff.setAccount(0);
                staff.setEducation(education->text());

                staffAndAccounts.accounts = accounts;
                staffAndAccounts.staff = staff;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&staff, &withAccount, &firstName, &lastName, &patronymic, &post, &passportSeries, &passportNumber, &login, &password, &education, &accounts, &staffAndAccounts, &dialog, &parent, &ok]()
            {
                if(firstName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Имя не должено быть пустым!");
                    return;
                }

                if(lastName->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Фамилия не Должна быть пустой!");
                    return;
                }

                if(patronymic->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Отчество не должено быть пустым!");
                    return;
                }

                if(post->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Должность должена быть выбрана!");
                    return;
                }

                if(passportSeries->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Серия паспорта не Должна быть пустой!");
                    return;
                }

                if(passportNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Номер паспорта не должен быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    if(login->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Логин не должен быть пустым!");
                        return;
                    }

                    if(password->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть пустым!");
                        return;
                    }

                    if(password->text().size() < 8)
                    {
                        QMessageBox::critical(parent, "Ошибка", "Пароль не должен быть менее 8 символов!");
                        return;
                    }
                }

                if(education->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Образование не должено быть пустым!");
                    return;
                }

                if(withAccount)
                {
                    accounts.setLogin(login->text());
                    accounts.setPassword(QCryptographicHash::hash(password->text().toUtf8(), QCryptographicHash::Sha1).toHex().append(QCryptographicHash::hash("passwordStaff", QCryptographicHash::Sha1).toHex()).toHex());
                }

                staff.setFirstName(firstName->text());
                staff.setLastName(lastName->text());
                staff.setPatronymic(patronymic->text());
                staff.setPassportSeries(passportSeries->text().toInt());
                staff.setPassportNumber(passportNumber->text().toInt());
                staff.setAccount(0);
                staff.setEducation(education->text());

                staffAndAccounts.accounts = accounts;
                staffAndAccounts.staff = staff;

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete firstName;
    delete lastName;
    delete patronymic;
    delete post;
    delete passportSeries;
    delete passportNumber;

    if(withAccount)
    {
        delete login;
        delete password;
    }

    delete education;

    delete layout;

    delete dialog;

    if(withAccount)
    {
        delete validator;
    }

    delete validatorFLP;
    delete validatorNumberPassport;
    delete validatorSeriesPassport;

    return staffAndAccounts;
}
BaggageAndTicketsAndServices CustomInputWidget::getBaggageAndTicketsAndServices(QString title, bool &ok, QString url, QWidget *parent)
{
    Tickets tickets(0, 0, 0, 0, 0, false, 0, false);
    Baggage baggage(0, "", "", 0, 0, false);
    QList<Services> services;
    BaggageAndTicketsAndServices baggageAndTicketsAndServices;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    //QLineEdit *price = nullptr;
    QLineEdit *seatNumber = nullptr;
    QLineEdit *baggageName = nullptr;
    QLineEdit *baggageDescription = nullptr;
    QLineEdit *baggageSize = nullptr;
    QLineEdit *baggageWeight = nullptr;

    QListWidget *listServices;

    QComboBox *client = nullptr;
    QComboBox *flights = nullptr;
    //QComboBox *baggage = nullptr;

    QCheckBox *baggageAvailable = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    //price = new QLineEdit();
    seatNumber = new QLineEdit();
    baggageName = new QLineEdit();
    baggageDescription = new QLineEdit();
    baggageSize = new QLineEdit();
    baggageWeight = new QLineEdit();

    listServices = new QListWidget();

    baggageAvailable = new QCheckBox("Есть багаж?");

    client = new QComboBox();
    flights = new QComboBox();
    //baggage = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    client->setPlaceholderText("Клиент");
    flights->setPlaceholderText("Рейс");
    //baggage->setPlaceholderText("Багаж");
    //price->setPlaceholderText("Цена");
    seatNumber->setPlaceholderText("Номер места");
    baggageName->setPlaceholderText("Имя багажа");
    baggageDescription->setPlaceholderText("Описание багажа");
    baggageSize->setPlaceholderText("Размер багажа");
    baggageWeight->setPlaceholderText("Вес багажа");

    baggageName->setValidator(validator);
    baggageDescription->setValidator(validator);

    baggageName->setMaxLength(30);
    baggageDescription->setMaxLength(100);

    seatNumber->setValidator(validatorNumbers);
    //price->setValidator(validatorNumbers);
    baggageSize->setValidator(validatorNumbers);
    baggageWeight->setValidator(validatorNumbers);

    baggageName->setVisible(false);
    baggageDescription->setVisible(false);
    baggageSize->setVisible(false);
    baggageWeight->setVisible(false);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    if(parent)
    {
        connect(baggageAvailable, &QCheckBox::stateChanged, parent, [&](int state)
        {
           baggageName->setVisible(baggageAvailable->checkState());
           baggageDescription->setVisible(baggageAvailable->checkState());
           baggageSize->setVisible(baggageAvailable->checkState());
           baggageWeight->setVisible(baggageAvailable->checkState());
           qDebug() << state;
        });
    }
    else
    {
        connect(baggageAvailable, &QCheckBox::stateChanged, [&](int state)
        {
           baggageName->setVisible(baggageAvailable->checkState());
           baggageDescription->setVisible(baggageAvailable->checkState());
           baggageSize->setVisible(baggageAvailable->checkState());
           baggageWeight->setVisible(baggageAvailable->checkState());
           qDebug() << state;
        });
    }

    //layout->addWidget(price);
    layout->addWidget(client);
    layout->addWidget(seatNumber);
    layout->addWidget(flights);
    layout->addWidget(baggageAvailable);
    //layout->addWidget(baggage);
    layout->addWidget(baggageName);
    layout->addWidget(baggageDescription);
    layout->addWidget(baggageSize);
    layout->addWidget(baggageWeight);
    layout->addWidget(listServices);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveClient([&parent, &title, &client](QList<Client> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            client->addItem(list.at(counter).getFirstName().append(" ").append(list.at(counter).getLastName()).append(" ").append(list.at(counter).getPatronymic()), list.at(counter).getId());
        }

        client->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveFlights([&parent, &title, &flights](QList<Flights> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            flights->addItem(list.at(counter).getDepartureDate().toString("yyyy-MM-dd hh:mm:ss").append(" ").append(list.at(counter).getArrivalPoint()), list.at(counter).getId());
        }

        flights->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    //requester->getActiveBaggage([&parent, &title, &baggage](QList<Baggage> list)
    //{
        //for(int counter = 0; counter < list.size(); ++counter)
        //{
            //baggage->addItem(list.at(counter).getName(), list.at(counter).getId());
        //}

    //},[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    //{
        //QMessageBox::critical(parent, title, replyServer);
    //});

    requester->getActiveServices([&parent, &title, &baggageAndTicketsAndServices, &listServices](QList<Services> list)
    {

        for(int counter = 0; counter < list.size(); ++counter)
        {
            listServices->addItem(new QListWidgetItem());

            listServices->item(counter)->setData(Qt::DisplayRole, list.at(counter).getName());
            listServices->item(counter)->setData(Qt::CheckStateRole, Qt::Unchecked);
            listServices->item(counter)->setWhatsThis(QString::number(list.at(counter).getId()).append(":").append(QString::number(list.at(counter).getPrice())));
        }


    }, [&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
       QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&tickets, &baggage, &baggageAndTicketsAndServices, &services, &client, &seatNumber, &flights, &baggageAvailable, &baggageName, &baggageDescription, &baggageSize, &baggageWeight, &listServices, &dialog, &parent, &ok]()
            {
                //if(price->text().isEmpty())
                //{
                    //QMessageBox::critical(parent, "Ошибка", "Цена не должна быть пустой!");
                    //return;
                //}

                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Клиент должен быть выбран!");
                    return;
                }

                if(seatNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Место не должено быть пустым!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Рейс должен быть выбран!");
                    return;
                }

                if(baggageAvailable->checkState() == Qt::CheckState::Checked)
                {
                    //if(baggage->count() == 0)
                    //{
                        //qDebug() << "DEBUG3: " << baggageAvailable->checkState();
                        //QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                        //return;
                    //}

                    if(baggageName->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Имя багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageDescription->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                        return;
                    }

                    if(baggageSize->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Размер багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageWeight->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Вес багажа не должено быть пустым!");
                        return;
                    }
                }

                for(int counter = 0; counter < listServices->count(); ++counter)
                {
                    if(listServices->item(counter))
                    {
                        services.append(Services(listServices->item(counter)->whatsThis().split(":")[0].toInt(), listServices->item(counter)->text(), "", listServices->item(counter)->whatsThis().split(":")[1].toInt(), false));
                        tickets.setPrice(tickets.getPrice() + listServices->item(counter)->whatsThis().split(":")[1].toInt());
                        //qDebug() << "D: " << tickets.getPrice(); 11
                    }
                }

                tickets.setIdClient(client->currentData().toInt());
                tickets.setSeatNumber(seatNumber->text().toInt());
                tickets.setFlights(flights->currentData().toInt());
                tickets.setBaggageAvailable((baggageAvailable->checkState()));

                if(baggageAvailable->checkState())
                {
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageSize->text().toInt() * 1.1 : 0));
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageWeight->text().toInt() * 1.1 : 0));

                    baggage.setName(baggageName->text());
                    baggage.setDescription(baggageDescription->text());
                    baggage.setSize(baggageSize->text().toInt());
                    baggage.setWeight(baggageName->text().toInt());
                }

                baggageAndTicketsAndServices.tickets = tickets;
                baggageAndTicketsAndServices.baggage = baggage;
                baggageAndTicketsAndServices.services = services;
                //tickets.setBaggage((baggageAvailable->checkState() == Qt::CheckState::Checked)? baggage->currentData().toInt() : 0);

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&tickets, &baggage, &baggageAndTicketsAndServices, &services, &client, &seatNumber, &flights, &baggageAvailable, &baggageName, &baggageDescription, &baggageSize, &baggageWeight, &listServices, &dialog, &parent, &ok]()
            {
                //if(price->text().isEmpty())
                //{
                    //QMessageBox::critical(parent, "Ошибка", "Цена не должна быть пустой!");
                    //return;
                //}

                if(client->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Клиент должен быть выбран!");
                    return;
                }

                if(seatNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Место не должено быть пустым!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Рейс должен быть выбран!");
                    return;
                }

                if(baggageAvailable->checkState() == Qt::CheckState::Checked)
                {
                    //if(baggage->count() == 0)
                    //{
                        //qDebug() << "DEBUG3: " << baggageAvailable->checkState();
                        //QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                        //return;
                    //}

                    if(baggageName->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Имя багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageDescription->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                        return;
                    }

                    if(baggageSize->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Размер багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageWeight->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Вес багажа не должено быть пустым!");
                        return;
                    }
                }

                for(int counter = 0; counter < listServices->count(); ++counter)
                {
                    if(listServices->item(counter))
                    {
                        services.append(Services(listServices->item(counter)->whatsThis().split(":")[0].toInt(), listServices->item(counter)->text(), "", listServices->item(counter)->whatsThis().split(":")[1].toInt(), false));
                        tickets.setPrice(tickets.getPrice() + listServices->item(counter)->whatsThis().split(":")[1].toInt());
                    }
                }

                tickets.setIdClient(client->currentData().toInt());
                tickets.setSeatNumber(seatNumber->text().toInt());
                tickets.setFlights(flights->currentData().toInt());
                tickets.setBaggageAvailable((baggageAvailable->checkState()));

                if(baggageAvailable->checkState())
                {
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageSize->text().toInt() * 1.1 : 0));
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageWeight->text().toInt() * 1.1 : 0));

                    baggage.setName(baggageName->text());
                    baggage.setDescription(baggageDescription->text());
                    baggage.setSize(baggageSize->text().toInt());
                    baggage.setWeight(baggageName->text().toInt());
                }

                baggageAndTicketsAndServices.tickets = tickets;
                baggageAndTicketsAndServices.baggage = baggage;
                baggageAndTicketsAndServices.services = services;
                //tickets.setBaggage((baggageAvailable->checkState() == Qt::CheckState::Checked)? baggage->currentData().toInt() : 0);

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    listServices->clear();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    //delete price;
    delete client;
    delete seatNumber;
    delete flights;
    delete baggageAvailable;
    delete baggageName;
    delete baggageDescription;
    delete baggageSize;
    delete baggageWeight;
    //delete baggage;

    delete listServices;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    delete requester;

    return baggageAndTicketsAndServices;
}
BaggageAndTicketsAndServices CustomInputWidget::getBaggageAndTicketsAndServices(QString title, bool &ok, QString url, unsigned int idClient, QWidget *parent)
{
    Tickets tickets(0, 0, idClient, 0, 0, false, 0, false);
    Baggage baggage(0, "", "", 0, 0, false);
    QList<Services> services;
    BaggageAndTicketsAndServices baggageAndTicketsAndServices;

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    //QLineEdit *price = nullptr;
    QLineEdit *seatNumber = nullptr;
    QLineEdit *baggageName = nullptr;
    QLineEdit *baggageDescription = nullptr;
    QLineEdit *baggageSize = nullptr;
    QLineEdit *baggageWeight = nullptr;

    QListWidget *listServices;

    QComboBox *flights = nullptr;
    //QComboBox *baggage = nullptr;

    QCheckBox *baggageAvailable = nullptr;

    QValidator *validator = nullptr;
    QValidator *validatorNumbers = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    validator = new QRegExpValidator(QRegExp("^[A-zА-я0-9]+$"));
    validatorNumbers = new QIntValidator(0, 999999);

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    //price = new QLineEdit();
    seatNumber = new QLineEdit();
    baggageName = new QLineEdit();
    baggageDescription = new QLineEdit();
    baggageSize = new QLineEdit();
    baggageWeight = new QLineEdit();

    listServices = new QListWidget();

    baggageAvailable = new QCheckBox("Есть багаж?");

    flights = new QComboBox();
    //baggage = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    flights->setPlaceholderText("Рейс");
    //baggage->setPlaceholderText("Багаж");
    //price->setPlaceholderText("Цена");
    seatNumber->setPlaceholderText("Номер места");
    baggageName->setPlaceholderText("Имя багажа");
    baggageDescription->setPlaceholderText("Описание багажа");
    baggageSize->setPlaceholderText("Размер багажа");
    baggageWeight->setPlaceholderText("Вес багажа");

    baggageName->setValidator(validator);
    baggageDescription->setValidator(validator);

    baggageName->setMaxLength(30);
    baggageDescription->setMaxLength(100);

    seatNumber->setValidator(validatorNumbers);
    //price->setValidator(validatorNumbers);
    baggageSize->setValidator(validatorNumbers);
    baggageWeight->setValidator(validatorNumbers);

    baggageName->setVisible(false);
    baggageDescription->setVisible(false);
    baggageSize->setVisible(false);
    baggageWeight->setVisible(false);

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    if(parent)
    {
        connect(baggageAvailable, &QCheckBox::stateChanged, parent, [&](int state)
        {
           baggageName->setVisible(baggageAvailable->checkState());
           baggageDescription->setVisible(baggageAvailable->checkState());
           baggageSize->setVisible(baggageAvailable->checkState());
           baggageWeight->setVisible(baggageAvailable->checkState());
           qDebug() << state;
        });
    }
    else
    {
        connect(baggageAvailable, &QCheckBox::stateChanged, [&](int state)
        {
           baggageName->setVisible(baggageAvailable->checkState());
           baggageDescription->setVisible(baggageAvailable->checkState());
           baggageSize->setVisible(baggageAvailable->checkState());
           baggageWeight->setVisible(baggageAvailable->checkState());
           qDebug() << state;
        });
    }

    //layout->addWidget(price);
    layout->addWidget(seatNumber);
    layout->addWidget(flights);
    layout->addWidget(baggageAvailable);
    //layout->addWidget(baggage);
    layout->addWidget(baggageName);
    layout->addWidget(baggageDescription);
    layout->addWidget(baggageSize);
    layout->addWidget(baggageWeight);
    layout->addWidget(listServices);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveFlights([&parent, &title, &flights](QList<Flights> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            flights->addItem(list.at(counter).getDepartureDate().toString("yyyy-MM-dd hh:mm:ss").append(" ").append(list.at(counter).getArrivalPoint()), list.at(counter).getId());
        }

        flights->setCurrentIndex(0);

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    //requester->getActiveBaggage([&parent, &title, &baggage](QList<Baggage> list)
    //{
        //for(int counter = 0; counter < list.size(); ++counter)
        //{
            //baggage->addItem(list.at(counter).getName(), list.at(counter).getId());
        //}

    //},[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    //{
        //QMessageBox::critical(parent, title, replyServer);
    //});

    requester->getActiveServices([&parent, &title, &baggageAndTicketsAndServices, &listServices](QList<Services> list)
    {

        for(int counter = 0; counter < list.size(); ++counter)
        {
            listServices->addItem(new QListWidgetItem());

            listServices->item(counter)->setData(Qt::DisplayRole, list.at(counter).getName());
            listServices->item(counter)->setData(Qt::CheckStateRole, Qt::Unchecked);
            listServices->item(counter)->setWhatsThis(QString::number(list.at(counter).getId()).append(":").append(QString::number(list.at(counter).getPrice())));
        }


    }, [&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
       QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&tickets, &baggage, &baggageAndTicketsAndServices, &services, &seatNumber, &flights, &baggageAvailable, &baggageName, &baggageDescription, &baggageSize, &baggageWeight, &listServices, &dialog, &parent, &ok]()
            {
                //if(price->text().isEmpty())
                //{
                    //QMessageBox::critical(parent, "Ошибка", "Цена не должна быть пустой!");
                    //return;
                //}

                if(seatNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Место не должено быть пустым!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Рейс должен быть выбран!");
                    return;
                }

                if(baggageAvailable->checkState() == Qt::CheckState::Checked)
                {
                    //if(baggage->count() == 0)
                    //{
                        //qDebug() << "DEBUG3: " << baggageAvailable->checkState();
                        //QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                        //return;
                    //}

                    if(baggageName->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Имя багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageDescription->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                        return;
                    }

                    if(baggageSize->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Размер багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageWeight->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Вес багажа не должено быть пустым!");
                        return;
                    }
                }

                for(int counter = 0; counter < listServices->count(); ++counter)
                {
                    if(listServices->item(counter))
                    {
                        services.append(Services(listServices->item(counter)->whatsThis().split(":")[0].toInt(), listServices->item(counter)->text(), "", listServices->item(counter)->whatsThis().split(":")[1].toInt(), false));
                        tickets.setPrice(tickets.getPrice() + listServices->item(counter)->whatsThis().split(":")[1].toInt());
                        //qDebug() << "D: " << tickets.getPrice(); 11
                    }
                }

                tickets.setSeatNumber(seatNumber->text().toInt());
                tickets.setFlights(flights->currentData().toInt());
                tickets.setBaggageAvailable((baggageAvailable->checkState()));

                if(baggageAvailable->checkState())
                {
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageSize->text().toInt() * 1.1 : 0));
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageWeight->text().toInt() * 1.1 : 0));

                    baggage.setName(baggageName->text());
                    baggage.setDescription(baggageDescription->text());
                    baggage.setSize(baggageSize->text().toInt());
                    baggage.setWeight(baggageName->text().toInt());
                }

                baggageAndTicketsAndServices.tickets = tickets;
                baggageAndTicketsAndServices.baggage = baggage;
                baggageAndTicketsAndServices.services = services;
                //tickets.setBaggage((baggageAvailable->checkState() == Qt::CheckState::Checked)? baggage->currentData().toInt() : 0);

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&tickets, &baggage, &baggageAndTicketsAndServices, &services, &seatNumber, &flights, &baggageAvailable, &baggageName, &baggageDescription, &baggageSize, &baggageWeight, &listServices, &dialog, &parent, &ok]()
            {
                //if(price->text().isEmpty())
                //{
                    //QMessageBox::critical(parent, "Ошибка", "Цена не должна быть пустой!");
                    //return;
                //}

                if(seatNumber->text().isEmpty())
                {
                    QMessageBox::critical(parent, "Ошибка", "Место не должено быть пустым!");
                    return;
                }

                if(flights->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Рейс должен быть выбран!");
                    return;
                }

                if(baggageAvailable->checkState() == Qt::CheckState::Checked)
                {
                    //if(baggage->count() == 0)
                    //{
                        //qDebug() << "DEBUG3: " << baggageAvailable->checkState();
                        //QMessageBox::critical(parent, "Ошибка", "Багаж должен быть выбран!");
                        //return;
                    //}

                    if(baggageName->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Имя багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageDescription->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Описание не должено быть пустым!");
                        return;
                    }

                    if(baggageSize->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Размер багажа не должено быть пустым!");
                        return;
                    }

                    if(baggageWeight->text().isEmpty())
                    {
                        QMessageBox::critical(parent, "Ошибка", "Вес багажа не должено быть пустым!");
                        return;
                    }
                }

                for(int counter = 0; counter < listServices->count(); ++counter)
                {
                    if(listServices->item(counter))
                    {
                        services.append(Services(listServices->item(counter)->whatsThis().split(":")[0].toInt(), listServices->item(counter)->text(), "", listServices->item(counter)->whatsThis().split(":")[1].toInt(), false));
                        tickets.setPrice(tickets.getPrice() + listServices->item(counter)->whatsThis().split(":")[1].toInt());
                    }
                }

                tickets.setSeatNumber(seatNumber->text().toInt());
                tickets.setFlights(flights->currentData().toInt());
                tickets.setBaggageAvailable((baggageAvailable->checkState()));

                if(baggageAvailable->checkState())
                {
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageSize->text().toInt() * 1.1 : 0));
                    tickets.setPrice(tickets.getPrice() + ((baggageAvailable->checkState())? baggageWeight->text().toInt() * 1.1 : 0));

                    baggage.setName(baggageName->text());
                    baggage.setDescription(baggageDescription->text());
                    baggage.setSize(baggageSize->text().toInt());
                    baggage.setWeight(baggageName->text().toInt());
                }

                baggageAndTicketsAndServices.tickets = tickets;
                baggageAndTicketsAndServices.baggage = baggage;
                baggageAndTicketsAndServices.services = services;
                //tickets.setBaggage((baggageAvailable->checkState() == Qt::CheckState::Checked)? baggage->currentData().toInt() : 0);

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    listServices->clear();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    //delete price;
    delete seatNumber;
    delete flights;
    delete baggageAvailable;
    delete baggageName;
    delete baggageDescription;
    delete baggageSize;
    delete baggageWeight;
    //delete baggage;

    delete listServices;

    delete layout;

    delete dialog;

    delete validator;
    delete validatorNumbers;

    delete requester;

    return baggageAndTicketsAndServices;
}
TicketsAndServices CustomInputWidget::getTicketsAndServices(QString title, bool &ok, QString url, QWidget *parent)
{
    TicketsAndServices ticketsAndServices(0, 0, 0, false);

    QDialog *dialog = nullptr;
    QWidget *contayner = nullptr;

    QComboBox *ticket = nullptr;
    QComboBox *service = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *layoutContayner = nullptr;

    QDialogButtonBox *dialogButtonBox = nullptr;

    QEventLoop *eventLoop = nullptr;

    NetworkAPIRequester *requester = nullptr;

    dialog = new QDialog();

    contayner = new QWidget();

    layout = new QVBoxLayout();
    layoutContayner = new QHBoxLayout();

    ticket = new QComboBox();
    service = new QComboBox();

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    ticket->setPlaceholderText("Билет");
    service->setPlaceholderText("Услуга");

    dialog->setWindowTitle(title);
    dialog->setModal(true);

    dialog->setLayout(layout);
    contayner->setLayout(layoutContayner);

    layout->addWidget(ticket);
    layout->addWidget(service);

    layoutContayner->addWidget(dialogButtonBox);

    layout->addWidget(contayner);

    dialog->show();

    eventLoop = new QEventLoop();

    requester = new NetworkAPIRequester(url);

    requester->getActiveTickets([&parent, &title, &ticket](QList<Tickets> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            ticket->addItem(QString::number(list.at(counter).getId()), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    requester->getActiveServices([&parent, &title, &service](QList<Services> list)
    {
        for(int counter = 0; counter < list.size(); ++counter)
        {
            service->addItem(list.at(counter).getName(), list.at(counter).getId());
        }

    },[&parent, &title](unsigned int errorCode, QString error, QString replyServer)
    {
        QMessageBox::critical(parent, title, replyServer);
    });

    if(parent)
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, parent, [&ticketsAndServices, &ticket, &service, &dialog, &parent, &ok]()
            {
                if(ticket->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должен быть выбран!");
                    return;
                }

                if(service->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Услуга должна быть выбрана!");
                    return;
                }

                ticketsAndServices.setIdTicket(ticket->currentData().toInt());
                ticketsAndServices.setIdService(service->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, parent, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }
    else
    {
        QObject::connect(dialogButtonBox, &QDialogButtonBox::accepted, [&ticketsAndServices, &ticket, &service, &dialog, &parent, &ok]()
            {
                if(ticket->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Билет должн быть выбран!");
                    return;
                }

                if(service->count() == 0)
                {
                    QMessageBox::critical(parent, "Ошибка", "Услуга должна быть выбрана!");
                    return;
                }

                ticketsAndServices.setIdTicket(ticket->currentData().toInt());
                ticketsAndServices.setIdService(service->currentData().toInt());

                dialog->close();

                ok = true;
            });

        QObject::connect(dialogButtonBox, &QDialogButtonBox::rejected, [&dialog, &ok]()
        {
            dialog->close();

            ok = false;
        });
    }

    connect(dialog, &QDialog::finished, eventLoop, &QEventLoop::quit);

    eventLoop->exec();

    delete dialogButtonBox;

    delete layoutContayner;

    delete contayner;

    delete ticket;
    delete service;

    delete layout;

    delete dialog;

    return ticketsAndServices;
}
