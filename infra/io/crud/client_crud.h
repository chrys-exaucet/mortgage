//
// Created by Roy on 11/02/2021.
//

#ifndef MORTGAGE_CLIENT_CRUD_H
#define MORTGAGE_CLIENT_CRUD_H

#include "../../../core/client/client.h"

int saveClientCsv(client_t client);

int deleteClientCsv(int clientId);

int updateClientCsv(client_t client);

#endif //MORTGAGE_CLIENT_CRUD_H
