#ifndef AUTOS_H
#define AUTOS_H

struct NodoAuto {
  struct Auto *detalleauto;
  struct NodoAuto *sig;
};

struct Auto {
  int id;
  char *marca;
  char *modelo;
  int precio;
  int year;
  int recalls;
};

int AgregarAuto(struct NodoAuto **head, struct NodoAuto *nuevoAuto);
int EliminarAuto(struct NodoAuto **head, int id);
struct NodoAuto *BuscarAuto(struct NodoAuto *head, int id);
void ModificarAuto(struct Auto *mAuto);
void ListarAutos(struct NodoAuto *head);
void MostrarAuto(struct Auto *mAuto);
struct NodoAuto *CrearNodoAuto();
struct Auto *CrearAuto();

#endif //! AUTOS_H