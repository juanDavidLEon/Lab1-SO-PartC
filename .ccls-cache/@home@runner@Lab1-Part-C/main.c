#include <stdio.h>

#define MAX_LINE_LENGTH 1000

void leerUpTime();
void leerUserStat();
void versionKernel();
void modelAndType();
void imprimirFormato(int segundos);

int main() {

  modelAndType();
  versionKernel();
  leerUpTime();
  leerUserStat();


  return 0;
}

void leerUpTime() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  float dato1, dato2;

  textfile = fopen("/proc/uptime", "r");
  if (textfile == NULL)
    return;

  fscanf(textfile, "%f %f", &dato1, &dato2);
  printf("Uptime: "); imprimirFormato(dato1);

  fclose(textfile);
}

void leerUserStat() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  int user, nice, system, idle, x1, x2, x3, x4, x5, x6;

  textfile = fopen("/proc/stat", "r");
  if (textfile == NULL)
    return;

  fscanf(textfile, "cpu %d %d %d %d %d %d %d %d %d %d", &user, &nice, &system,
         &idle, &x1, &x2, &x3, &x4, &x5, &x6);

  printf("\nUser: ");
  imprimirFormato(user * 100);
  printf("\nsystem: ");
  imprimirFormato(system * 100);
  printf("\nidle: ");
  imprimirFormato(idle * 100);

  fclose(textfile);
}

void versionKernel() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char numVersion[30];

  textfile = fopen("/proc/version", "r");
  if (textfile == NULL)
    return;

  fscanf(textfile, "Linux version %s", numVersion);
  printf("\nKernel version: %s \n", numVersion);

  fclose(textfile);
}

void modelAndType() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char vendor[30];
  char business[20];
  char core[20];
  char processorNumber[20];
  
  textfile = fopen("/proc/cpuinfo", "r");
  if (textfile == NULL)
    return;

  fscanf(textfile, "processor	: 0\n vendor_id	: %s\n cpu family	: 6\n model : 94\n model name	: %s %s %s\n", vendor, business, core, processorNumber);
  printf("\nType: %s \nmodel: %s %s %s", vendor, business, core, processorNumber);

  fclose(textfile);
}

void imprimirFormato(int seconds) {

  int dias = (int)seconds / (24 * 3600);
  int horas = ((int)seconds % (24 * 3600)) / 3600;
  int minutos = (((int)seconds % (24 * 3600)) % 3600) / 60;
  int segundos = (((int)seconds % (24 * 3600)) % 3600) % 60;

  printf("%id %i:%i:%i ", dias, horas, minutos, segundos);
}