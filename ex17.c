#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void die(char *message) {
  if (errno) {
    perror(message);
  }
  else {
    printf("ERROR: %s.\n", message);
  }

  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc < 3) die("USAGE: ex17 <dbfile> <action> <params>");

  char *dbfile = argv[1];
  char *action = argv[2];
  char **params = &argv[3];

  printf("Input:\n");
  printf("dbfile: %s\n", dbfile);
  printf("action: %s\n", action);
  printf("params: \n");

  for (int i = 0; i < (argc - 3) ; i++) {
    printf("\t%s\n", *(params + i));
  }

  return 0;
}


