#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

template <class T>
struct NodoAVL {
    T elemento;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(T e) : elemento(e), izq(nullptr), der(nullptr), altura(1) {}
};

template <class T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;
    function<float(T)> obtenerLlave; 

    int Altura(NodoAVL<T>* N) {
        if (N == nullptr) return 0;
        return N->altura;
    }

    int ObtenerBalance(NodoAVL<T>* N) {
        if (N == nullptr) return 0;
        return Altura(N->izq) - Altura(N->der);
    }

    NodoAVL<T>* RotacionDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izq;
        NodoAVL<T>* T2 = x->der;

        x->der = y;
        y->izq = T2;

        y->altura = max(Altura(y->izq), Altura(y->der)) + 1;
        x->altura = max(Altura(x->izq), Altura(x->der)) + 1;

        return x;
    }

    NodoAVL<T>* RotacionIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->der;
        NodoAVL<T>* T2 = y->izq;

        y->izq = x;
        x->der = T2;

        x->altura = max(Altura(x->izq), Altura(x->der)) + 1;
        y->altura = max(Altura(y->izq), Altura(y->der)) + 1;

        return y;
    }

    NodoAVL<T>* _insertar(NodoAVL<T>* nodo, T e) {
        // Inserción normal de BST usando la Lambda
        if (nodo == nullptr) return new NodoAVL<T>(e);

        if (obtenerLlave(e) < obtenerLlave(nodo->elemento))
            nodo->izq = _insertar(nodo->izq, e);
        else if (obtenerLlave(e) > obtenerLlave(nodo->elemento))
            nodo->der = _insertar(nodo->der, e);
        else
            return nodo; // No se permiten llaves duplicadas exactamente iguales

        // Actualizar altura
        nodo->altura = 1 + max(Altura(nodo->izq), Altura(nodo->der));

        // Obtener el factor de balance
        int balance = ObtenerBalance(nodo);

        // Casos de desbalanceo (Rotaciones AVL)
        if (balance > 1 && obtenerLlave(e) < obtenerLlave(nodo->izq->elemento))
            return RotacionDerecha(nodo);

        if (balance < -1 && obtenerLlave(e) > obtenerLlave(nodo->der->elemento))
            return RotacionIzquierda(nodo);

        if (balance > 1 && obtenerLlave(e) > obtenerLlave(nodo->izq->elemento)) {
            nodo->izq = RotacionIzquierda(nodo->izq);
            return RotacionDerecha(nodo);
        }

        if (balance < -1 && obtenerLlave(e) < obtenerLlave(nodo->der->elemento)) {
            nodo->der = RotacionDerecha(nodo->der);
            return RotacionIzquierda(nodo);
        }

        return nodo;
    }

    void _inOrden(NodoAVL<T>* nodo, function<void(T)> accion) {
        if (nodo != nullptr) {
            _inOrden(nodo->izq, accion);
            accion(nodo->elemento);
            _inOrden(nodo->der, accion);
        }
    }

    void _inOrdenInverso(NodoAVL<T>* nodo, function<void(T)> accion) {
    if (nodo != nullptr) {
        _inOrdenInverso(nodo->der, accion); // Primero los más caros
        accion(nodo->elemento);             // Luego el medio
        _inOrdenInverso(nodo->izq, accion); // Finalmente los más baratos
    }
    }
public:
    ArbolAVL(function<float(T)> lambdaLlave) {
        raiz = nullptr;
        obtenerLlave = lambdaLlave;
    }

    void Insertar(T e) {
        raiz = _insertar(raiz, e);
    }

    void RecorrerInOrden(function<void(T)> accion) {
        _inOrden(raiz, accion);
    }
    void RecorrerInOrdenInverso(function<void(T)> accion) {
    _inOrdenInverso(raiz, accion);
    }
};