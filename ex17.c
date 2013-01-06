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

void print_params(char *params[], int paramc) {
  printf("params: \n");

  for (int i = 0; i < paramc; i++) {
    printf("\t%s\n", params[i]);
  }
}

void print_input(char *dbfile, char *action, char *params[], int paramc) {
  printf("Input:\n");
  printf("dbfile: %s\n", dbfile);
  printf("action: %s\n", action);

  print_params(params, paramc);

  printf("======================\n");
}

struct Address {
  int id;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Address *Address_create(char *name, char *email) {
  struct Address *addr = malloc(sizeof(struct Address));
  if (!addr) die("Memory error");

  strncpy(addr->name, name, MAX_DATA);
  strncpy(addr->email, email, MAX_DATA);

  return addr;
}

void Address_destroy(struct Address *addr) {
  if (!addr) die("Memory error");

  //free(addr->name);
  //free(addr->email);
  //free(addr);
}

void Address_print(struct Address *addr) {
  printf("Name: %s\n", addr->name);
  printf("Email: %s\n", addr->email);
}

struct Database {
  struct Address rows[MAX_ROWS];
  int count;
};

struct Database *Database_create() {
  struct Database *db = malloc(sizeof(struct Database));
  if (!db) die("Memory error");

  db->count = 0;

  return db;
}

void Database_destroy(struct Database *db) {
  if (!db) die("Memory error");

  //for (int i = 0; i < db->count; i++) {
  //  Address_destroy(&db->rows[i]);
  //}

  //free(db->rows);
  free(db);
}

void Database_set(struct Database *db, char *name, char *email) {
  if (!db) die("Memory error");

  struct Address *addr = Address_create(name, email);
  db->rows[db->count] = *addr;
  db->count++;

  Address_print(addr);
}

struct Connection {
  FILE *file;
  struct Database *db;
};

struct Connection *Connection_create() {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die("Memory error");

  return conn;
}

void Connection_destroy(struct Connection *conn) {
  if (!conn) die("Memory error");  

  //free(conn->db);
  //free(conn->file);
  free(conn);
}

void process_input(char *dbfile, char *action, char *params[], int paramc) {
  struct Connection *conn = Connection_create();
  struct Database *db = Database_create();
  
  conn->db = db;

  switch (action[0]) {
     case 's':
       if (paramc < 2) die("Please specify name and email");
       Database_set(db, params[0], params[1]); 
       break;

     default:
       die("Invalid action, only c=create, g=get, s=set, d=delete, l=list.\n");
  }

  Connection_destroy(conn);
  Database_destroy(db);
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


