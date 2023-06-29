#include <stdio.h>
#include <stdlib.h>

#include "sucursales.h"
#include "stock.h"
#include "utilidades.h"

int AgregarSucursal(struct NodoSucursal **abb, struct NodoSucursal *nuevaSucursal) {
  struct NodoSucursal **rec = abb;
  while (*rec != NULL) {
    if ((*rec)->detallesucursal->id == nuevaSucursal->detallesucursal->id) {
      return 1;
    }

    rec = (nuevaSucursal->detallesucursal->id < (*rec)->detallesucursal->id) ? &(*rec)->izq : &(*rec)->der;
  }

  *rec = nuevaSucursal;

  return 0;
}

int EliminarSucursal(struct NodoSucursal **abb, int id) {
  while ((*abb)) {
    if ((*abb)->detallesucursal->id == id) {
      if ((*abb)->izq && (*abb)->der) {
        struct NodoSucursal **raizRecorrido = &(*abb)->der;

        while ((*raizRecorrido)->izq) {
          raizRecorrido = &(*raizRecorrido)->izq;
        }

        (*abb)->detallesucursal = (*raizRecorrido)->detallesucursal;
        *raizRecorrido = (*raizRecorrido)->der;
      } else {
        *abb = ((*abb)->izq) ? (*abb)->izq : (*abb)->der;
      }
      return 0;
    }
    abb = (id < (*abb)->detallesucursal->id) ? &(*abb)->izq : &(*abb)->der;
  }
  return 1;
}

struct NodoSucursal *BuscarSucursal(struct NodoSucursal *abb, int id) {
  while (abb) {
    if (abb->detallesucursal->id == id) {
      return abb;
    }
    abb = (id < abb->detallesucursal->id) ? abb->izq : abb->der;
  }
  return NULL;
}

void ModificarSucursal(struct Sucursal *sucursal) {
  if (sucursal == NULL) {
    return;
  }

  int entrada;

  do {
    MostrarSucursal(sucursal);
    printf("0. regresar\n1. nombre\n2. direccion\n\n");
    entrada = EnterInteger(0, 2, "¿Que desea modificar? ");
    switch (entrada) {
    case 1:
      sucursal->nombre = EnterText("Ingrese nuevo nombre: ");
      break;
    case 2:
      sucursal->direccion = EnterText("Ingrese nueva direccion: ");
      break;
    }
  } while (entrada != 0);
}

void LSucursales(struct NodoSucursal *abb) {
  if (abb->izq){
      LSucursales(abb->izq);
  }
  MostrarSucursal(abb->detallesucursal);
  if (abb->der){
      LSucursales(abb->der);
  }
}

void ListarSucursales(struct NodoSucursal *abb) {
  if(abb==NULL) {
    printf("No hay nada que mostrar\n\n");
    return;
  }

  printf("Lista de Sucursales:\n\n");
  LSucursales(abb);
  printf("Fin de la lista\n\n");
}

void MostrarSucursal(struct Sucursal *sucursal) {
  printf("Id: %d\n", sucursal->id);
  printf("Nombre: %s\n", sucursal->nombre);
  printf("Direccion: %s\n\n", sucursal->direccion);
}

struct NodoSucursal *CrearNodoSucursal(struct Sucursal *sucursal) {
  struct NodoSucursal *nuevo =
      (struct NodoSucursal *)malloc(sizeof(struct NodoSucursal));

  nuevo->detallesucursal = sucursal;
  nuevo->izq = NULL;
  nuevo->der = NULL;

  return nuevo;
}

struct Sucursal *CrearSucursal() {
  struct Sucursal *nuevo = (struct Sucursal *)malloc(sizeof(struct Sucursal));

  nuevo->id = EnterInteger(0, POSINF, "Ingrese el id de la sucursal: ");
  nuevo->nombre = EnterText("Ingrese el nombre de la sucursal: ");
  nuevo->direccion = EnterText("Ingrese la direccion de la sucursal: ");
  nuevo->vehiculos = CrearStock();

  return nuevo;
}