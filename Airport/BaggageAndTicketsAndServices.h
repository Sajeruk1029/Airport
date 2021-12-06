#ifndef BAGGAGEANDTICKETSANDSERVICES_H
#define BAGGAGEANDTICKETSANDSERVICES_H

#include <QList>

#include "Baggage.h"
#include "Tickets.h"
#include "Services.h"

typedef struct
{
    Baggage baggage;
    Tickets tickets;
    QList<Services> services;
} BaggageAndTicketsAndServices;

#endif // BAGGAGEANDTICKETSANDSERVICES_H
