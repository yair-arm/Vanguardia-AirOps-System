#ifndef INTERFAZCONSOLA_H
#define INTERFAZCONSOLA_H

#include <string>
#include "GestorJSON.h"

class Aerolinea;
class Avion;

class InterfazConsola {
private:
    GestorJSON gestor;
    Aerolinea* aerolineas[3];
    Avion** aviones;
    int numAviones;

    void mostrarItinerarios();
    void crearVuelo();
    void modificarVuelo();
    void cancelarVuelo();
    Avion* buscarAvion(std::string id) const;

public:
    InterfazConsola();
    ~InterfazConsola();
    void iniciarMenu();
};

#endif