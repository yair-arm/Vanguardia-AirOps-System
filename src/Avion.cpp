#include "Avion.h"

Avion::Avion(std::string id, std::string modelo, int capacidad) : id(id), modelo(modelo), capacidad(capacidad) {}

std::string Avion::getId() const {
    return id;
}

std::string Avion::getModelo() const {
    return modelo;
}

int Avion::getCapacidad() const {
    return capacidad;
}

