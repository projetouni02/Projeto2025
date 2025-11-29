#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "usuarios.h"

void cadastrarUsuario(sqlite3 *db) {
    char user[80], pass[80], tipo[20];
    char sql[256];
    char *err = NULL;

    printf("Novo usuario - login: ");
    scanf("%79s", user);
    printf("Senha: ");
    scanf("%79s", pass);
    printf("Tipo (admin/medico/recepcao): ");
    scanf("%19s", tipo);

    snprintf(sql, sizeof(sql),
        "INSERT INTO usuarios (username, senha, tipo) VALUES ('%s', '%s', '%s');",
        user, pass, tipo);

    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("Erro ao cadastrar usuario: %s\n", err ? err : "desconhecido");
        if (err) sqlite3_free(err);
    } else {
        printf("Usuario cadastrado.\n");
    }
}

void listarUsuarios(sqlite3 *db) {
    const char *sql = "SELECT id, username, tipo FROM usuarios;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) { printf("Erro listar usuarios.\n"); return; }
    printf("\nID  | Usuario       | Tipo\n---------------------------\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-3d | %-13s | %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
}
