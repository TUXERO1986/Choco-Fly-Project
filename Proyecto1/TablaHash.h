#pragma once
#include "Lista.h"
#include <string>
#include <iostream>
#include <functional>
using namespace std;

template<class T,class K>
struct HashNode {
    string clave;
    T valor;
    
    HashNode(string c, T v) {
        clave = c;
        valor = v;
    }
};

template<class T,class K>
class HashTable {
private:
    int TABLE_SIZE;
    int numElementos;

    Lista<HashNode<T>*>** tabla; 
    function<unsigned int(K)> funcionHash;

public:

    HashTable(function<unsigned int(K)> hashFunction, int size = 1009) {
        this->funcionHash = hashFunction;
        this->TABLE_SIZE = size;
        this->numElementos = 0;
        
        tabla = new Lista<HashNode<T>*>*[TABLE_SIZE];
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            tabla[i] = new Lista<HashNode<T>*>();
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {

            for (int j = 0; j < tabla[i]->longitud(); j++) {
                delete tabla[i]->obtenerPos(j); 
            }

            delete tabla[i];
        }
        delete[] tabla;
    }

    void Insertar(K clave, T valor) {
        int indice = funcionHash(clave);
        
        Lista<HashNode<T>*>* listaEnCasilla = tabla[indice];
        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            if (listaEnCasilla->obtenerPos(i)->clave == clave) {

                listaEnCasilla->obtenerPos(i)->valor = valor;
                return;
            }
        }

        listaEnCasilla->agregaFinal(new HashNode<T>(clave, valor));
        numElementos++;
    }

    T Buscar(K clave) {
        int indice = funcionHash(clave);
        Lista<HashNode<T>*>* listaEnCasilla = tabla[indice];

        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            HashNode<T>* nodoActual = listaEnCasilla->obtenerPos(i);
            if (nodoActual->clave == clave) {
                return nodoActual->valor;
            }
        }
        return nullptr;
    }

    bool Eliminar(K clave) {
        int indice = funcionHash(clave);

        Lista<HashNode<T>*>* listaEnCasilla = tabla[indice];

        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            HashNode<T>* nodoActual = listaEnCasilla->obtenerPos(i);
            if (nodoActual->clave == clave) {

                listaEnCasilla->eliminaPos(i);
                delete nodoActual; 
                numElementos--;
                return true;
            }
        }
        return false; 
    }

    int sizeActual() {
        return numElementos;
    }
};