#ifndef WINDOWCONTROLPANELCLIENT_H
#define WINDOWCONTROLPANELCLIENT_H

#include <QObject>
#include <QWidget>

#include <QGroupBox>

#include <QVBoxLayout>

#include <QPushButton>

#include <QTabWidget>

#include "WindowServicesClient.h"
#include "WindowFlightsClient.h"
#include "WindowPlacesOfAirportsClient.h"
#include "WindowTicketsClient.h"
#include "WindowProfile.h"

class WindowControlPanelClient : public QWidget
{
    Q_OBJECT
public:
    explicit WindowControlPanelClient(ClientFull, QString);
    ~WindowControlPanelClient();

private:
    QVBoxLayout *layout;

    QTabWidget *tabs;

    WindowFlightsClient *windowFlightsClient;
    WindowServicesClient *windowServicesClient;
    WindowPlacesOfAirportsClient *windowPlacesOfAirportsClient;
    WindowTicketsClient *windowTicketsClient;
    WindowProfile *windowProfile;

    QString Host;
};

#endif // WINDOWCONTROLPANELCLIENT_H
