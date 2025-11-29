#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "medicos.h"

void cadastrarMedico(sqlite3 *db) {
    char nome[120], crm[40], espec[80];
    char sql[256];
    char *err = NULL;

    getchar();
    printf("Nome do medico: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("CRM: ");
    scanf("%39s", crm);
    getchar();

    printf("Especialidade: ");
    fgets(espec, sizeof(espec), stdin);
    espec[strcspn(espec, "\n")] = 0;

    snprintf(sql, sizeof(sql),
        "INSERT INTO medicos (nome, crm, especialidade) VALUES ('%s', '%s', '%s');",
        nome, crm, espec);

    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("Erro ao cadastrar medico: %s\n", err ? err : "desconhecido");
        if (err) sqlite3_free(err);
    } else {
        printf("Medico cadastrado.\n");
    }
}

void listarMedicos(sqlite3 *db) {
    const char *sql = "SELECT id, nome, crm, especialidade FROM medicos;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) { printf("Erro listar medicos.\n"); return; }
    printf("\nID | Nome                     | CRM       | Especialidade\n--------------------------------------------------------\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-2d | %-23s | %-9s | %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3));
    }
    sqlite3_finalize(stmt);
}
