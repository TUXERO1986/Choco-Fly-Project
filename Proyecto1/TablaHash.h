#pragma once
#include "Lista.h"
#include <string>
#include <iostream>
#include <functional>
using namespace std;

// 1. Usamos struct para tener acceso público a los nodos, y el orden estándar <K, T>
template<class K, typename T>
struct HashNode {
    K clave;
    T valor;
    
    HashNode(K c, T v) {
        clave = c;
        valor = v;
    }
};

template<class K, typename T>
class HashTable {
private:
    int TABLE_SIZE;
    int numElementos;

    // 2. Ahora sí le pasamos AMBOS parámetros al nodo: <K, T>
    Lista<HashNode<K, T>*>** tabla; 
    function<unsigned int(K)> funcionHash;

public:

    HashTable(function<unsigned int(K)> hashFunction, int size = 1009) {
        this->funcionHash = hashFunction;
        this->TABLE_SIZE = size;
        this->numElementos = 0;
        
        tabla = new Lista<HashNode<K, T>*>*[TABLE_SIZE];
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            tabla[i] = new Lista<HashNode<K, T>*>();
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
        // 3. OBLIGATORIO: Aplicar el módulo para no salirnos del arreglo
        int indice = funcionHash(clave) % TABLE_SIZE;
        
        Lista<HashNode<K, T>*>* listaEnCasilla = tabla[indice];
        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            if (listaEnCasilla->obtenerPos(i)->clave == clave) {
                listaEnCasilla->obtenerPos(i)->valor = valor;
                return;
            }
        }

        listaEnCasilla->agregaFinal(new HashNode<K, T>(clave, valor));
        numElementos++;
    }

    T Buscar(K clave) {
        int indice = funcionHash(clave) % TABLE_SIZE;
        Lista<HashNode<K, T>*>* listaEnCasilla = tabla[indice];

        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            HashNode<K, T>* nodoActual = listaEnCasilla->obtenerPos(i);
            if (nodoActual->clave == clave) {
                return nodoActual->valor; // 4. Era flecha (->), no punto (.)
            }
        }
        return nullptr;
    }

    bool Eliminar(K clave) {
        int indice = funcionHash(clave) % TABLE_SIZE;

        Lista<HashNode<K, T>*>* listaEnCasilla = tabla[indice];

        for (int i = 0; i < listaEnCasilla->longitud(); i++) {
            HashNode<K, T>* nodoActual = listaEnCasilla->obtenerPos(i);
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