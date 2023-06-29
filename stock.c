#include <stdio.h>
#include <stdlib.h>

#include "autos.h"
#include "stock.h"

struct Stock *CrearStock() {
  struct Stock *stock;

  stock = (struct Stock *)malloc(sizeof(struct Stock));

  stock->pLibre = 0;
  stock->autos = (struct Auto **)malloc(sizeof(struct Auto *) * maxAutos);

  return stock;
}

int AgregarStock(struct Stock *stock, struct Auto *nuevoAuto) {
  if (stock->pLibre >= maxAutos) {
    return 1;
  }

  stock->autos[stock->pLibre++] = nuevoAuto;

  return 0;
}

int EliminarStock(struct Stock *stock, int id) {
  int i;
  for (i = 0; i < stock->pLibre; i++) {
    if (stock->autos[i]->id == id) {
      Compactar(stock, i);
      return 0;
    }
  }
  return 1;
}

void Compactar(struct Stock *stock, int indexInicio) {
  int i;

  stock->pLibre--;

  for (i = indexInicio; i < stock->pLibre; i++) {
    stock->autos[i] = stock->autos[i + 1];
  }

  stock->autos[stock->pLibre] = NULL;
}

struct Auto *BuscarStock(struct Stock *stock, int id) {
  int i;
  for (i = 0; i < stock->pLibre; i++) {
    if (stock->autos[i]->id == id) {
      return stock->autos[i];
    }
  }
  return NULL;
}

int ModificarStock(struct Stock *stock, int cantNueva) {
  if (cantNueva == stock->cantAutos)
    return 1;
  stock->cantAutos = cantNueva;
  stock->pLibre = cantNueva;
  return 0;
}

void ListarStock(struct Stock *stock) {
  if (stock->pLibre == 0) {
    printf("No hay nada que mostrar\n\n");
    return;
  }

  int i;

  printf("Lista de Stock:\n\n");
  for (i = 0; i < stock->pLibre; i++) {
    MostrarAuto(stock->autos[i]);
  }
  printf("Fin de la lista\n\n");
}