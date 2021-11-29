#include "WindowControlPanelStaff.h"

WindowControlPanelStaff::WindowControlPanelStaff() : layout(new QVBoxLayout()), tabs(new QTabWidget()), windowAirCompany(new WindowAirCompany()), windowAirplane(new WindowAirplane())
{
    setLayout(layout);

    tabs->addTab(windowAirCompany, "Авиакомпании");
    tabs->addTab(windowAirplane, "Самолеты");

    layout->addWidget(tabs);
}

WindowControlPanelStaff::~WindowControlPanelStaff()
{
    if(windowAirCompany){ delete windowAirCompany; }
    if(windowAirplane){ delete windowAirplane; }

    if(tabs){ delete tabs; }

    if(layout){ delete layout; }
}
