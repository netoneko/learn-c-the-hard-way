#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 512
#define MAX_DATA 100

void die(char *message) {
  if (errno) {
    perror(message);
  }
  else {
    printf("ERROR: %s.\n", message);
  }

  exit(1);
}

struct Address {
  int id;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

struct Connection *Connection_create(char *dbname) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die("Memory error");

  return conn;
}

void Connection_destroy(struct Connection *connection) {
  free(connection->db);
  free(connection);
}

void print_input(char *dbfile, char *action, char *params[], int paramc) {
  printf("Input:\n");
  printf("dbfile: %s\n", dbfile);
  printf("action: %s\n", action);
  printf("params: \n");

  for (int i = 0; i < paramc; i++) {
    printf("\t%s\n", params[i]);
  }
}

void process_input(char *dbfile, char *action, char *params[], int paramc) {
  struct Connection *conn = Connection_create(dbfile);

  Connection_destroy(conn);
}

int main(int argc, char *argv[]) {
  if (argc < 3) die("USAGE: ex17 <dbfile> <action> <params>");

  char *dbfile = argv[1];
  char *action = argv[2];
  char **params = &argv[3];
  int paramc = argc - 3;

  print_input(dbfile, action, params, paramc);
  process_input(dbfile, action, params, paramc);

  return 0;
}


