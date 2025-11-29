#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "banco.h"

int abrirBanco(sqlite3 **db) {
    int rc = sqlite3_open("sigsaude.db", db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir/ criar banco: %s\n", sqlite3_errmsg(*db));
        return 1;
    }
    return 0;
}

void criarTabelas(sqlite3 *db) {
    char *err = NULL;

    const char *sqlUsuarios =
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "senha TEXT NOT NULL,"
        "tipo TEXT NOT NULL"
        ");";

    const char *sqlPacientes =
        "CREATE TABLE IF NOT EXISTS pacientes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT NOT NULL,"
        "cpf TEXT UNIQUE,"
        "idade INTEGER"
        ");";

    const char *sqlMedicos =
        "CREATE TABLE IF NOT EXISTS medicos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT NOT NULL,"
        "crm TEXT UNIQUE,"
        "especialidade TEXT"
        ");";

    const char *sqlConsultas =
        "CREATE TABLE IF NOT EXISTS consultas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "id_paciente INTEGER,"
        "id_medico INTEGER,"
        "data TEXT,"
        "hora TEXT"
        ");";

    sqlite3_exec(db, sqlUsuarios, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL erro usuarios: %s\n", err); sqlite3_free(err); err = NULL; }

    sqlite3_exec(db, sqlPacientes, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL erro pacientes: %s\n", err); sqlite3_free(err); err = NULL; }

    sqlite3_exec(db, sqlMedicos, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL erro medicos: %s\n", err); sqlite3_free(err); err = NULL; }

    sqlite3_exec(db, sqlConsultas, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL erro consultas: %s\n", err); sqlite3_free(err); err = NULL; }

    /* cria admin default só se não existir */
    const char *sqlAdmin =
        "INSERT INTO usuarios (username, senha, tipo) "
        "SELECT 'admin','admin','admin' "
        "WHERE NOT EXISTS (SELECT 1 FROM usuarios WHERE username = 'admin');";

    sqlite3_exec(db, sqlAdmin, NULL, NULL, &err);
    if (err) { fprintf(stderr, "SQL erro admin: %s\n", err); sqlite3_free(err); err = NULL; }
}
