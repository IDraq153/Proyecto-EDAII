CYBERSHIELD - GUIA RAPIDA
=========================

Que hace: lee alertas de seguridad, junta las del mismo incidente,
suma su gravedad y arma un ranking del mas grave al menos grave.

Palabras clave:
- Struct: solo guarda datos (como un formulario).
- Clase: guarda datos y sabe hacer acciones (como una maquina con botones).
- .h = lista de lo que tiene y hace. .cpp = como lo hace.


CARPETAS
--------
codigo/         El programa (.h y .cpp).
datos_prueba/   Archivos de alertas para probar.
resultados/     Ranking y metricas de cada prueba.

Sueltos: informe.pdf (el informe) y README.txt (como compilar y ejecutar).


ARCHIVOS DE codigo/
-------------------

incidente.h      STRUCT Incidente
  Guarda: ID, cantidad de alertas, prioridad total, puntero al siguiente.
  Acciones: ninguna.

metricas.h       STRUCT Metricas
  Guarda: sondeos_hash, comparaciones_heap, intercambios_heap.
  Acciones: ninguna.

tabla_hash.h/.cpp   CLASE TablaHash
  Guarda: los casilleros, cuantos hay, cuantos incidentes tiene.
  Acciones: registrar alerta (busca y suma, o crea), agrandar la tabla,
  recorrer todos los incidentes, liberar memoria.

max_heap.h/.cpp     CLASE MaxHeap
  Guarda: el arreglo de incidentes, su capacidad, cuantos hay.
  Acciones: insertar, sacar el mayor, ver si esta vacio, subir, bajar,
  comparar (mayor prioridad gana; si empatan, gana el ID menor).

lector_csv.h/.cpp   CLASE LectorCSV
  Guarda: el archivo abierto.
  Acciones: abrir, leer la siguiente alerta, avisar cuando termina.

main.cpp            Sin clase, solo la funcion main
  Coordina en orden: lee argumentos, lee el archivo, junta en la hash,
  pasa al heap, saca en orden, mide tiempo, escribe ranking.csv y
  metricas.txt.


QUIEN USA A QUIEN
-----------------
TablaHash y MaxHeap usan Incidente y reciben Metricas para contar.
main crea cada pieza y las conecta.