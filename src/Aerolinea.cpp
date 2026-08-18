#include "Aerolinea.h"
#include "Vuelo.h"
#include "Avion.h"
#include <sstream>

Aerolinea::Aerolinea(std::string nombre, int numDias, std::string* nombreDias, int* vuelosPorDia) : nombre(nombre), numDias(numDias), nombreDias(nombreDias), vuelosPorDia(vuelosPorDia) {
    itinerario = new Vuelo**[numDias];
    for (int i = 0; i < numDias; i++) {
        itinerario[i] = new Vuelo*[vuelosPorDia[i]];
        for (int j = 0; j < vuelosPorDia[i]; j++) {
            itinerario[i][j] = nullptr;
        }
    }
}

Aerolinea::~Aerolinea() {
    for (int i = 0; i < numDias; i++) {
        for (int j = 0; j < vuelosPorDia[i]; j++) {
            delete itinerario[i][j];
        }
        delete[] itinerario[i];
    }
    delete[] itinerario;
    delete[] nombreDias;
    delete[] vuelosPorDia;
}

bool Aerolinea::agregarVuelo(int diaIdx, int vueloIdx, Vuelo* vuelo) {
    if (diaIdx < 0 || diaIdx >= numDias) {
        return false;
    }
    if (vueloIdx < 0 || vueloIdx >= vuelosPorDia[diaIdx]) {
        return false;
    }
    if (itinerario[diaIdx][vueloIdx] != nullptr) {
        return false;
    }
    itinerario[diaIdx][vueloIdx] = vuelo;
    return true;
}

bool Aerolinea::eliminarVuelo(int diaIdx, int vueloIdx) {
    if (diaIdx < 0 || diaIdx >= numDias) {
        return false;
    }
    if (vueloIdx < 0 || vueloIdx >= vuelosPorDia[diaIdx]) {
        return false;
    }
    if (itinerario[diaIdx][vueloIdx] == nullptr) {
        return false;
    }
    delete itinerario[diaIdx][vueloIdx];
    itinerario[diaIdx][vueloIdx] = nullptr;
    return true;
}

std::string Aerolinea::mostrarInformacion() const {
    std::ostringstream out;
    out << "Aerolinea: " << nombre << " (" << numDias << " dias)\n";
    for (int d = 0; d < numDias; d++) {
        out << nombreDias[d] << ":\n";
        for (int v = 0; v < vuelosPorDia[d]; v++) {
            Vuelo* vuelo = itinerario[d][v];
            if (vuelo == nullptr) {
                out << "  [" << v << "] Libre\n";
            } else {
                out << "  [" << v << "] " << vuelo->getOrigen() << " -> " << vuelo->getDestino()
                    << " | " << vuelo->getHorario() << " | ";
                Avion* avion = vuelo->getAvionAsignado();
                if (avion != nullptr) {
                    out << avion->getId() << " | " << vuelo->getPasajeros() << " pasajeros";
                } else {
                    out << "Sin avion";
                }
                out << "\n";
            }
        }
    }
    return out.str();
}

