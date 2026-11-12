#include "maxHeap.h"
#include <iostream>
#include <fstream>
#include <string>
#include "incidente.h"
#include "metricas.h"
#include "tablaHash.h"

class maxHeap{
private:
    Incidente** arreglo;   // guarda punteros: un intercambio mueve un puntero, no un string
    int capacidad;
    int cantidad;
    Metricas* metricas;


    bool maxHeap::esMayor(const Incidente* a, const Incidente* b){
    metricas->comparaciones_heap++;
    if(a.prioridad_total > b.prioridad_total){
        return true;
    }
    return false;
        



    }
    void maxHeap::subir(int i){
        while(i>0){
            int padre = (i-1)/2;
            if(esMayor(arreglo[i], arreglo[padre])){
                swap(arreglo[i], arreglo[padre]);
                metricas->intercambios_heap++;
                i = padre;
            } else {
                break
            }
        }

    }
// Se usa cuando queremos extraer el mayor, el cual es la raiz y queremos reacomodar el heap
   void maxHeap::bajar(int i){
    while(i<cantidad){
        int izq = 2*i + 1;
        int der = 2*i + 2;
        if(izq >= cantidad){
            break;                                    
        }
        if(der < cantidad){
            int mejor; //Se usa para comparar cual de los hijos es mayor, o izquierda o derecha (es un pivote)
            if(esMayor(arreglo[izq], arreglo[der])){
                mejor = izq;
            } else {
                mejor = der;
            }
            //En esta parte realizamos las comparaciones para poder acomodar el heap
            if(esMayor(arreglo[mejor], arreglo[i])){
                swap(arreglo[mejor], arreglo[i]);
                i = mejor;
                metricas->intercambios_heap++;
            } else {
                break;
            }
        } else {
            if(esMayor(arreglo[izq], arreglo[i])){
                swap(arreglo[izq], arreglo[i]);
                i = izq;
                metricas->intercambios_heap++;
            } else {
                break;
            }
        }
    }
}

public:
    maxHeap::maxHeap(int capacidad, Metricas& metricas){
        this->capacidad = capacidad;
        this->metricas = metricas
        this->cantidad = -1;
        this->arreglo = new Incidente();

    }

    maxHeap::~maxHeap(){
        delete[] arreglo;
    }

    void maxHeap::insertar(const Incidente* incidente){
        if(cantidad ==capacidad){
            cout<<" El heap esta lleno "<<endl;
            return;
        }
        this->arreglo[cantidad] = incidente;
        cantidad++;
        subir(cantidad);

    }











}



// TODO (equipo): implementar aqui los metodos declarados en maxHeap.h:
//   MaxHeap::MaxHeap, MaxHeap::~MaxHeap, insertar, sacarMayor, estaVacio,
//   subir, bajar y esMayor.
// Recordar: cada llamada a esMayor suma 1 a metricas->comparaciones_heap
// y cada intercambio suma 1 a metricas->intercambios_heap.
