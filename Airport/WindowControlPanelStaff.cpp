#include "WindowControlPanelStaff.h"

WindowControlPanelStaff::WindowControlPanelStaff(StaffFull staffFull, QString host) : layout(new QVBoxLayout()), tabs(new QTabWidget()), windowAirCompany(new WindowAirCompany(host)), windowAirplane(new WindowAirplane(host)), windowServices(new WindowServices(host)), windowPost(new WindowPost(host)), windowTickets(new WindowTickets(host)), windowPlacesOfAirports(new WindowPlacesOfAirports(host)), windowCategoriesCargo(new WindowCategoriesCargo(host)), windowFlights(new WindowFlights(host)), windowProfile(new WindowProfile(staffFull, host)), Host(host)
{
    setLayout(layout);

    tabs->addTab(windowAirCompany, "Авиакомпании");
    tabs->addTab(windowAirplane, "Самолеты");
    tabs->addTab(windowServices, "Услуги");
    tabs->addTab(windowPost, "Должности");
    tabs->addTab(windowTickets, "Билеты");
    tabs->addTab(windowPlacesOfAirports, "Аэропорты");
    tabs->addTab(windowCategoriesCargo, "Категории грузов");
    tabs->addTab(windowFlights, "Рейсы");
    tabs->addTab(windowProfile, "Профиль");

    layout->addWidget(tabs);
}

WindowControlPanelStaff::~WindowControlPanelStaff()
{
    if(windowAirCompany){ delete windowAirCompany; }
    if(windowAirplane){ delete windowAirplane; }
    if(windowServices){ delete windowServices; }
    if(windowPost){ delete windowPost; }
    if(windowTickets){ delete windowTickets; }
    if(windowPlacesOfAirports){ delete windowPlacesOfAirports; }
    if(windowCategoriesCargo){ delete windowCategoriesCargo; }
    if(windowFlights){ delete windowFlights; }

    if(tabs){ delete tabs; }

    if(layout){ delete layout; }
}
