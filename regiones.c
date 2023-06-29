#include <stdio.h>
#include <stdlib.h>

#include "regiones.h"
#include "utilidades.h"

int AgregarRegion(struct NodoRegion **head, struct NodoRegion *region) {
  
  if (*head == NULL) {
    *head = region;
    return 0;
  }
  
  if (BuscarRegion(*head, region->detalleregion->numero) != NULL) {
    return 1;
  }

  struct NodoRegion *rec = *head;

  while (rec->sig != NULL) {
    rec = rec->sig;
  }

  rec->sig = region;

  return 0;
}

int EliminarRegion(struct NodoRegion **head, int numero) {
  if(*head == NULL)
    return 1;
  
  if ((*head)->detalleregion->numero == numero) {
    *head = (*head)->sig;
    return 0;
  }

  struct NodoRegion *rec = *head;

  while (rec->sig != NULL) {
    if (rec->sig->detalleregion->numero == numero) {
      rec->sig = rec->sig->sig;
      free(rec->sig);
      return 0;
    }
    rec = rec->sig;
  }
  return 1;
}

struct NodoRegion *BuscarRegion(struct NodoRegion *head, int numero) {
  if(head==NULL)
    return NULL;
  struct NodoRegion *rec=head;
  while (rec != NULL) {
    if (rec->detalleregion->numero == numero) {
      return rec;
    }
    rec = rec->sig;
  }
  return NULL;
}

void ModificarRegion(struct Region *region) {
  if (region == NULL) {
    return;
  }

  int entrada;

  do {
    MostrarRegion(region);
    printf("0. regresar\n1. nombre\n\n");
    entrada = EnterInteger(0, 1, "¿Que desea modificar? ");
    switch (entrada) {
    case 1:
      region->nombre = EnterText("Ingrese nuevo nombre: ");
      break;
    }
  } while (entrada != 0);
}

void ListarRegiones(struct NodoRegion *head) {
  if (head == NULL) {
    printf("No hay nada que mostrar\n\n");
    return;
  }

  struct NodoRegion *rec = head;

  printf("Lista de Regiones:\n\n");
  while (rec != NULL) {
    MostrarRegion(rec->detalleregion);
    rec = rec->sig;
  }
  printf("Fin de la lista\n\n");
}

void MostrarRegion(struct Region *region) {
  printf("Numero: %d\n", region->numero);
  printf("Nombre: %s\n\n", region->nombre);
}

struct NodoRegion *CrearNodoRegion(struct Region *region) {
  struct NodoRegion *nuevo = (struct NodoRegion *) malloc(sizeof(struct NodoRegion));

  nuevo->detalleregion = region;
  nuevo->sig = NULL;

  return nuevo;
}

struct Region *CrearRegion() {
  struct Region *nuevo = (struct Region *)malloc(sizeof(struct Region));
  
  nuevo->numero = EnterInteger(0, 16,"Ingrese el numero de la region: ");
  nuevo->nombre = EnterText("Ingrese el nombre de la region: ");
  nuevo->sucursales = NULL;

  return nuevo;
}