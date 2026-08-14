# Informe de validación de memoria y persistencia

> Estado: PENDIENTE — se completa en la Fase 4 del backlog, una vez implementado y compilado el proyecto.

## Objetivo

Verificar que el sistema:

1. No presenta fugas de memoria (todo `new` tiene su `delete`).
2. No presenta accesos inválidos (doble `delete`, uso de punteros liberados).
3. Persiste correctamente: guardar → recargar produce un estado idéntico.

## 1. Compilación

| Herramienta | Resultado | Observaciones |
|---|---|---|
| g++ (C++17) | ⏳ Pendiente | Comando: `g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o aerolineas` |
| AddressSanitizer | ⏳ Pendiente | Comando: `g++ -std=c++17 -fsanitize=address -g -Iinclude main.cpp src/*.cpp -o aerolineas_asan` |
| Valgrind | ⏳ Pendiente | `valgrind --leak-check=full ./aerolineas` |

## 2. Escenarios de prueba

| # | Escenario | Resultado esperado |
|---|---|---|
| 1 | Arranque con `datos.json` válido | Carga flota + 3 aerolíneas, menú operativo |
| 2 | Carga con archivo inexistente | `cargarDatos` retorna `false`, aviso al usuario |
| 3 | Ver itinerarios | Impresión correcta con posiciones `nullptr` como "Libre" |
| 4 | Modificar vuelo (cambiar avión) | `getPasajeros()` refleja la nueva capacidad |
| 5 | Cancelar vuelo | Posición en `nullptr`; avión sigue disponible para otro vuelo |
| 6 | Índices fuera de rango | Rechazados sin crash |
| 7 | Guardar → cerrar → recargar | Estado idéntico al guardado |
| 8 | Salida normal | Sin fugas ni dobles `delete` |

## 3. Resultados

| Herramienta | Escenario | Resultado | Observaciones |
|---|---|---|---|
| — | — | ⏳ Pendiente | — |

## 4. Correcciones registradas

| Fecha | Problema | Solución |
|---|---|---|
| — | — | — |

## Conclusión

⏳ Pendiente de ejecución.