#ifndef PACIENTES_H
#define PACIENTES_H

#include "sqlite3.h"

void cadastrarPaciente(sqlite3 *db);
void listarPacientes(sqlite3 *db);

#endif
