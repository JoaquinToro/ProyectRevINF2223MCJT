#ifndef UTILIDADES_H
#define UTILIDADES_H

#define maxstr 100
#define limpiarInputBuffer while (getchar() != '\n')
#define limpiarConsola printf("\e[1;1H\e[2J")

#define POSINF 0x7FFFFFFF
#define NEGINF 0xFFFFFFFF

#define TRUE 1
#define FALSE 0

struct NodoEntero {
  int entero;
  struct NodoEntero *sig;
};

struct NodoCaracteres {
  char *caracteres;
  struct NodoCaracteres *sig;
};

char *EnterText(char *printText);
int EnterInteger(int min, int max, char *printText);

void PrintListaCaracteres(struct NodoCaracteres* lista);

struct NodoEntero *AgregarNodoEntero(struct NodoEntero *lista, int numero);
int BuscarNodoEntero(struct NodoEntero *lista, int numero);

struct NodoCaracteres *AgregarNodoCaracteres(struct NodoCaracteres *lista,
                                             char *caracteres);
int BuscarNodoCaracteres(struct NodoCaracteres *lista, char *caracteres);

#endif //! UTILIDADES_H