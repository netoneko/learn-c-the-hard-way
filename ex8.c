#include <stdio.h>

int main(int argc, char *argv[]) {
  int areas[] = {1, 2, 7, 40, 93};
  char name[] = "Kirill";

  char full_name[] = {'K', 'i', 'r', 'i', 'l', 'l', ' ',
                    'A', '.', ' ',
                    'M', 'a', 'k', 's', 'i', 'm', 'o', 'v', '\0'};

  printf("The size of an int: %ld\n",
          sizeof(int));
  printf("The size of areas int[]: %ld\n",
          sizeof(areas));
  printf("The first area %ld, the second %ld.\n",
          sizeof(areas[0]), sizeof(areas[1]));

  printf("The size of a char: %ld\n",
          sizeof(char));
  printf("The size of name (char[]): %ld\n",
         sizeof(name));
  printf("The number of chars: %ld\n",
          sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %ld\n",
            sizeof(full_name));
  printf("The number of chars: %ld\n",
          sizeof(full_name) / sizeof(char));

  printf("name=\"%s\" and full_name=\"%s\"\n",
         name, full_name);

  return 0;
}

