#!/bin/bash
# Compila el proyecto y ejecuta todas las pruebas, guardando las salidas en resultados/
# Uso (desde la carpeta PROYECTO, en Git Bash):  bash ejecutar_pruebas.sh

cd "$(dirname "$0")"
PRUEBAS=CyberShield_Pruebas_Estudiantes

# Elegir el comando de Python disponible
PY=python
command -v $PY >/dev/null 2>&1 || PY=python3
command -v $PY >/dev/null 2>&1 || PY=py

echo "== Compilando =="
g++ -std=c++17 -O2 codigo/*.cpp -o codigo/cybershield || { echo "Error de compilacion"; exit 1; }
mkdir -p resultados

ejecutar() {   # $1 = archivo de entrada, $2 = archivo esperado (opcional)
    nombre=$(basename "$1" .csv)
    ./codigo/cybershield "$1" "resultados/${nombre}_ranking.csv" "resultados/${nombre}_metricas.txt"
    if [ -n "$2" ] && [ -f "$2" ]; then
        printf "%-26s " "$nombre"
        $PY "$PRUEBAS/herramientas/comparar.py" "$2" "resultados/${nombre}_ranking.csv" | head -1
    else
        echo "$nombre: generado (sin archivo esperado)"
    fi
}

echo "== Pruebas oficiales =="
if [ -d "$PRUEBAS/datos" ]; then
    for f in "$PRUEBAS"/datos/*.csv; do
        ejecutar "$f" "$PRUEBAS/esperados/$(basename "$f" .csv).esperado.csv"
    done
else
    echo "No se encontro $PRUEBAS/ (descomprimir el zip oficial dentro de PROYECTO)"
fi

echo "== Datos propios =="
for f in datos_prueba/*.csv; do
    ejecutar "$f"
done

echo "Listo: revisar la carpeta resultados/"
