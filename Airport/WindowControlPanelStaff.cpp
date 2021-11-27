#include "WindowControlPanelStaff.h"

WindowControlPanelStaff::WindowControlPanelStaff() : layout(new QVBoxLayout()), tabs(new QTabWidget()), windowAirCompany(new WindowAirCompany())
{
    setLayout(layout);

    tabs->addTab(windowAirCompany, "Авиакомпании");

    layout->addWidget(tabs);
}

WindowControlPanelStaff::~WindowControlPanelStaff()
{
    if(windowAirCompany){ delete windowAirCompany; }

    if(tabs){ delete tabs; }

    if(layout){ delete layout; }
}
