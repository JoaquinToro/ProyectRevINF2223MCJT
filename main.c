#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autos.h"
#include "regiones.h"
#include "stock.h"
#include "sucursales.h"
#include "utilidades.h"
#include "ventas.h"

#define NoEncontrado printf("No se encuentra en el sistema\n\n")

#define Exito printf("Se realizó la operacion con éxito\n\n")
#define Fallo printf("Hubo un fallo y no se pudo realizar\n\n")

struct Derco {
  struct NodoAuto *autos;
  struct DatosVentas *datosVentas;
  struct NodoRegion *regiones;
} * derco;

////////////////////////////////////marcas de auto vendidos por
/// region////////////////////////////////////////

void MarcasEnVentas(struct NodoVenta *ventas, struct NodoCaracteres **marcas) {
  if (ventas == NULL) {
    return;
  }

  MarcasEnVentas(ventas->izq, marcas);
  if (BuscarNodoCaracteres(*marcas,
                           ventas->detalleVenta->autoComprado->marca) == 1) {
    *marcas = AgregarNodoCaracteres(*marcas,
                                    ventas->detalleVenta->autoComprado->marca);
  }
  MarcasEnVentas(ventas->der, marcas);
}

struct NodoCaracteres *MarcasDeAutoVendidosPorRegion(struct Region *region) {
  struct NodoCaracteres *marcas = NULL;
  MarcasEnVentas(derco->datosVentas->ventas, &marcas);
  return marcas;
}

/////////////////////////////////////////modelos de auto vendidos por
/// region//////////////////////////////////////////

void ModelosEnVentas(struct NodoVenta *ventas,
                     struct NodoCaracteres **modelos) {
  if (ventas == NULL) {
    return;
  }

  ModelosEnVentas(ventas->izq, modelos);
  if (BuscarNodoCaracteres(*modelos,
                           ventas->detalleVenta->autoComprado->modelo) == 1) {
    *modelos = AgregarNodoCaracteres(
        *modelos, ventas->detalleVenta->autoComprado->modelo);
  }
  ModelosEnVentas(ventas->der, modelos);
}

struct NodoCaracteres *ModelosDeAutoVendidosPorRegion(struct Region *region) {
  struct NodoCaracteres *modelos = NULL;
  ModelosEnVentas(derco->datosVentas->ventas, &modelos);
  return modelos;
}

/////////////////////////////////////////cliente que mas ha
/// gastado///////////////////////////////////////////

void ClientesEnVentas(struct NodoVenta *ventas, struct NodoCaracteres **ruts) {
  if (ventas == NULL) {
    return;
  }

  ClientesEnVentas(ventas->izq, ruts);
  if (BuscarNodoCaracteres(*ruts, ventas->detalleVenta->rutCliente) == 1) {
    *ruts = AgregarNodoCaracteres(*ruts, ventas->detalleVenta->rutCliente);
  }
  ClientesEnVentas(ventas->der, ruts);
}

void DineroGastadoPorCliente(struct NodoVenta *ventas, char *rutCliente,
                             int *contador) {
  if (ventas == NULL) {
    return;
  }

  DineroGastadoPorCliente(ventas->izq, rutCliente, contador);
  if (strcmp(ventas->detalleVenta->rutCliente, rutCliente) == 0) {
    (*contador) += ventas->detalleVenta->precio;
  }
  DineroGastadoPorCliente(ventas->der, rutCliente, contador);
}

char *ClienteQueMasHaGastado() {
  struct NodoCaracteres *rutClientes = NULL, *rec;
  int dineroGastado, mayor = 0;
  char *rutCliente = NULL;

  ClientesEnVentas(derco->datosVentas->ventas, &rutClientes);

  rec = rutClientes;

  while (rec != NULL) {
    dineroGastado = 0;

    DineroGastadoPorCliente(derco->datosVentas->ventas, rec->caracteres,
                            &dineroGastado);

    if (dineroGastado > mayor || rutCliente == NULL) {
      rutCliente = rec->caracteres;
      mayor = dineroGastado;
    }

    rec = rec->sig;
  }

  return rutCliente;
}

//////////////////////////////////////sucursal con mas
/// ventas///////////////////////////////////////////

void EncontrarSucursalEnVentas(struct NodoVenta *ventas, int id,
                               struct Sucursal **sucursal) {
  if (ventas == NULL || *sucursal != NULL) {
    return;
  }

  EncontrarSucursalEnVentas(ventas->izq, id, sucursal);
  if (ventas->detalleVenta->sucursal->id == id) {
    *sucursal = ventas->detalleVenta->sucursal;
    return;
  }
  EncontrarSucursalEnVentas(ventas->der, id, sucursal);
}

void SucursalesEnVentas(struct NodoVenta *ventas, struct NodoEntero **ids) {
  if (ventas == NULL) {
    return;
  }

  SucursalesEnVentas(ventas->izq, ids);
  if (BuscarNodoEntero(*ids, ventas->detalleVenta->sucursal->id) == 1) {
    *ids = AgregarNodoEntero(*ids, ventas->detalleVenta->sucursal->id);
  }
  SucursalesEnVentas(ventas->der, ids);
}

void ContarSucursalEnVentas(struct NodoVenta *ventas, int idSucursal,
                            int *contador) {
  if (ventas == NULL) {
    return;
  }

  ContarSucursalEnVentas(ventas->izq, idSucursal, &(*contador));
  if (ventas->detalleVenta->sucursal->id == idSucursal) {
    (*contador)++;
  }
  ContarSucursalEnVentas(ventas->der, idSucursal, &(*contador));
}

struct Sucursal *SucursalConMayorDistribucion() {
  struct NodoEntero *idSucursales = NULL, *rec;
  struct Sucursal *sucursal = NULL;
  int apariciones, mayor = 0, idMayor = -1;

  SucursalesEnVentas(derco->datosVentas->ventas, &idSucursales);

  rec = idSucursales;

  while (rec != NULL) {
    apariciones = 0;

    ContarSucursalEnVentas(derco->datosVentas->ventas, rec->entero,
                           &apariciones);

    if (apariciones > mayor || idMayor == -1) {
      idMayor = rec->entero;
      mayor = apariciones;
    }

    rec = rec->sig;
  }

  EncontrarSucursalEnVentas(derco->datosVentas->ventas, idMayor, &sucursal);

  return sucursal;
}

/////////////////////////////////////auto con mas
/// recalls////////////////////////////////////////

struct Auto *AutoConMasRecalls(struct NodoAuto *head) {
  if (head == NULL) {
    return NULL;
  }

  struct NodoAuto *rec = head;
  struct Auto *mAuto = NULL;
  int masRecalls;

  do {
    if (mAuto == NULL || rec->detalleauto->recalls > masRecalls) {
      mAuto = rec->detalleauto;
      masRecalls = mAuto->recalls;
    }
    rec = rec->sig;
  } while (rec != head);

  return mAuto;
}

///////////////////////////////////////////////////////////////
/// EXTRAS//////////////////////////////////////////////////////////////////

int TotalSucursales(struct NodoSucursal *abb) {
  if (!abb) {
    return 0;
  }
  return 1 + TotalSucursales(abb->izq) + TotalSucursales(abb->der);
}

float PromedioSucursalesPorRegion(struct Derco *derco) {
  if (derco->regiones == NULL)
    return 0;

  int contadorRegiones = 0, contSucursales = 0;

  struct NodoRegion *rec = derco->regiones;
  struct NodoSucursal *recSucursal = NULL;

  while (rec != NULL) {
    recSucursal = rec->detalleregion->sucursales;
    contSucursales += TotalSucursales(recSucursal);
    contadorRegiones++;
    rec = rec->sig;
  }
  if (contadorRegiones == 0)
    return 0;

  return (float)contSucursales / contadorRegiones;
}

void ContarComprasEnAbbIn(struct NodoVenta *abb, char *rutComprador,
                          int *compras) {
  if (abb) {
    ContarComprasEnAbbIn(abb->izq, rutComprador, compras);
    if (strcmp(abb->detalleVenta->rutCliente, rutComprador) == 0)
      (*compras)++;
    ContarComprasEnAbbIn(abb->der, rutComprador, compras);
  }
  return;
}

int ComprasDeUnCliente(struct NodoVenta *abb, char *rutClienteB) {
  if (derco == NULL || derco->datosVentas == NULL)
    return 0;
  int contCompras = 0;
  ContarComprasEnAbbIn(abb, rutClienteB, &(contCompras));
  return contCompras;
}

///////////////////////////////////////////////////////////////
/// MENU//////////////////////////////////////////////////////////////////
void PedirFuncionesBasicas() {
  printf("¿Qué desea hacer?\n");
  printf("Presione 0 para regresar\n");
  printf("Presione 1 para buscar\n");
  printf("Presione 2 para listar todos los elementos\n");
  printf("Presione 3 para agregar\n");
  printf("Presione 4 para eliminar\n");
  printf("Presione 5 para modificar\n");
  return;
}

void MenuStock(struct Stock *vehiculos) {
  int min = 0, max = 6, entrada;

  do {
    limpiarConsola;
    printf("MENU STOCK:\n\n");
    PedirFuncionesBasicas();
    printf("\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      struct Auto *autoBuscado =
          BuscarStock(vehiculos, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (autoBuscado != NULL)
        MostrarAuto(autoBuscado);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {

      ListarStock(vehiculos);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      struct NodoAuto *nodoAuto =
          BuscarAuto(derco->autos, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (nodoAuto == NULL)
        Fallo;
      else {
        int agregar = AgregarStock(vehiculos, nodoAuto->detalleauto);

        if (agregar == 0)
          Exito;
        else
          Fallo;

        printf("Presione enter para continuar.");
        limpiarInputBuffer;
      }
    } else if (entrada == 4) {
      int eliminar =
          EliminarStock(vehiculos, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (eliminar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      int modificar = ModificarStock(
          vehiculos,
          EnterInteger(0, maxAutos, "Ingrese la nueva cantidad de stock: "));

      if (modificar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    }
  } while (entrada != 0);
}

void MenuSucursales(struct Region *region) {
  int min = 0, max = 6, entrada;

  do {
    limpiarConsola;
    printf("MENU SUCURSALES:\n\n");
    PedirFuncionesBasicas();
    printf("Presione 6 para acceder a los vehículos de una sucursal\n\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      struct NodoSucursal *sucursalBuscada = BuscarSucursal(
          region->sucursales, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (sucursalBuscada != NULL)
        MostrarSucursal(sucursalBuscada->detallesucursal);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {

      ListarSucursales(region->sucursales);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      int agregar = AgregarSucursal(&(region->sucursales),
                                    CrearNodoSucursal(CrearSucursal()));

      if (agregar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 4) {
      int eliminar = EliminarSucursal(
          &(region->sucursales), EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (eliminar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      struct NodoSucursal *sucursalAM = BuscarSucursal(
          region->sucursales, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (sucursalAM != NULL)
        ModificarSucursal(sucursalAM->detallesucursal);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 6) {
      printf("¿Sobre qué sucursal desea trabajar?\n\n");

      struct NodoSucursal *sucursal = BuscarSucursal(
          region->sucursales, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (sucursal != NULL)
        MenuStock(sucursal->detallesucursal->vehiculos);
      else {
        NoEncontrado;
        printf("Presione enter para continuar.");
        limpiarInputBuffer;
      }
    }
  } while (entrada != 0);
}

void MenuRegiones() {
  int min = 0, max = 6, entrada;

  do {
    limpiarConsola;
    printf("MENU REGIONES:\n\n");
    PedirFuncionesBasicas();
    printf("Presione 6 para acceder a las sucursales de una región\n\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      struct NodoRegion *regionBuscada = BuscarRegion(
          derco->regiones,
          EnterInteger(0, POSINF, "Ingrese el número de la region: "));

      if (regionBuscada != NULL)
        MostrarRegion(regionBuscada->detalleregion);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {

      ListarRegiones(derco->regiones);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      int agregar =
          AgregarRegion(&(derco->regiones), CrearNodoRegion(CrearRegion()));

      if (agregar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 4) {
      int eliminar = EliminarRegion(
          &(derco->regiones),
          EnterInteger(0, POSINF, "Ingrese el número de la region: "));

      if (eliminar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      struct NodoRegion *regionAM = BuscarRegion(
          derco->regiones,
          EnterInteger(0, POSINF, "Ingrese el número de la region: "));

      if (regionAM != NULL)
        ModificarRegion(regionAM->detalleregion);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 6) {
      printf("¿Sobre qué región desea trabajar?\n\n");

      struct NodoRegion *region =
          BuscarRegion(derco->regiones, EnterInteger(1, 16, "Ingrese el ID: "));

      if (region != NULL)
        MenuSucursales(region->detalleregion);
      else {
        NoEncontrado;
        printf("Presione enter para continuar.");
        limpiarInputBuffer;
      }
    }
  } while (entrada != 0);
}

void MenuVentas() {
  int min = 0, max = 5, entrada;

  do {
    limpiarConsola;
    printf("MENU VENTAS:\n\n");
    PedirFuncionesBasicas();
    printf("\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      struct NodoVenta *ventaBuscado =
          BuscarVenta(derco->datosVentas->ventas,
                      EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (ventaBuscado != NULL)
        MostrarVenta(ventaBuscado->detalleVenta);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {

      ListarVentas(derco->datosVentas);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      printf("¿En que region se encuentra la venta?\n");
      struct NodoRegion *region = BuscarRegion(
          derco->regiones, EnterInteger(0, POSINF, "Ingrese el ID: "));
      if (region == NULL)
        NoEncontrado;
      else {
        printf("¿Qué sucursal desea escoger?\n");
        struct NodoSucursal *sucursal =
            BuscarSucursal(region->detalleregion->sucursales,
                           EnterInteger(0, POSINF, "Ingrese el ID: "));
        if (sucursal == NULL)
          NoEncontrado;
        else {
          printf("¿Que auto desea comprar?\n");
          struct Auto *mAuto =
              BuscarStock(sucursal->detallesucursal->vehiculos,
                          EnterInteger(0, POSINF, "Ingrese el ID: "));
          if (mAuto == NULL)
            NoEncontrado;
          else {
            int agregar = AgregarVenta(
                derco->datosVentas,
                CrearNodoVenta(CrearVenta(region->detalleregion,
                                          sucursal->detallesucursal, mAuto)));
            if (agregar == 0) {
              EliminarStock(sucursal->detallesucursal->vehiculos, mAuto->id);
              Exito;
            } else
              Fallo;
          }
        }
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 4) {
      int eliminar = EliminarVenta(derco->datosVentas,
                                   EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (eliminar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      struct NodoVenta *nodoVenta =
          BuscarVenta(derco->datosVentas->ventas,
                      EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (nodoVenta != NULL)
        ModificarVenta(nodoVenta->detalleVenta, derco->regiones);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    }
  } while (entrada != 0);
}

void MenuAutos() {
  int min = 0, max = 5, entrada;

  do {
    limpiarConsola;
    printf("MENU AUTOS:\n\n");
    PedirFuncionesBasicas();
    printf("\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      struct NodoAuto *autoBuscado =
          BuscarAuto(derco->autos, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (autoBuscado != NULL)
        MostrarAuto(autoBuscado->detalleauto);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {

      ListarAutos(derco->autos);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      int agregar = AgregarAuto(&(derco->autos), CrearNodoAuto(CrearAuto()));
      if (agregar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 4) {
      int eliminar = EliminarAuto(&(derco->autos),
                                  EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (eliminar == 0)
        Exito;
      else
        Fallo;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      struct NodoAuto *nodoAuto =
          BuscarAuto(derco->autos, EnterInteger(0, POSINF, "Ingrese el ID: "));

      if (nodoAuto != NULL)
        ModificarAuto(nodoAuto->detalleauto);
      else
        NoEncontrado;

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    }
  } while (entrada != 0);
}

void Funciones() {
  int min = 0, max = 8, entrada;

  do {
    limpiarConsola;
    printf("MENU FUNCIONES:\n\n");
    printf("Presione 0 para retroceder\n");
    printf("Presione 1 si desea saber el total de sucursales de una región\n");
    printf("Presione 2 si desea saber el promedio de sucursales por región\n");
    printf("Presione 3 si desea saber la cantidad de compras de un cliente\n");
    printf("Presione 4 si desea saber el auto con mas recalls\n");
    printf("Presione 5 si desea saber la sucursal con mas ventas\n");
    printf("Presione 6 si desea saber el cliente que mas ha gastado\n");
    printf("Presione 7 si desea saber los modelos de autos vendidos en una "
           "región\n");
    printf("Presione 8 si desea saber las marcas de autos vendidos en una "
           "región\n\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {
      printf("¿En qué región desea buscar?\n\n");

      int idRegion = EnterInteger(0, POSINF, "Ingrese el ID: ");
      struct NodoRegion *nodoRegion = BuscarRegion(derco->regiones, idRegion);
      if (nodoRegion == NULL)
        printf("No hay datos\n\n");
      else {
        int numeroDeSucursales =
            TotalSucursales(nodoRegion->detalleregion->sucursales);
        printf("En la región de \"%s\" hay un total de %d sucursales\n\n",
               nodoRegion->detalleregion->nombre, numeroDeSucursales);
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 2) {
      float promedioSucursales = PromedioSucursalesPorRegion(derco);
      printf("El promedio de sucursales por región es de %.2f sucursales por "
             "región\n\n",
             promedioSucursales);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 3) {
      char *rutBuscado = EnterText("Ingrese el rut del cliente: ");
      int compras = ComprasDeUnCliente(derco->datosVentas->ventas, rutBuscado);
      if (compras == 0)
        printf("El cliente no tiene compras en el sistema\n\n");
      else
        printf("La cantidad de compras del cliente es de %d compras\n\n",
               compras);

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 4) {
      struct Auto *mAuto = AutoConMasRecalls(derco->autos);

      if (mAuto != NULL) {
        MostrarAuto(mAuto);
      } else {
        printf("No existen autos.");
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 5) {
      struct Sucursal *sucursal = SucursalConMayorDistribucion();

      if (sucursal != NULL) {
        MostrarSucursal(sucursal);
      } else {
        printf("No existen ventas.\n\n");
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 6) {
      char *cliente = ClienteQueMasHaGastado();

      if (cliente != NULL) {
        printf("El rut del cliente que mas ha gastado es: %s\n\n", cliente);
      } else {
        printf("No existen ventas.\n\n");
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 7) {
      printf("¿Que región desea escoger?\n\n");
      struct NodoRegion *region =
          BuscarRegion(derco->regiones, EnterInteger(1, 16, "Ingrese el id: "));

      if (region == NULL) {
        NoEncontrado;
      } else {
        struct NodoCaracteres *modelos =
            ModelosDeAutoVendidosPorRegion(region->detalleregion);

        if (modelos != NULL) {
          printf("Modelos de auto en la region de \"%s\":\n\n",
                 region->detalleregion->nombre);
          PrintListaCaracteres(modelos);
        } else {
          printf("No existen ventas.\n\n");
        }
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    } else if (entrada == 8) {
      printf("¿Que región desea escoger?\n\n");
      struct NodoRegion *region =
          BuscarRegion(derco->regiones, EnterInteger(1, 16, "Ingrese el id: "));

      if (region == NULL) {
        NoEncontrado;
      } else {
        struct NodoCaracteres *marcas =
            MarcasDeAutoVendidosPorRegion(region->detalleregion);

        if (marcas != NULL) {
          printf("Marcas de auto en la region de \"%s\":\n\n",
                 region->detalleregion->nombre);
          PrintListaCaracteres(marcas);
        } else {
          printf("No existen ventas.\n\n");
        }
      }

      printf("Presione enter para continuar.");
      limpiarInputBuffer;
    }
  } while (entrada != 0);
}

void MenuDerco() {
  int min = 0, max = 4, entrada;

  do {
    printf("MENU DERCO:\n\n");
    printf("Presione 0 para salir del programa\n");
    printf("Presione 1 para acceder a los autos\n");
    printf("Presione 2 para acceder a las ventas\n");
    printf("Presione 3 para acceder a las regiones\n");
    printf("Presione 4 para acceder a las funciones extras\n\n");

    entrada = EnterInteger(min, max, "Ingrese la opcion que desea ejecutar: ");

    if (entrada == 1) {

      MenuAutos();

    } else if (entrada == 2) {

      MenuVentas();

    } else if (entrada == 3) {

      MenuRegiones();

    } else if (entrada == 4) {

      Funciones();
    }
    limpiarConsola;
  } while (entrada != 0);
}

struct Derco *CrearDerco() {
  struct Derco *derco;
  derco = (struct Derco *)malloc(sizeof(struct Derco));

  derco->autos = NULL;
  derco->datosVentas = CrearDatosVentas();
  derco->regiones = NULL;

  return derco;
}

int main() {
  derco = CrearDerco();
  printf("Bienvenido\n\n");
  MenuDerco();
  return 0;
}