#pragma once
#include "Nodo.h"
#include <functional>
#include <iostream>
typedef unsigned int uint;
template<class T>
class Lista
{
private:
    typedef std::function<int(T, T)> Comp;
	Nodo<T>* ini;
	uint lon;
public:
	Lista();
	~Lista();

    uint longitud();
    bool esVacia();
    void agregaInicial(T elem);
    void agregaPos(T elem, uint pos);
    void agregaFinal(T elem);
    void modificarInicial(T elem);
    void modificarPos(T elem, uint pos);
    void modificarFinal(T elem);
    void eliminaInicial();
    void eliminaPos(uint pos);
    void eliminaFinal();
    T obtenerInicial();
    T obtenerPos(uint pos);
    uint getPos(T elem);
    T obtenerFinal();
    T buscar(T elem);

};
template<class T>
Lista<T>::Lista() {
    ini = nullptr;
    lon = 0;
}
template<class T>
Lista<T>::~Lista() {
    Nodo<T>* aux = ini;
    while (aux != nullptr) {
        Nodo<T>* siguiente = aux->getSig();
        delete aux;
        aux = siguiente;
    }
    ini = nullptr;
    lon = 0;
}

template <class T>
uint Lista<T>::longitud() {
    return lon;
}
template <class T>
bool Lista<T>::esVacia() {
    return lon == 0;
}
template <class T>
void Lista<T>::agregaInicial(T elem) {
    Nodo<T>* nuevo = new Nodo<T>(elem);
    if (nuevo != nullptr) {
		nuevo->setSig(ini);
        ini = nuevo;
        lon++;
    }
}
template <class T>
T Lista<T>::buscar(T elem) {
    Nodo<T>* aux = ini;
    while (aux != nullptr) {
        if (Comp(aux->elem, elem) == 0) {
            return aux->elem;
        }
        aux = aux->getSig();
    }
    return 0;
}

template <class T>
void Lista<T>::agregaPos(T elem, uint pos) {
    if (pos > lon) return;
    if (pos == 0) {
        agregaInicial(elem);
    }
    else {
        Nodo<T>* aux = ini;
        for (int i = 1; i < pos; i++) {
            aux = aux->getSig();
        }
        Nodo<T>* nuevo = new Nodo<T>(elem);
        nuevo->setSig(aux->getSig());
        if (nuevo != nullptr) {

            aux->setSig(nuevo);
            lon++;
        }
    }
}
template <class T>
void Lista<T>::agregaFinal(T elem) {
    agregaPos(elem, lon);  
}

template <class T>
void Lista<T>::eliminaInicial() {
    if (lon > 0) {
        Nodo<T>* aux = ini;
        ini = ini->getSig();
        delete aux;
        lon--;
    }
}

template <class T>
void Lista<T>::eliminaPos(uint pos) {
    if (pos >= lon) return;

    if (pos == 0) {
        eliminaInicial();
        return;
    }

    Nodo<T>* aux = ini;
    for (uint i = 0; i < pos - 1; i++) {
        aux = aux->getSig();
    }

    Nodo<T>* nodoAEliminar = aux->getSig();

    aux->setSig(nodoAEliminar->getSig());
    delete nodoAEliminar;
    lon--;
}
template <class T>
void Lista<T>::eliminaFinal() {
    if (lon == 0) return;


    if (lon == 1) {
        delete ini;
        ini = nullptr;
        lon = 0;
        return;
    }

    Nodo<T>* aux = ini;
    for (int i = 0; i < lon - 2; i++) {
        aux = aux->getSig();
    }

    Nodo<T>* nodoAEliminar = aux->getSig();
    aux->setSig(nullptr);
    delete nodoAEliminar;

    lon--; 
}

template <class T>
void Lista<T>::modificarInicial(T elem) {
    if (lon > 0) {
		ini->setElemento(elem);
    }
}

template <class T>
void Lista<T>::modificarPos(T elem, uint pos) {
    if (pos >= 0 && pos < lon) {
        Nodo<T>* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->getSig();
        }
        aux->setElemento(elem);
    }
}
template <class T>
void Lista<T>::modificarFinal(T elem) {
    modificarPos(elem, lon - 1);
}

template <class T>
T Lista<T>::obtenerInicial() {
    return obtenerPos(0);
}


template <class T>
T Lista<T>::obtenerPos(uint pos) {
    if (pos >= 0 && pos < lon) {
        Nodo<T>* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->getSig();
        }
        return aux->getElemento();
    }
    else {
        return NULL;
    }
}
template <class T>
T Lista<T>::obtenerFinal() {
    return obtenerPos(lon - 1);
}
template <class T>
uint Lista<T>::getPos(T elem) {
    Nodo<T>* aux = ini;
    for (int i = 0; i < lon; i++) {
        if (aux->getElemento() == elem)
            return i;
        aux = aux->getSig();
    }
    return lon;
}
