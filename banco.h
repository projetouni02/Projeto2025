#ifndef BANCO_H
#define BANCO_H

#include "sqlite3.h"

int abrirBanco(sqlite3 **db);
void criarTabelas(sqlite3 *db);

#endif
