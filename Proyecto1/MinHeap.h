#pragma once
#include <iostream>
#include <functional>

using namespace std;

template <class T>
class MinHeap {
private:
    T* arreglo;
    int capacidad;
    int sizeActual;

    function<bool(T, T)> comp;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void Heapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

       
        if (l < sizeActual && comp(arreglo[l], arreglo[smallest]))
            smallest = l;

        if (r < sizeActual && comp(arreglo[r], arreglo[smallest]))
            smallest = r;

        if (smallest != i) {
            swap(arreglo[i], arreglo[smallest]);
            Heapify(smallest);
        }
    }

public:

    MinHeap(int cap, function<bool(T, T)> comparador) {
        capacidad = cap;
        sizeActual = 0;
        arreglo = new T[capacidad];
        comp = comparador;
    }

    ~MinHeap() {
        delete[] arreglo;
    }

    void Insertar(T x) {
        if (sizeActual == capacidad) return; 

        sizeActual++;
        int i = sizeActual - 1;
        arreglo[i] = x;

        
        while (i != 0 && comp(arreglo[i], arreglo[parent(i)])) {
            swap(arreglo[i], arreglo[parent(i)]);
            i = parent(i);
        }
    }

    T ExtraerMinimo() {
        if (sizeActual <= 0) return nullptr;
        if (sizeActual == 1) {
            sizeActual--;
            return arreglo[0];
        }

        T root = arreglo[0];
        arreglo[0] = arreglo[sizeActual - 1];
        sizeActual--;
        Heapify(0);

        return root;
    }

    bool EsVacio() { return sizeActual == 0; }
};