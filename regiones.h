#ifndef REGIONES_H
#define REGIONES_H

#include "sucursales.h"

struct NodoRegion {
  struct Region *detalleregion;
  struct NodoRegion *sig;
};

struct Region {
  int numero;
  char *nombre;
  struct NodoSucursal *sucursales;
};

int AgregarRegion(struct NodoRegion **head, struct NodoRegion *region);
int EliminarRegion(struct NodoRegion **head, int numero);
struct NodoRegion *BuscarRegion(struct NodoRegion *head, int numero);
void ModificarRegion(struct Region *region);
void ListarRegiones(struct NodoRegion *head);
void MostrarRegion(struct Region *region);
struct NodoRegion *CrearNodoRegion(struct Region *region);
struct Region *CrearRegion();

#endif // REGIONES_H