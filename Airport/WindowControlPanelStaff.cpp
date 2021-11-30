#include "WindowControlPanelStaff.h"

WindowControlPanelStaff::WindowControlPanelStaff() : layout(new QVBoxLayout()), tabs(new QTabWidget()), windowAirCompany(new WindowAirCompany()), windowAirplane(new WindowAirplane()), windowServices(new WindowServices())
{
    setLayout(layout);

    tabs->addTab(windowAirCompany, "Авиакомпании");
    tabs->addTab(windowAirplane, "Самолеты");
    tabs->addTab(windowServices, "Услуги");

    layout->addWidget(tabs);
}

WindowControlPanelStaff::~WindowControlPanelStaff()
{
    if(windowAirCompany){ delete windowAirCompany; }
    if(windowAirplane){ delete windowAirplane; }
    if(windowServices){ delete windowServices; }

    if(tabs){ delete tabs; }

    if(layout){ delete layout; }
}
