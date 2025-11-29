#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "login.h"

int fazerLogin(sqlite3 *db, char *tipoUsuario, int tipoBuf, int *idUsuarioRetorno) {
    char usuario[80];
    char senha[80];
    char sql[256];
    sqlite3_stmt *stmt = NULL;
    int rc;

    printf("Usuario: ");
    scanf("%79s", usuario);
    printf("Senha: ");
    scanf("%79s", senha);

    snprintf(sql, sizeof(sql),
            "SELECT id, tipo FROM usuarios WHERE username = '%s' AND senha = '%s' LIMIT 1;",
            usuario, senha);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro prepare login: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *tipo = sqlite3_column_text(stmt, 1);
        if (tipo) {
            strncpy(tipoUsuario, (const char*)tipo, tipoBuf-1);
            tipoUsuario[tipoBuf-1] = '\0';
        } else {
            tipoUsuario[0] = '\0';
        }
        *idUsuarioRetorno = id;
        sqlite3_finalize(stmt);
        return 1;
    } else {
        sqlite3_finalize(stmt);
        printf("Login invalido.\n");
        return 0;
    }
}
