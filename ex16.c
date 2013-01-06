#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int weight;
  int height;
};

struct Person *Person_create(char *name, int age, int weight, int height) {
  struct Person *person = malloc(sizeof(struct Person));
  assert(person != NULL);

  person->name = strdup(name);
  person->age = age;
  person->weight = weight;
  person->height = height;

  return person;
}

void Person_destroy(struct Person *person) {
  assert(person != NULL);
  free(person->name);
  free(person);
}

void Person_print(struct Person *person) {
  printf("Name: %s.\n", person->name);
  printf("Age: %d.\n", person->age);
  printf("Weight: %d.\n", person->weight);
  printf("Height: %d.\n", person->height);
}

int main(int argc, char *argv[]) {
  struct Person *kirill = Person_create("Kirill", 25, 74, 176);
  Person_print(kirill);
  Person_destroy(kirill);

  return 0;
}

