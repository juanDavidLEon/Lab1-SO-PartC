#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define TAMCAD 100

#define MAX_LINE_LENGTH 1000

void leerUpTime();
void leerUserStat();
void versionKernel();
void modelAndType();
void diskStat();
void context();
void process();
void imprimirFormato(int segundos);

int main() {

  modelAndType();
  versionKernel();
  leerUpTime();
  leerUserStat();
  diskStat();
  context();
  leerUpTime();
  process();

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
  printf("Uptime: ");
  imprimirFormato(dato1);
  printf("\n");

  fclose(textfile);
}


void leerUserStat() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  int user, nice, system, idle, x1, x2, x3, x4, x5, x6;
  char command[2];
  char opc;

  textfile = fopen("/proc/stat", "r");
  if (textfile == NULL)
    return;

  do {
    fflush(stdin);
    printf("\nsi desea mas informacion del sistema use el comando -s\n");
    scanf("\n%s", command);

    if (!strcmp(command, "-s")) {

      fscanf(textfile, "cpu %d %d %d %d %d %d %d %d %d %d", &user, &nice,
             &system, &idle, &x1, &x2, &x3, &x4, &x5, &x6);

      printf("\nUser: ");
      imprimirFormato(user * 100);
      printf("\nsystem: ");
      imprimirFormato(system * 100);
      printf("\nidle: ");
      imprimirFormato(idle * 100);
      printf("\n");

      fclose(textfile);
      break;
    }
    printf("Comando incorrecto.");
  } while (strcmp(command, "-s"));
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
  FILE *fp = fopen("/proc/cpuinfo", "r");
  int n = 0;
  char lineascpu[TAMCAD];

  // Para hallar el numero de lineas de un archivo
  while (!feof(fp)) {
    fscanf(fp, "%s", lineascpu);
    n++;
  }
  //printf("El numero de lineas que tiene el archivo es de: %d\n", n);

  rewind(fp); // Para volver al inicio del archivo

  char palabrasModelType[n][TAMCAD];
  int i = 0;

  // Para almecenar las lineas del archivo en un arreglo de caracteres llamado
  // palabrasModelType
  while (!feof(fp)) {
    fscanf(fp, "%s", palabrasModelType[i]);
    i++;
  }

  // Recorre el arreglo de caracteres
   for (i = 0; i < n; i++) {

    // Condicion para imprimir el modelo del cpu
    if(!strcmp(palabrasModelType[i], "vendor_id")){
      //printf("%d\n", i);
      printf("Type: ");
      printf("%s\n", palabrasModelType[i + 2]);
      break;
      }
   }

    for (i = 0; i < n; i++) {

    // Condicion para imprimir el modelo del cpu
    if(!strcmp(palabrasModelType[i], "name")){
      //printf("%d\n", i);
      printf("Cpu model: ");
      printf("%s ", palabrasModelType[i + 2]);
      printf("%s ", palabrasModelType[i + 3]);
      printf("%s", palabrasModelType[i + 4]);
      break;
      }
   }

  fclose(fp);
}


void diskStat() {
  FILE *fp = fopen("/proc/diskstats", "r");
  int n = 0;
  char lineasDisk[TAMCAD];

  // Para hallar el numero de lineas de un archivo
  while (!feof(fp)) {
    fscanf(fp, "%s", lineasDisk);
    n++;
  }
  //printf("El numero de lineas que tiene el archivo es de: %d\n", n);

  rewind(fp); // Para volver al inicio del archivo

  char palabrasDisk[n][TAMCAD];
  int i = 0;

  // Para almecenar las lineas del archivo en un arreglo de caracteres llamado
  // palabrasDisk
  while (!feof(fp)) {
    fscanf(fp, "%s", palabrasDisk[i]);
    i++;
  }

  // Recorre el arreglo de caracteres
   for (i = 0; i < n; i++) {

    // Condicion para imprimir las lecturas completadas con éxito en el disco
    if (!strcmp(palabrasDisk[i], "sda")) {
      //printf("%d\n", i); //Indice de la palabra
      printf("Numero de peticiones a disco realizadas:\n");
      printf("Lectura: ");
      printf("%s", palabrasDisk[i + 4]);
      printf("\n");
    }
  }

  // Recorre el arreglo de caracteres
   for (i = 0; i < n; i++) {

    // Condicion para imprimir las escrituras completadas
    if (!strcmp(palabrasDisk[i], "sda")) {
      //printf("%d\n", i); //Indice de la palabra
      printf("Escritura: ");
      printf("%s", palabrasDisk[i + 8]);
    }
  }

  printf("\n");
  fclose(fp);
}


void context() {
  FILE *fp = fopen("/proc/stat", "r");
  int n = 0;
  char lineas[TAMCAD];

  // Para hallar el numero de lineas de un archivo
  while (!feof(fp)) {
    fscanf(fp, "%s", lineas);
    n++;
  }
  // printf("El numero de lineas que tiene el archivo es de: %d\n", n);

  rewind(fp); // Para volver al inicio del archivo

  char palabras[n][TAMCAD];
  int i = 0;

  // Para almecenar las lineas del archivo en un arreglo de caracteres llamado
  // palabras
  while (!feof(fp)) {
    fscanf(fp, "%s", palabras[i]);
    i++;
  }

  // Recorre el arreglo de caracteres
  for (i = 0; i < n; i++) {

    // Condicion para imprimir ctxt del archivo
    if (!strcmp(palabras[i], "ctxt")) {
      // printf("%d\n", i); //Indice de la palabra
      printf("%s: ", palabras[i]);
      printf("%s", palabras[i + 1]);
      printf("\n");
    }
  }

  fclose(fp);
}


void process(){
    FILE *fp = fopen("/proc/stat", "r");
  int n = 0;
  char lineas[TAMCAD];

  // Para hallar el numero de lineas de un archivo
  while (!feof(fp)) {
    fscanf(fp, "%s", lineas);
    n++;
  }
  // printf("El numero de lineas que tiene el archivo es de: %d\n", n);

  rewind(fp); // Para volver al inicio del archivo

  char palabras[n][TAMCAD];
  int i = 0;

  // Para almecenar las lineas del archivo en un arreglo de caracteres llamado
  // palabras
  while (!feof(fp)) {
    fscanf(fp, "%s", palabras[i]);
    i++;
  }

  // Recorre el arreglo de caracteres
  for (i = 0; i < n; i++) {

    // Condicion para imprimir processes del archivo
    if (!strcmp(palabras[i], "processes")) {
      // printf("%d\n", i);  //Indice de la palabra
      printf("%s: ", palabras[i]);
      printf("%s", palabras[i + 1]);
    }
  }

  printf("\n");
  fclose(fp);
}


void imprimirFormato(int seconds) {

  int dias = (int)seconds / (24 * 3600);
  int horas = ((int)seconds % (24 * 3600)) / 3600;
  int minutos = (((int)seconds % (24 * 3600)) % 3600) / 60;
  int segundos = (((int)seconds % (24 * 3600)) % 3600) % 60;

  printf("%id %i:%i:%i ", dias, horas, minutos, segundos);
}