#pragma once
#include <functional>
#include <algorithm>
#include "Lista.h"

template <class T, class K>
class ArbolAVLMultiClave {
private:
    struct Nodo {
        K clave;
        Lista<T>* bucket;
        int altura;
        Nodo* izq;
        Nodo* der;
        Nodo(K k, T dato) : clave(k), altura(1), izq(nullptr), der(nullptr) {
            bucket = new Lista<T>();
            bucket->agregaFinal(dato);
        }
        ~Nodo() { delete bucket; }
    };

    Nodo* raiz;
    std::function<K(T)> getClave;

    int getAltura(Nodo* n) { return n ? n->altura : 0; }
    int getBalance(Nodo* n) { return n ? getAltura(n->izq) - getAltura(n->der) : 0; }

    Nodo* rotacionDerecha(Nodo* y) {
        Nodo* x = y->izq; Nodo* T2 = x->der;
        x->der = y; y->izq = T2;
        y->altura = (std::max)(getAltura(y->izq), getAltura(y->der)) + 1;
        x->altura = (std::max)(getAltura(x->izq), getAltura(x->der)) + 1;
        return x;
    }
    Nodo* rotacionIzquierda(Nodo* x) {
        Nodo* y = x->der; Nodo* T2 = y->izq;
        y->izq = x; x->der = T2;
        x->altura = (std::max)(getAltura(x->izq), getAltura(x->der)) + 1;
        y->altura = (std::max)(getAltura(y->izq), getAltura(y->der)) + 1;
        return y;
    }

    Nodo* insertarRecursivo(Nodo* nodo, T dato, K clave) {
        if (!nodo) return new Nodo(clave, dato);

        if (clave < nodo->clave)
            nodo->izq = insertarRecursivo(nodo->izq, dato, clave);
        else if (clave > nodo->clave)
            nodo->der = insertarRecursivo(nodo->der, dato, clave);
        else {
            nodo->bucket->agregaFinal(dato); 
            return nodo;
        }

        nodo->altura = 1 + (std::max)(getAltura(nodo->izq), getAltura(nodo->der));
        int balance = getBalance(nodo);

        if (balance > 1 && getBalance(nodo->izq) >= 0) return rotacionDerecha(nodo);
        if (balance < -1 && getBalance(nodo->der) <= 0) return rotacionIzquierda(nodo);
        if (balance > 1 && getBalance(nodo->izq) < 0) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && getBalance(nodo->der) > 0) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }
        return nodo;
    }

    Lista<T>* buscarRecursivo(Nodo* nodo, K claveBuscada) {
        if (!nodo) return nullptr;
        if (claveBuscada == nodo->clave) return nodo->bucket;
        if (claveBuscada < nodo->clave) return buscarRecursivo(nodo->izq, claveBuscada);
        return buscarRecursivo(nodo->der, claveBuscada);
    }

    void destruirRecursivo(Nodo* nodo) {
        if (!nodo) return;
        destruirRecursivo(nodo->izq);
        destruirRecursivo(nodo->der);
        delete nodo;
    }

public:
    ArbolAVLMultiClave(std::function<K(T)> lambdaExtractor) {
        raiz = nullptr;
        getClave = lambdaExtractor;
    }
    ~ArbolAVLMultiClave() { destruirRecursivo(raiz); }

    void Insertar(T dato) {
        raiz = insertarRecursivo(raiz, dato, getClave(dato));
    }

  
    Lista<T>* BuscarTodos(K clave) {
        return buscarRecursivo(raiz, clave);
    }
};