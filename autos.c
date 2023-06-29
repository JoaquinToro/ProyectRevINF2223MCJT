#include "autos.h"
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>

int AgregarAuto(struct NodoAuto **head, struct NodoAuto *nuevoAuto) {
  if (BuscarAuto(*head, nuevoAuto->detalleauto->id) != NULL) {
    return 1;
  }

  if (*head == NULL) {
    *head = nuevoAuto;
    nuevoAuto->sig = *head;
    return 0;
  }

  struct NodoAuto *rec = *head;

  do {
    rec = rec->sig;
  } while (rec->sig != *head);

  rec->sig = nuevoAuto;
  nuevoAuto->sig = *head;

  return 0;
}

int EliminarAuto(struct NodoAuto **head, int id) {
  if (*head == NULL)
    return 1;
  struct NodoAuto *rec = *head;
  do {
    if (rec->sig->detalleauto->id == id) {
      if (rec->sig == rec) {
        *head = NULL;
        return 0;
      }
      if (rec->sig == *head) {
        (*head) = (*head)->sig;
      }
      rec->sig = rec->sig->sig;
      return 0;
    }
    rec = rec->sig;
  } while (rec != (*head));
  return 1;
}

struct NodoAuto *BuscarAuto(struct NodoAuto *head, int id) {
  if (head == NULL)
    return NULL;
  struct NodoAuto *rec = head;
  do {
    if (rec->detalleauto->id == id)
      return rec;
    rec = rec->sig;
  } while (rec != head);
  return NULL;
}

void ModificarAuto(struct Auto *mAuto) {
  if (mAuto == NULL) {
    return;
  }

  int entrada;

  do {
    MostrarAuto(mAuto);
    printf("0. regresar\n1. marca\n2. modelo\n3. precio\n4. año\n5. recalls\n\n");
    entrada = EnterInteger(0, 5, "¿Que desea modificar? ");
    switch (entrada) {
    case 1:
      mAuto->marca = EnterText("Ingrese nueva marca: ");
      break;
    case 2:
      mAuto->modelo = EnterText("Ingrese nuevo modelo: ");
      break;
    case 3:
      mAuto->precio = EnterInteger(0, POSINF, "Ingrese nuevo precio: ");
      break;
    case 4:
      mAuto->year = EnterInteger(0, POSINF, "Ingrese nuevo año: ");
      break;
    case 5:
      mAuto->recalls = EnterInteger(0, POSINF, "Ingrese recalls: ");
      break;
    }
  } while (entrada != 0);
}

void ListarAutos(struct NodoAuto *head) {
  if (head == NULL) {
    printf("No hay nada que mostrar\n\n");
    return;
  }
  struct NodoAuto *rec = head;
  printf("Lista De Autos:\n\n");

  do {
    MostrarAuto(rec->detalleauto);
    rec = rec->sig;
  } while (rec != head);

  printf("Fin de la lista\n\n");
}

void MostrarAuto(struct Auto *mAuto) {
  printf("Id: %d\n", mAuto->id);
  printf("Marca: %s\n", mAuto->marca);
  printf("Modelo: %s\n", mAuto->modelo);
  printf("Año: %d\n", mAuto->year);
  printf("Precio: %d\n", mAuto->precio);
  printf("Recalls: %d\n\n", mAuto->recalls);
}

struct NodoAuto *CrearNodoAuto(struct Auto *nAuto) {
  struct NodoAuto *nuevo = (struct NodoAuto *)malloc(sizeof(struct NodoAuto));

  nuevo->detalleauto = nAuto;
  nuevo->sig = NULL;

  return nuevo;
}

struct Auto *CrearAuto() {
  struct Auto *nuevo = (struct Auto *)malloc(sizeof(struct Auto));

  nuevo->id = EnterInteger(0, POSINF, "Ingrese el id del auto: ");
  nuevo->marca = EnterText("Ingrese la marca del auto: ");
  nuevo->modelo = EnterText("Ingrese el modelo del auto: ");
  nuevo->year = EnterInteger(0, POSINF, "Ingrese el año del auto: ");
  nuevo->precio = EnterInteger(0, POSINF, "Ingrese el precio del auto: ");
  nuevo->recalls = 0;

  return nuevo;
}