#include "WindowStartMenu.h"

WindowStartMenu::WindowStartMenu() : layout(new QVBoxLayout()), buttonClient(new QPushButton("Я - клиент.")), buttonStaff(new QPushButton("Я - сотрудник.")), windowStaffLogin(nullptr), windowClientLogin(nullptr)
{
    setTitle("Стартовое меню");

    layout->addWidget(buttonClient);
    layout->addWidget(buttonStaff);

    setLayout(layout);

    layout->setAlignment(Qt::AlignHCenter);

    connect(buttonClient, SIGNAL(clicked()), this, SLOT(clickButClient()));
    connect(buttonStaff, SIGNAL(clicked()), this, SLOT(clickButStaff()));
}

WindowStartMenu::~WindowStartMenu()
{
    if(buttonClient){ delete buttonClient; }
    if(buttonStaff){ delete buttonStaff; }

    if(layout){ delete layout; }

    if(windowStaffLogin){ delete windowStaffLogin; }
    if(windowClientLogin){ delete windowClientLogin; }
}

void WindowStartMenu::clickButClient()
{
    windowClientLogin = new WindowClientLogin();

    windowClientLogin->show();
    this->close();
}

void WindowStartMenu::clickButStaff()
{
    windowStaffLogin = new WindowStaffLogin();

    windowStaffLogin->show();
    this->close();
}
