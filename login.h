#ifndef LOGIN_H
#define LOGIN_H

#include "sqlite3.h"

int fazerLogin(sqlite3 *db, char *tipoUsuario, int tipoBuf, int *idUsuarioRetorno);

#endif
