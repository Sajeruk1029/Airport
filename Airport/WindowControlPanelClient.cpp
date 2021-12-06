#include "WindowControlPanelClient.h"

WindowControlPanelClient::WindowControlPanelClient(ClientFull clientFull, QString host) : layout(new QVBoxLayout()), tabs(new QTabWidget()), windowFlightsClient(new WindowFlightsClient(host)), windowServicesClient(new WindowServicesClient(host)), windowPlacesOfAirportsClient(new WindowPlacesOfAirportsClient(host)), windowTicketsClient(new WindowTicketsClient(clientFull, host)), windowProfile(new WindowProfile(clientFull, host)), Host(host)
{
    setLayout(layout);

    tabs->addTab(windowFlightsClient, "Рейсы");
    tabs->addTab(windowServicesClient, "Услуги");
    tabs->addTab(windowPlacesOfAirportsClient, "Аэропорты");
    tabs->addTab(windowTicketsClient, "Билеты");
    tabs->addTab(windowProfile, "Профиль");

    layout->addWidget(tabs);
}

WindowControlPanelClient::~WindowControlPanelClient()
{
    if(windowFlightsClient){ delete windowFlightsClient; }
    if(windowServicesClient){ delete windowServicesClient; }
    if(windowPlacesOfAirportsClient){ delete windowPlacesOfAirportsClient; }
    if(windowTicketsClient){ delete windowTicketsClient; }
    if(windowProfile){ delete windowProfile; }

    if(tabs){ delete tabs; }

    if(layout){ delete layout; }
}
