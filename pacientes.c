#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "pacientes.h"

void cadastrarPaciente(sqlite3 *db) {
    char nome[120], cpf[30];
    int idade;
    char sql[256];
    char *err = NULL;

    getchar(); // limpar buffer
    printf("Nome do paciente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("CPF: ");
    scanf("%29s", cpf);

    printf("Idade: ");
    scanf("%d", &idade);

    snprintf(sql, sizeof(sql),
        "INSERT INTO pacientes (nome, cpf, idade) VALUES ('%s', '%s', %d);",
        nome, cpf, idade);

    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("Erro ao cadastrar paciente: %s\n", err ? err : "desconhecido");
        if (err) sqlite3_free(err);
    } else {
        printf("Paciente cadastrado.\n");
    }
}

void listarPacientes(sqlite3 *db) {
    const char *sql = "SELECT id, nome, cpf, idade FROM pacientes;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) { printf("Erro listar pacientes.\n"); return; }
    printf("\nID | Nome                      | CPF         | Idade\n---------------------------------------------------\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-2d | %-24s | %-11s | %d\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_int(stmt, 3));
    }
    sqlite3_finalize(stmt);
}
