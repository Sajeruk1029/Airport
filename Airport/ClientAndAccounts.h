#ifndef CLIENTANDACCOUNTS_H
#define CLIENTANDACCOUNTS_H

#include "Accounts.h"
#include "Client.h"

typedef struct
{
    Client client;
    Accounts accounts;
} ClientAndAccounts;

#endif // CLIENTANDACCOUNTS_H
