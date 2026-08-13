# Especificación del archivo JSON

Formato de datos del sistema Vanguardia AirOps. El archivo se carga al iniciar (`GestorJSON::cargarDatos`) y se reescribe tras cada operación que modifique el estado (`GestorJSON::guardarDatos`).

## Estructura general

El archivo tiene **dos secciones de nivel superior**:

| Sección | Tipo | Descripción |
|---|---|---|
| `aviones` | arreglo | Flota global, compartida por todas las aerolíneas |
| `aerolineas` | arreglo | Las 3 aerolíneas con su agenda semanal |

## Sección `aviones`

Cada elemento:

| Campo | Tipo | Descripción |
|---|---|---|
| `id` | string | Identificador único del avión (ej. `"AV-001"`) |
| `modelo` | string | Modelo de la aeronave |
| `capacidad` | int | Capacidad máxima de pasajeros |

## Sección `aerolineas`

Cada elemento:

| Campo | Tipo | Descripción |
|---|---|---|
| `nombre` | string | Nombre de la aerolínea |
| `dias` | arreglo de string | Nombres de los días de operación |
| `vuelosPorDia` | arreglo de int | Cantidad máxima de vuelos por cada día (mismo orden que `dias`) |
| `itinerario` | arreglo de arreglos | Matriz día x vuelo; cada celda es un vuelo o `null` |

### Celda de `itinerario`

| Campo | Tipo | Descripción |
|---|---|---|
| `origen` | string | Ciudad de origen |
| `destino` | string | Ciudad de destino |
| `horario` | string | Hora de salida (ej. `"06:00"`) |
| `avionId` | string | Referencia a un avión de la sección `aviones` |

- `null` en una celda indica espacio libre (sin vuelo asignado).
- `avionId` debe existir en `aviones`; `GestorJSON` lo resuelve contra la flota al cargar.

## Ejemplo

```json
{
  "aviones": [
    { "id": "AV-001", "modelo": "Airbus A320", "capacidad": 180 },
    { "id": "ST-101", "modelo": "ATR 42-600", "capacidad": 48 },
    { "id": "CL-201", "modelo": "Let L-410", "capacidad": 19 }
  ],
  "aerolineas": [
    {
      "nombre": "Avianca",
      "dias": ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes"],
      "vuelosPorDia": [2, 2, 2, 2, 2],
      "itinerario": [
        [ { "origen": "VVC", "destino": "Bogota", "horario": "06:00", "avionId": "AV-001" }, null ],
        [ { "origen": "VVC", "destino": "Bogota", "horario": "18:00", "avionId": "AV-001" }, null ],
        [ null, null ],
        [ null, null ],
        [ null, null ]
      ]
    },
    {
      "nombre": "SATENA",
      "dias": ["Lunes", "Miercoles", "Viernes"],
      "vuelosPorDia": [2, 2, 2],
      "itinerario": [
        [ { "origen": "VVC", "destino": "Mitu", "horario": "07:30", "avionId": "ST-101" }, null ],
        [ { "origen": "VVC", "destino": "Puerto Carreno", "horario": "10:00", "avionId": "ST-101" }, null ],
        [ { "origen": "VVC", "destino": "Inirida", "horario": "14:00", "avionId": "ST-101" }, null ]
      ]
    },
    {
      "nombre": "Clic Air",
      "dias": ["Sabado"],
      "vuelosPorDia": [3],
      "itinerario": [
        [ { "origen": "VVC", "destino": "Medellin", "horario": "08:00", "avionId": "CL-201" }, null, null ]
      ]
    }
  ]
}
```

## Reglas

- El orden de carga importa: primero `aviones`, luego `aerolineas` (para resolver `avionId`).
- `vuelosPorDia` debe tener la misma longitud que `dias`.
- La matriz `itinerario` debe tener una fila por día y `vuelosPorDia[dia]` columnas.
- Si el archivo no existe o es inválido, `cargarDatos` retorna `false`.