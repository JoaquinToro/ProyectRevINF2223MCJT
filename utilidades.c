#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NodoEntero *AgregarNodoEntero(struct NodoEntero *lista, int numero) {
  struct NodoEntero *nuevo =
      (struct NodoEntero *)malloc(sizeof(struct NodoEntero));

  nuevo->entero = numero;
  nuevo->sig = lista;

  return nuevo;
}

int BuscarNodoEntero(struct NodoEntero *lista, int numero) {
  while (lista != NULL) {
    if (lista->entero == numero) {
      return 0;
    }
    lista = lista->sig;
  }
  return 1;
}

struct NodoCaracteres *AgregarNodoCaracteres(struct NodoCaracteres *lista,
                                             char *caracteres) {
  struct NodoCaracteres *nuevo =
      (struct NodoCaracteres *)malloc(sizeof(struct NodoCaracteres));

  nuevo->caracteres = caracteres;
  nuevo->sig = lista;

  return nuevo;
}

int BuscarNodoCaracteres(struct NodoCaracteres *lista, char *caracteres) {
  while (lista != NULL) {
    if (strcmp(lista->caracteres, caracteres) == 0) {
      return 0;
    }
    lista = lista->sig;
  }
  return 1;
}

void PrintListaCaracteres(struct NodoCaracteres *lista) {
  int i = 1;
  while (lista != NULL) {
    printf("%d. %s\n", i++, lista->caracteres);
    lista = lista->sig;
  }
  printf("\n");
}

char *EnterText(char *printText) {
  char *aux, *text;
  int scanFlag;
  aux = (char *)malloc(sizeof(char) * maxstr);
  do {
    printf("[MAX %d CARACTERES] ", maxstr);
    printf(printText);

    scanFlag = !scanf("%[^\n]", aux);
    if (scanFlag) {
      printf("\nValor invalido.\n");
    }
    printf("\n");
    limpiarInputBuffer;
  } while (scanFlag);

  text = (char *)malloc(sizeof(char) * strlen(aux));
  if (!text) {
    return NULL;
  }
  strcpy(text, aux);

  return text;
}

int EnterInteger(int min, int max, char *printText) {
  int output;
  int scanFlag;
  do {
    printf("[ENTERO ");
    if (max == POSINF && min == NEGINF) {
      printf("] ");
    } else if (max == POSINF) {
      printf("MAYOR O IGUAL A %d] ", min);
    } else if (min == NEGINF) {
      printf("MENOR O IGUAL A %d] ", max);
    } else {
      printf("ENTRE %d - %d] ", min, max);
    }

    printf(printText);
    scanFlag = !scanf("%d", &output) || output < min || output > max;
    if (scanFlag) {
      printf("\nValor invalido.\n");
    }
    printf("\n");
    limpiarInputBuffer;
  } while (scanFlag);
  return output;
}