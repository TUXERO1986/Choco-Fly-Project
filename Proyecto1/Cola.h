#pragma once
#include <iostream>
#include "Nodo.h"
template <class T>
class Cola {
private:
    Nodo<T>* frente; 
    Nodo<T>* final;  
    int tamano;

public:
    Cola();
    ~Cola();

    Cola(const Cola&) = delete;
    Cola& operator=(const Cola) = delete;

    void encolar(T dato);     
    T desencolar();          
    bool estaVacia();        
    T verFrente();           
    int obtenerTamano();     
};


template <class T>
Cola<T>::Cola() {
    frente = nullptr;
    final = nullptr;
    tamano = 0;
}

template <class T>
Cola<T>::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

template <class T>
void Cola<T>::encolar(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);

    if (estaVacia()) {
        frente = nuevoNodo;
        final = nuevoNodo;
    }
    else {
        final->setSig(nuevoNodo);
        final = nuevoNodo;
    }
    tamano++;
}

template <class T>
T Cola<T>::desencolar() {
    if (estaVacia()) {
        std::cout << "Error: La cola esta vacia." << std::endl;
        return T(); 
    }

    Nodo<T>* nodoAEliminar = frente;
    T datoExtraido = nodoAEliminar->getElemento();

    frente = frente->getSig();

    if (frente == nullptr) {
        final = nullptr;
    }

    delete nodoAEliminar;
    tamano--;

    return datoExtraido;
}

template <class T>
bool Cola<T>::estaVacia() {
    return frente == nullptr;
}

template <class T>
T Cola<T>::verFrente() {
    if (estaVacia()) {
        std::cout << "Error: La cola esta vacia." << std::endl;
        return T();
    }
    return frente->getElemento();
}

template <class T>
int Cola<T>::obtenerTamano() {
    return tamano;
}