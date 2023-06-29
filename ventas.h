#ifndef VENTAS_H
#define VENTAS_H

#include "autos.h"
#include "sucursales.h"

struct DatosVentas {
  int cantidadVentas;
  int dineroAcumulado;
  struct NodoVenta *ventas;
};

struct NodoVenta {
  struct Venta *detalleVenta;
  struct NodoVenta *izq;
  struct NodoVenta *der;
};

struct Venta {
  int numero;
  char *rutCliente;
  int precio;
  struct Region *region;
  struct Sucursal *sucursal;
  struct Auto *autoComprado;
};

struct DatosVentas *CrearDatosVentas();
int AgregarVenta(struct DatosVentas *ventas, struct NodoVenta *nuevaVenta);
int EliminarVenta(struct DatosVentas *ventas, int numero);
struct NodoVenta *BuscarVenta(struct NodoVenta *abb, int numero);
void ModificarVenta(struct Venta *venta, struct NodoRegion *regiones);
void ListarVentas(struct DatosVentas *ventas);
void MostrarVenta(struct Venta *venta);
struct NodoVenta *CrearNodoVenta(struct Venta *venta);
struct Venta *CrearVenta(struct Region *region, struct Sucursal *sucursal,
                         struct Auto *mAuto);

#endif //! VENTAS_H