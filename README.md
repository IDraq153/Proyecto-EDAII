CYBERSHIELD - Proyecto final EDA II 
=========================================================

1. QUÉ HACE EL PROGRAMA
-----------------------
Lee un CSV de alertas de ciberseguridad (alerta_id,incidente_id,severidad),
agrupa las alertas por incidente (suma severidades y cuenta alertas) y genera
un ranking de incidentes: mayor prioridad_total primero; si hay empate, gana el
incidente_id menor (comparado como texto, ej. "INC-0000050").

Restricciones cumplidas: tabla hash y max-heap propios; no se usa vector, map,
unordered_map, priority_queue ni sort.


2. COMPILAR
-----------
Desde la carpeta raíz del proyecto (Git Bash o terminal con g++):

    g++ -std=c++17 -O2 codigo/*.cpp -o codigo/cybershield


3. EJECUTAR
-----------
    ./codigo/cybershield entrada.csv ranking.csv metricas.txt

Ejemplo:

    ./codigo/cybershield datos_prueba/1000data.csv resultados/1000data_ranking.csv resultados/1000data_metricas.txt

Salidas:
  - ranking.csv  -> cabecera: posicion,incidente_id,cantidad_alertas,prioridad_total
  - metricas.txt -> sondeos_hash, comparaciones_heap, intercambios_heap,
                    tiempo_proceso_ms


4. EJECUTAR TODAS LAS PRUEBAS
-----------------------------
    bash ejecutar_pruebas.sh

Compila, corre los casos oficiales (carpeta CyberShield_Pruebas_Estudiantes,
descomprimida dentro de esta carpeta) y los de datos_prueba/, guarda todo en
resultados/ y compara cada ranking con el esperado usando comparar.py.

Para comparar un caso a mano:

    python comparar.py esperado.csv resultado.csv


5. ESTRUCTURA DE CARPETAS
-------------------------
    codigo/          fuentes C++
    datos_prueba/    CSV propios de prueba
    resultados/      rankings y métricas generados
    ejecutar_pruebas.sh
    README.txt

Archivos de codigo/:
    main.cpp        flujo principal: lee, consolida, ordena, escribe salidas
    lector_csv.*    lee el CSV línea por línea (IDs se conservan como texto)
    incidente.h     struct Incidente (id, cantidad_alertas, prioridad_total,
                    puntero siguiente para la lista de la tabla hash)
    metricas.h      struct Metricas (los 4 contadores del enunciado)
    tablaHash.*     tabla hash con encadenamiento separado
    maxHeap.*       max-heap sobre un arreglo de punteros a Incidente


6. CÓMO FUNCIONA (RESUMEN)
--------------------------
Paso 1 - Lectura. main.cpp lee todas las alertas a arreglos dinámicos propios
         (la capacidad se duplica cuando se llena). No cuenta en el tiempo.

Paso 2 - Consolidación (tabla hash). Por cada alerta se llama a
         registrarAlerta(id, severidad):
           a) funcionHash(id) devuelve la cubeta.
           b) Se recorre la lista de esa cubeta buscando el id.
           c) Si existe: cantidad_alertas++ y prioridad_total += severidad.
              Si no existe: se crea un nodo nuevo al inicio de la lista.
           d) Si la carga (incidentes / tamaño) llega a 0.75 se llama a
              redimensionar().

         funcionHash: método de la división. Toma los dígitos del ID (se salta
         el prefijo "INC-"), arma el número y devuelve numero % tamanoTabla.
         Supuesto: los IDs tienen formato INC- seguido de dígitos.

         redimensionar: duplica el tamaño de la tabla (inicia en 1024) y
         vuelve a ubicar cada nodo con la función hash y el tamaño nuevo.

Paso 3 - Ranking (max-heap). copiarIncidentes() pasa los punteros de todos los
         incidentes a un arreglo. Se insertan en el MaxHeap y luego se extrae
         el mayor u veces; el orden de salida es el ranking. esMayor compara
         prioridad_total (mayor gana) y, si empata, incidente_id (menor gana).

Paso 4 - Salida. Se escribe ranking.csv y metricas.txt. El tiempo se mide solo
         alrededor de los pasos 2 y 3 (sin lectura ni escritura).


7. MÉTRICAS
-----------
    sondeos_hash       +1 por cada nodo revisado al buscar en una lista, y +1
                       por cada nodo reubicado durante un rehash
    comparaciones_heap +1 cada vez que el heap compara dos incidentes
    intercambios_heap  +1 cada vez que el heap intercambia dos posiciones
    tiempo_proceso_ms  consolidación + ranking, en milisegundos

    C(n) = sondeos_hash + comparaciones_heap
    R(n) = C(2n) / C(n)     (referencia: R(n) <= 3.0)


8. COMPLEJIDAD
--------------
Con u incidentes distintos y n alertas, y una buena distribución de la función
hash, el costo esperado es O(n + u log u): O(1) esperado por alerta en la tabla
hash (el rehash duplica el tamaño y reparte el costo) y O(log u) por inserción
o extracción en el heap.
Si la función hash enviara todo a una sola cubeta (por ejemplo, devolviendo
siempre 0), cada búsqueda recorrería toda la lista y el costo sería Θ(n²).
