#include <stdio.h>

int main(int argc, char *argv[]) {
  int distance = 100;
  float power = 2.345f;
  double super_power = 4123423143214.32141234;
  char initial = 'A';
  char first_name[] = "Kirill";
  char last_name[] = "Maksimov";

  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of power.\n", power);
  printf("You have %f awesome supwerpowers.\n", super_power);
  printf("You have initial %c.\n", initial);
  printf("You are %s %c. %s.\n", first_name, initial, last_name);

  return 0;
}

