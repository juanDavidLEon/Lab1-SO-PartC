#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define TAMCAD 500

#define MAX_LINE_LENGTH 1000

void leerUpTime();
void leerUserStat();
void versionKernel();
void modelAndType();
void diskStat();
void contextAndProcess();
void imprimirFormato(int segundos);

int main() {

  modelAndType();
  versionKernel();
  leerUpTime();
  contextAndProcess();
  // diskStat();
  // leerUserStat();

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
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char vendor[30];
  char business[20];
  char core[20];
  char processorNumber[20];

  textfile = fopen("/proc/cpuinfo", "r");
  if (textfile == NULL)
    return;

  fscanf(textfile,
         "processor	: 0\n vendor_id	: %s\n cpu family	: 6\n model : "
         "94\n model name	: %s %s %s\n",
         vendor, business, core, processorNumber);
  printf("\nType: %s \nmodel: %s %s %s", vendor, business, core,
         processorNumber);

  fclose(textfile);
}

void diskStat() {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  int reads, writes, major, min, device, x1, x2, x3, x4, x5, x6, x7, x8, x9,
      x10, x11, x12, x13, x14, x15, x16, x17, y1, y2, y3, y4, y5, y6, y7, y8,
      y9, y10, y11, y12, y13, y14, y15, y16, y17, z1, z2, z3, z4, z5, z6, z7,
      z8, z9, z10, z11, z12, z13, z14, z15, z16, z17, p1, p2, p3, p4, p5, p6,
      p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, b1, b2, b3, b4, b5,
      b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16, b17, d1, d2, d3, d4,
      d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, t1, t2, t3,
      t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, m1, m2,
      m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, r5,
      r6, r7;

  textfile = fopen("/proc/diskstats", "r");
  if (textfile == NULL)
    return;

  fscanf(
      textfile,
      "   7       0 loop0 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       1 loop1 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n "
      "   7       2 loop2 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       3 loop3 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       4 loop4 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       5 loop5 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       6 loop6 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    7       7 loop7 %d %d %d %d %d %d %d %d %d %d %d "
      "%d %d %d %d %d %d\n    8       0 sda %d %d %d %d %d %d %d %d",
      &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8, &x9, &x10, &x11, &x12, &x13, &x14,
      &x15, &x16, &x17, &y1, &y2, &y3, &y4, &y5, &y6, &y7, &y8, &y9, &y10, &y11,
      &y12, &y13, &y14, &y15, &y16, &y17, &z1, &z2, &z3, &z4, &z5, &z6, &z7,
      &z8, &z9, &z10, &z11, &z12, &z13, &z14, &z15, &z16, &z17, &p1, &p2, &p3,
      &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15, &p16,
      &p17, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12, &b13,
      &b14, &b15, &b16, &b17, &d1, &d2, &d3, &d4, &d5, &d6, &d7, &d8, &d9, &d10,
      &d11, &d12, &d13, &d14, &d15, &d16, &d17, &t1, &t2, &t3, &t4, &t5, &t6,
      &t7, &t8, &t9, &t10, &t11, &t12, &t13, &t14, &t15, &t16, &t17, &m1, &m2,
      &m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11, &m12, &m13, &m14, &m15,
      &m16, &m17, &major, &min, &device, &reads, &r5, &r6, &r7, &writes);

  printf("\nNúmero de peticiones a disco realizadas : %d %d \n", reads, writes);

  fclose(textfile);
}

void contextAndProcess() {
  FILE *fp = fopen("/proc/stat", "r");

  int n = 0;
  char palabra[TAMCAD];

  while (!feof(fp)) {
    fscanf(fp, "%s", palabra);
    n++;
  }
  printf("numero es de lineas es: %d\n", n);

  rewind(fp);

  char palabras[n][TAMCAD];
  int i = 0;

  while (!feof(fp)) {

    fscanf(fp, "%s", palabras[i]);
    i++;
  }

  printf("las palabras son\n");

  for (i = 0; i < n; i++) {

    if (!strcmp(palabras[i], "ctxt")) {
      // printf("ctxt\n");
      // printf("%d\n", i);
      printf("%s: ", palabras[2149]); printf("%s", palabras[2150]);
    }

  } // printf("%s\n", palabras[i]);

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