#include <stdio.h>
#include <stdlib.h>

#include "regiones.h"
#include "utilidades.h"
#include "ventas.h"

#define NoEncontrado printf("No se encuentra en el sistema\n\n")

struct DatosVentas *CrearDatosVentas() {
  struct DatosVentas *nuevo =
      (struct DatosVentas *)malloc(sizeof(struct DatosVentas));

  nuevo->cantidadVentas = 0;
  nuevo->dineroAcumulado = 0;
  nuevo->ventas = NULL;

  return nuevo;
}

int AgregarVenta(struct DatosVentas *ventas, struct NodoVenta *nuevaVenta) {
  struct NodoVenta **rec = &ventas->ventas;
  while (*rec != NULL) {
    if ((*rec)->detalleVenta->numero == nuevaVenta->detalleVenta->numero) {
      return 1;
    }

    rec = (nuevaVenta->detalleVenta->numero < (*rec)->detalleVenta->numero)
              ? &(*rec)->izq
              : &(*rec)->der;
  }

  *rec = nuevaVenta;
  ventas->cantidadVentas++;
  ventas->dineroAcumulado += nuevaVenta->detalleVenta->precio;

  return 0;
}

int EliminarVenta(struct DatosVentas *ventas, int numero) {
  struct NodoVenta **abb = &ventas->ventas;
  while ((*abb)) {
    if ((*abb)->detalleVenta->numero == numero) {
      ventas->cantidadVentas--;
      ventas->dineroAcumulado -= (*abb)->detalleVenta->precio;

      if ((*abb)->izq && (*abb)->der) {
        struct NodoVenta **raizRecorrido = &(*abb)->der;

        while ((*raizRecorrido)->izq) {
          raizRecorrido = &(*raizRecorrido)->izq;
        }

        (*abb)->detalleVenta = (*raizRecorrido)->detalleVenta;
        *raizRecorrido = (*raizRecorrido)->der;
      } else {
        *abb = ((*abb)->izq) ? (*abb)->izq : (*abb)->der;
      }

      return 0;
    }
    abb = (numero < (*abb)->detalleVenta->numero) ? &(*abb)->izq : &(*abb)->der;
  }
  return 1;
}

struct NodoVenta *BuscarVenta(struct NodoVenta *abb, int numero) {
  while (abb) {
    if (abb->detalleVenta->numero == numero) {
      return abb;
    }
    abb = (numero < abb->detalleVenta->numero) ? abb->izq : abb->der;
  }
  return NULL;
}

void ModificarVenta(struct Venta *venta, struct NodoRegion *regiones) {
  if (venta == NULL) {
    return;
  }

  struct Auto *mAuto;
  struct NodoRegion *region;
  struct NodoSucursal *sucursal;
  int entrada;

  do {
    MostrarVenta(venta);
    printf("0. regresar\n1. rut cliente.\n2. precio\n3. sucursal\n4. auto "
           "comprado\n\n");
    entrada = EnterInteger(0, 2, "¿Que desea modificar? ");
    switch (entrada) {
    case 1:
      venta->rutCliente = EnterText("Ingrese nuevo rut del cliente: ");
      break;
    case 2:
      venta->precio = EnterInteger(0, POSINF, "Ingrese nueva direccion: ");
      break;
    case 3:
      printf("¿En que region se encuentra la sucursal?\n");
      region =
          BuscarRegion(regiones, EnterInteger(0, POSINF, "Ingrese el ID: "));
      if (region == NULL)
        NoEncontrado;
      else {
        printf("¿A que sucursal se desea cambiar?");
        sucursal = BuscarSucursal(region->detalleregion->sucursales,
                                  EnterInteger(0, POSINF, "Ingrese el ID: "));
        if (sucursal == NULL)
          NoEncontrado;
        else
          venta->sucursal = sucursal->detallesucursal;
      }
      break;
    case 4:
      mAuto = BuscarStock(venta->sucursal->vehiculos,
                          EnterInteger(0, POSINF, "Ingrese el ID: "));
      if (mAuto == NULL)
        NoEncontrado;
      else
        venta->autoComprado = mAuto;
      break;
    }
  } while (entrada != 0);
}

void LVentas(struct NodoVenta *abb) {
  if (abb->izq) {
    LVentas(abb->izq);
  }
  MostrarVenta(abb->detalleVenta);
  if (abb->der) {
    LVentas(abb->der);
  }
}

void ListarVentas(struct DatosVentas *ventas) {
  printf("Total de ventas: %d\n", ventas->cantidadVentas);
  printf("Dinero acumulado: %d\n\n", ventas->dineroAcumulado);

  if (ventas->ventas == NULL) {
    printf("No hay nada que mostrar\n\n");
    return;
  }

  printf("Lista de Ventas:\n\n");
  LVentas(ventas->ventas);
  printf("Fin de la lista\n\n");
}

void MostrarVenta(struct Venta *venta) {
  printf("número de venta: %d\n", venta->numero);
  printf("rut cliente: %s\n", venta->rutCliente);
  printf("precio de compra: %d\n", venta->precio);
  printf("id sucursal: %d\n", venta->sucursal->id);
  printf("id auto comprado: %d\n\n", venta->autoComprado->id);
}

struct NodoVenta *CrearNodoVenta(struct Venta *venta) {
  struct NodoVenta *nuevo =
      (struct NodoVenta *)malloc(sizeof(struct NodoVenta));

  nuevo->detalleVenta = venta;
  nuevo->izq = NULL;
  nuevo->der = NULL;

  return nuevo;
}

struct Venta *CrearVenta(struct Region *region, struct Sucursal *sucursal,
                         struct Auto *mAuto) {
  struct Venta *nuevo = (struct Venta *)malloc(sizeof(struct Venta));
  nuevo->numero = EnterInteger(0, POSINF, ("Ingrese el ID de la venta: "));
  nuevo->rutCliente = EnterText("Ingrese el rut del cliente: ");
  nuevo->precio = mAuto->precio;
  nuevo->region = region;
  nuevo->sucursal = sucursal;
  nuevo->autoComprado = mAuto;

  return nuevo;
}