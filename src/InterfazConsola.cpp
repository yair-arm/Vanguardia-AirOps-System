#include "InterfazConsola.h"
#include "Aerolinea.h"
#include "Avion.h"
#include "Vuelo.h"
#include <iostream>

const int MAX_AVIONES = 100;

InterfazConsola::InterfazConsola() : gestor("datos.json"), numAviones(0) {
    aerolineas[0] = nullptr;
    aerolineas[1] = nullptr;
    aerolineas[2] = nullptr;

    aviones = new Avion*[MAX_AVIONES];
    for (int i = 0; i < MAX_AVIONES; i++) {
        aviones[i] = nullptr;
    }

    if (!gestor.cargarDatos(aerolineas, aviones, numAviones)) {
        std::cout << "No se pudo cargar datos.json (verifique que exista y sea valido).\n";
    }
}

InterfazConsola::~InterfazConsola() {
    gestor.guardarDatos(aerolineas, aviones, numAviones);

    for (int i = 0; i < 3; i++) {
        delete aerolineas[i];
    }
    for (int i = 0; i < numAviones; i++) {
        delete aviones[i];
    }
    delete[] aviones;
}

Avion* InterfazConsola::buscarAvion(std::string id) const {
    for (int i = 0; i < numAviones; i++) {
        if (aviones[i] != nullptr && aviones[i]->getId() == id) {
            return aviones[i];
        }
    }
    return nullptr;
}

void InterfazConsola::mostrarItinerarios() {
    for (int i = 0; i < 3; i++) {
        if (aerolineas[i] != nullptr) {
            std::cout << aerolineas[i]->mostrarInformacion() << "\n";
        }
    }
}

void InterfazConsola::cancelarVuelo() {
    int aero, dia, pos;
    std::cout << "Aerolinea (0-2): ";
    std::cin >> aero;
    std::cout << "Dia: ";
    std::cin >> dia;
    std::cout << "Posicion: ";
    std::cin >> pos;

    if (aero < 0 || aero >= 3 || aerolineas[aero] == nullptr) {
        std::cout << "Aerolinea invalida.\n";
        return;
    }

    if (aerolineas[aero]->eliminarVuelo(dia, pos)) {
        std::cout << "Vuelo cancelado.\n";
        gestor.guardarDatos(aerolineas, aviones, numAviones);
    } else {
        std::cout << "No hay vuelo en esa posicion (o indice invalido).\n";
    }
}

void InterfazConsola::modificarVuelo() {
    int aero, dia, pos;
    std::cout << "Aerolinea (0-2): ";
    std::cin >> aero;
    std::cout << "Dia: ";
    std::cin >> dia;
    std::cout << "Posicion: ";
    std::cin >> pos;

    if (aero < 0 || aero >= 3 || aerolineas[aero] == nullptr) {
        std::cout << "Aerolinea invalida.\n";
        return;
    }

    std::string origen, destino, horario, avionId;
    std::cout << "Nuevo origen: ";
    std::cin >> origen;
    std::cout << "Nuevo destino: ";
    std::cin >> destino;
    std::cout << "Nuevo horario: ";
    std::cin >> horario;
    std::cout << "Nuevo avion (id): ";
    std::cin >> avionId;

    Avion* avion = buscarAvion(avionId);
    if (avion == nullptr) {
        std::cout << "Avion no encontrado en la flota.\n";
        return;
    }

    if (!aerolineas[aero]->eliminarVuelo(dia, pos)) {
        std::cout << "No hay vuelo en esa posicion (o indice invalido).\n";
        return;
    }

    Vuelo* nuevoVuelo = new Vuelo(origen, destino, horario, avion);
    aerolineas[aero]->agregarVuelo(dia, pos, nuevoVuelo);
    std::cout << "Vuelo modificado.\n";
    gestor.guardarDatos(aerolineas, aviones, numAviones);
}

void InterfazConsola::iniciarMenu() {
    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\n==========================================\n";
        std::cout << "  VANGUARDIA AIR-OPS - Aeropuerto VVC\n";
        std::cout << "==========================================\n";
        std::cout << "  1. Ver itinerarios\n";
        std::cout << "  2. Modificar vuelo\n";
        std::cout << "  3. Cancelar vuelo\n";
        std::cout << "  0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarItinerarios();
                break;
            case 2:
                modificarVuelo();
                break;
            case 3:
                cancelarVuelo();
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
}