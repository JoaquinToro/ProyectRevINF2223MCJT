#ifndef STOCK_H
#define STOCK_H

#include "autos.h"

#define maxAutos 100

struct Stock {
  int cantAutos;
  int pLibre;
  struct Auto **autos;
};

// Crea una estructura stock, asigna memoria para ella y para su arreglo de
// autos, de tamaño maximo 100.
struct Stock *CrearStock();

//
int AgregarStock(struct Stock *stock, struct Auto *nuevoAuto);
int EliminarStock(struct Stock *stock, int id);
void Compactar(struct Stock *stock, int indexInicio);
struct Auto *BuscarStock(struct Stock *stock, int id);
int ModificarStock(struct Stock *stock, int cantNueva);
void ListarStock(struct Stock *stock);

#endif //! STOCK_H