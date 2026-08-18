#include "GestorJSON.h"
#include "Aerolinea.h"
#include "Avion.h"
#include "Vuelo.h"
#include "json.hpp" 
#include <fstream>
#include <iostream>

using json = nlohmann::json;

GestorJSON::GestorJSON(std::string ruta) : rutaArchivo(ruta) {}

bool GestorJSON::cargarDatos(Aerolinea* outAerolineas[], Avion* outAviones[], int& outNumAviones) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    json j = json::parse(archivo, nullptr, false);
    
    if (j.is_discarded()) {
        std::cerr << "Error al leer JSON: Formato incorrecto\n";
        return false;
    }

    outNumAviones = 0;
    if (j.contains("aviones") && j["aviones"].is_array()) {
        for (const auto& avionJson : j["aviones"]) {
            std::string id = avionJson["id"];
            std::string modelo = avionJson["modelo"];
            int capacidad = avionJson["capacidad"];
            
            outAviones[outNumAviones++] = new Avion(id, modelo, capacidad);
        }
    }

    int idxAero = 0;
    if (j.contains("aerolineas") && j["aerolineas"].is_array()) {
        for (const auto& aeroJson : j["aerolineas"]) {
            std::string nombre = aeroJson["nombre"];
            int numDias = aeroJson["dias"].size();
            
            std::string* nombreDias = new std::string[numDias];
            int* vuelosPorDia = new int[numDias];
            
            for (int d = 0; d < numDias; d++) {
                nombreDias[d] = aeroJson["dias"][d];
                vuelosPorDia[d] = aeroJson["vuelosPorDia"][d];
            }

            Aerolinea* aerolinea = new Aerolinea(nombre, numDias, nombreDias, vuelosPorDia);

            if (aeroJson.contains("itinerario") && aeroJson["itinerario"].is_array()) {
                for (int d = 0; d < numDias; d++) {
                    auto vuelosDiaJson = aeroJson["itinerario"][d];
                    for (int v = 0; v < vuelosPorDia[d]; v++) {
                        if (!vuelosDiaJson[v].is_null()) {
                            auto vueloJson = vuelosDiaJson[v];
                            std::string origen = vueloJson["origen"];
                            std::string destino = vueloJson["destino"];
                            std::string horario = vueloJson["horario"];
                            std::string avionId = vueloJson["avionId"];
                            
                            Avion* avionAsignado = nullptr;
                            for (int i = 0; i < outNumAviones; i++) {
                                if (outAviones[i]->getId() == avionId) {
                                    avionAsignado = outAviones[i];
                                    break;
                                }
                            }
                            
                            Vuelo* nuevoVuelo = new Vuelo(origen, destino, horario, avionAsignado);
                            aerolinea->agregarVuelo(d, v, nuevoVuelo);
                        }
                    }
                }
            }
            outAerolineas[idxAero++] = aerolinea;
        }
    }

    return true;
}

bool GestorJSON::guardarDatos(Aerolinea* aerolineas[], Avion* aviones[], int numAviones) {
    json j;

    j["aviones"] = json::array();
    for (int i = 0; i < numAviones; i++) {
        if (aviones[i] != nullptr) {
            j["aviones"].push_back({
                {"id", aviones[i]->getId()},
                {"modelo", aviones[i]->getModelo()},
                {"capacidad", aviones[i]->getCapacidad()}
            });
        }
    }

    j["aerolineas"] = json::array();
    for (int i = 0; i < 3; i++) { 
        if (aerolineas[i] == nullptr) continue;
        
        json aeroJson;

        aeroJson["nombre"] = aerolineas[i]->nombre;
        
        aeroJson["dias"] = json::array();
        aeroJson["vuelosPorDia"] = json::array();
        for (int d = 0; d < aerolineas[i]->numDias; d++) {
            aeroJson["dias"].push_back(aerolineas[i]->nombreDias[d]);
            aeroJson["vuelosPorDia"].push_back(aerolineas[i]->vuelosPorDia[d]);
        }

        aeroJson["itinerario"] = json::array();
        for (int d = 0; d < aerolineas[i]->numDias; d++) {
            json vuelosDiaJson = json::array();
            for (int v = 0; v < aerolineas[i]->vuelosPorDia[d]; v++) {
                Vuelo* vuelo = aerolineas[i]->itinerario[d][v];
                
                if (vuelo == nullptr) {
                    vuelosDiaJson.push_back(nullptr);
                } else {
                    json vueloJson;
                    vueloJson["origen"] = vuelo->getOrigen();
                    vueloJson["destino"] = vuelo->getDestino();
                    vueloJson["horario"] = vuelo->getHorario();
                    
                    Avion* avion = vuelo->getAvionAsignado();
                    vueloJson["avionId"] = avion ? avion->getId() : "";
                    
                    vuelosDiaJson.push_back(vueloJson);
                }
            }
            aeroJson["itinerario"].push_back(vuelosDiaJson);
        }
        
        j["aerolineas"].push_back(aeroJson);
    }

    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) return false;
    
    archivo << j.dump(2);
    return true;
}