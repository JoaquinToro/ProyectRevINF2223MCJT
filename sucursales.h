#ifndef SUCURSALES_H
#define SUCURSALES_H

#include "stock.h"

struct NodoSucursal {
  struct Sucursal *detallesucursal;
  struct NodoSucursal *izq, *der;
};

struct Sucursal {
  int id;
  int idRegion;
  char *nombre;
  char *direccion;
  struct Stock *vehiculos;
};

int AgregarSucursal(struct NodoSucursal **abb, struct NodoSucursal *nuevaSucursal);
int EliminarSucursal(struct NodoSucursal **abb, int id);
struct NodoSucursal *BuscarSucursal(struct NodoSucursal *abb, int id);
void ModificarSucursal(struct Sucursal *sucursal);
void ListarSucursales(struct NodoSucursal *abb);
void MostrarSucursal(struct Sucursal *sucursal);
struct NodoSucursal *CrearNodoSucursal(struct Sucursal* sucursal);
struct Sucursal *CrearSucursal();

#endif //! SUCURSALES_H