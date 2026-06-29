#pragma once
#include <iostream>
#include "Nodo.h"

template <class T>
class Pila {
private:
    Nodo<T>* tope; 
    int tamano;

public:
    Pila();
    ~Pila();

    void apilar(T dato);
    T desapilar();
    bool estaVacia();
    T verTope();
    int obtenerTamano();
};

template <class T>
Pila<T>::Pila() {
    tope = nullptr;
    tamano = 0;
}

template <class T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        desapilar();
    }
}

template <class T>
void Pila<T>::apilar(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);

    nuevoNodo->setSig(tope);
    
    tope = nuevoNodo;
    tamano++;
}

template <class T>
T Pila<T>::desapilar() {
    if (estaVacia()) {
        std::cout << "Error: La pila esta vacia." << std::endl;
        return T(); 
    }

    Nodo<T>* nodoAEliminar = tope;
    
    T datoExtraido = nodoAEliminar->getElemento();

    tope = tope->getSig();

    delete nodoAEliminar;
    tamano--;

    return datoExtraido;
}

template <class T>
bool Pila<T>::estaVacia() {
    return tope == nullptr;
}

template <class T>
T Pila<T>::verTope() {
    if (estaVacia()) {
        std::cout << "Error: La pila esta vacia." << std::endl;
        return T();
    }
    return tope->getElemento();
}

template <class T>
int Pila<T>::obtenerTamano() {
    return tamano;
}