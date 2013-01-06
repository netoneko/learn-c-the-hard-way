#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 512
#define MAX_DATA 100
#define MAX_LINES MAX_DATA * 2 + 1

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

struct Address {
  int id;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
  int count;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

struct Address *Address_create(char *name, char *email) {
  struct Address *addr = malloc(sizeof(struct Address));
  if (!addr) die("Memory error");

  strncpy(addr->name, name, MAX_DATA);
  strncpy(addr->email, email, MAX_DATA);

  return addr;
}

void Address_print(struct Address *addr) {
  printf("%s <%s>\n", addr->name, addr->email);
}


void Database_set(struct Connection *conn, char *name, char *email) {
  if (!conn) die("memory error");

  struct Address *addr = Address_create(name, email);
  conn->db->rows[conn->db->count] = *addr;
  conn->db->count++;
}

void Database_load(struct Connection *conn) {
  char *line = malloc(sizeof(char) * MAX_LINES);
  while (fgets(line, MAX_LINES, conn->file) != NULL) {
    char *name = strndup(line, MAX_DATA);
    char *email = NULL;

    strtok_r(name, ",", &email);
    *rindex(email, '\n') = '\0';

    Database_set(conn, name, email);
  }
}

struct Connection *Database_open(char *dbfile) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die("Memory error");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) die("Memory error");
  conn->db->count = 0;

  conn->file = fopen(dbfile, "r+");

  if (!conn->file) conn->file = fopen(dbfile, "w+");

  if (!conn->file) die("Could not open the file");

  Database_load(conn);

  return conn;
}

void Database_close(struct Connection *conn) {
  if (!conn) die("Memory error");

  fclose(conn->file);

  free(conn->db);
  free(conn);
}

void Database_write(struct Connection *conn) {
  rewind(conn->file);

  for (int i = 0; i < conn->db->count; i++) {
    struct Address *addr = &conn->db->rows[i];

    if (!addr) continue;
    
    char *line = malloc(sizeof(char) * MAX_DATA);;
    sprintf(line, "%s,%s\n", addr->name, addr->email);

    int rc = fputs(line, conn->file);

    free(line);
    if (rc != 1) die("Failed to write database");
  }

  fflush(conn->file);
}

void Database_delete(struct Connection *conn, int num) {
  if (!conn) die("Memory error");

  printf("count, num: %d, %d\n", conn->db->count, num);

  if (conn->db->count <= num) die("Sorry, I just can't.");

  struct Address *addr = &conn->db->rows[num];
  printf("Following address was deleted: ");
  Address_print(addr);

  //conn->db->rows[num] = NULL;
  //free(addr);
}


void Database_list(struct Connection *conn) {
  for (int i = 0; i < conn->db->count; i++) {
    printf("#%d ", i);
    Address_print(&conn->db->rows[i]);
  }

  printf("Total %d entries.\n", conn->db->count);
}

void process_input(char *dbfile, char *action, char *params[], int paramc) {
  struct Connection *conn = Database_open(dbfile);

  switch (action[0]) {
     case 's':
       if (paramc < 2) die("Please specify name and email");
       Database_set(conn, params[0], params[1]);
       Database_write(conn);
       break;

     case 'l':
       Database_list(conn);
       break;

     case 'd':
       if (paramc < 1) die("Please specify id");
       Database_delete(conn, atoi(params[0]));
       Database_write(conn);
       break;

     default:
       die("Invalid action, only g=get, s=set, d=delete, l=list.\n");
  }

  Database_close(conn);
}

int main(int argc, char *argv[]) {
  if (argc < 3) die("USAGE: ex17 <dbfile> <action> <params>");

  char *dbfile = argv[1];
  char *action = argv[2];
  char **params = &argv[3];
  int paramc = argc - 3;

  process_input(dbfile, action, params, paramc);

  return 0;
}


