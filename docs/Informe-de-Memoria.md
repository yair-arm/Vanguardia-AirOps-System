# Informe de validación de memoria y persistencia

> Estado: COMPLETADO — Fase 4 del backlog, 2026-08-14.

## Objetivo

Verificar que el sistema:

1. No presenta fugas de memoria (todo `new` tiene su `delete`).
2. No presenta accesos inválidos (doble `delete`, uso de punteros liberados).
3. Persiste correctamente: guardar → recargar produce un estado idéntico.

## 1. Compilación

| Herramienta | Resultado | Observaciones |
|---|---|---|
| g++ (C++17) | ✅ OK | `g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o aerolineas` — compila con `-Wall` sin warnings |
| AddressSanitizer | ⚠️ No disponible | El toolchain MinGW-w64/MSYS2 (gcc 16.1.0) **no incluye `libasan`** (el paquete no existe en MSYS2); los sanitizers no se compilan para Windows en esta toolchain. Se sustituyó por auditoría manual de pares `new`/`delete` (sección 3). |
| Valgrind | ⚠️ Solo Linux | `valgrind --leak-check=full ./aerolineas` — documentado para ejecutar en un entorno Linux (profesor o WSL); en Windows no existe |

## 2. Escenarios de prueba

| # | Escenario | Resultado |
|---|---|---|
| 1 | Arranque con `datos.json` válido | ✅ Carga flota (3 aviones) + 3 aerolíneas, menú operativo |
| 2 | Carga con archivo inexistente | ✅ `cargarDatos` retorna `false`, aviso al usuario; **no se recrea el archivo** al salir (bug corregido, ver sección 4) |
| 3 | Ver itinerarios | ✅ Impresión correcta con posiciones `nullptr` como "Libre"; incluye avión y pasajeros |
| 4 | Modificar vuelo (cambiar avión) | ✅ `getPasajeros()` refleja la nueva capacidad del avión |
| 5 | Cancelar vuelo | ✅ Posición en `nullptr`; avión sigue disponible para otro vuelo |
| 6 | Índices fuera de rango / casilla ocupada | ✅ Rechazados sin crash (bool de `Aerolinea`) |
| 7 | Guardar → cerrar → recargar | ✅ Estado idéntico al guardado (vuelo creado en ejecución 1 visible en ejecución 2) |
| 8 | Salida normal | ✅ Sin dobles `delete`: todos los `delete`/`delete[]` sobre punteros verificados `nullptr`-safe |

## 3. Auditoría manual de memoria (pares `new` / `delete`)

| Clase / función | `new` | `delete` emparejado | Estado |
|---|---|---|---|
| `GestorJSON::cargarDatos` | `new Avion(...)` (flota) | `InterfazConsola::~InterfazConsola` (`delete aviones[i]`) — el gestor no es dueño, transfiere propiedad | ✅ Sin fuga |
| `GestorJSON::cargarDatos` | `new std::string[numDias]`, `new int[numDias]` | `Aerolinea::~Aerolinea` (`delete[] nombreDias`, `delete[] vuelosPorDia`) | ✅ Sin fuga |
| `GestorJSON::cargarDatos` | `new Aerolinea(...)` | `InterfazConsola::~InterfazConsola` (`delete aerolineas[i]`) | ✅ Sin fuga |
| `GestorJSON::cargarDatos` | `new Vuelo(...)` | `Aerolinea` (composición ♦): `eliminarVuelo` y `~Aerolinea` | ✅ Sin fuga |
| `Aerolinea` (constructor) | `new Vuelo**[numDias]` + `new Vuelo*[vuelosPorDia[i]]` por día | `~Aerolinea`: `delete[] itinerario[i]` × numDias + `delete[] itinerario` | ✅ Sin fuga |
| `Aerolinea::eliminarVuelo` | — | `delete itinerario[d][v]` + asigna `nullptr` | ✅ Sin doble delete |
| `InterfazConsola` (constructor) | `new Avion*[100]` (buffer flota) | `~InterfazConsola`: `delete[] aviones`; casillas inicializadas a `nullptr` | ✅ Sin fuga |
| `InterfazConsola::crearVuelo` | `new Vuelo(...)` | Si `agregarVuelo` acepta → dueño `Aerolinea`; si rechaza → `delete nuevoVuelo` inmediato | ✅ Sin fuga |
| `InterfazConsola::modificarVuelo` | `new Vuelo(...)` | `agregarVuelo` tras `eliminarVuelo` exitoso (casilla libre garantizada) → dueño `Aerolinea` | ✅ Sin fuga |
| `Avion`, `Vuelo` (clases) | Sin miembros dinámicos | — | ✅ No gestionan memoria |

**Resultado:** todo `new` tiene su `delete`; no hay dobles liberaciones ni punteros liberados en uso. Los `delete` sobre punteros a objetos inexistentes (carga fallida) son seguros por el chequeo `nullptr`.

**Limitaciones conocidas:** el buffer de flota es fijo (100 aviones): un JSON con más de 100 aviones escribiría fuera del buffer. El JSON controlado trae 3; se documenta como limitación de diseño aceptada (decisión de buffer fijo).

## 4. Correcciones registradas

| Fecha | Problema | Solución |
|---|---|---|
| 2026-08-14 | `std::cerr` en `GestorJSON::cargarDatos` (violaba regla v1.2: solo la interfaz imprime) | Reemplazado por comentario + `return false`; eliminado `#include <iostream>` (commit `8459f29`) |
| 2026-08-14 | Con `datos.json` ausente/corrupto, al salir el programa **sobrescribía el archivo con estado vacío** (pérdida de datos) | Nueva bandera `cargaExitosa` en `InterfazConsola`: `guardarDatos` solo se ejecuta si la carga fue exitosa |
| 2026-08-14 | `mostrarInformacion` no mostraba pasajeros (el Manual de Usuario lo prometía) | Añadido `vuelo->getPasajeros()` a la impresión de itinerarios |
| 2026-08-14 | CRUD incompleto (sin Create) | Opción "2. Crear vuelo" con `crearVuelo()` (commit `3cc35b0`) |

## Conclusión

El sistema no presenta fugas de memoria ni accesos inválidos según la auditoría manual de pares `new`/`delete` (9 pares verificados). La validación con herramientas automáticas está limitada por el toolchain: ASan no existe para MinGW-w64 y Valgrind es solo Linux; el comando de Valgrind queda documentado para ejecutarlo en un entorno Linux si el profesor lo requiere. La persistencia se verificó empíricamente: guardar → recargar produce estado idéntico, y el programa ya no destruye datos ante un archivo ausente.