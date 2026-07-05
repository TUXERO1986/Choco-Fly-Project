#pragma once
#include <functional>
#include <algorithm>

template <class T, class K>
class ArbolAVLClave {
private:
    struct Nodo {
        T dato;
        int altura;
        Nodo* izq;
        Nodo* der;
        Nodo(T d) : dato(d), altura(1), izq(nullptr), der(nullptr) {}
    };

    Nodo* raiz;
    std::function<K(T)> getClave;

    int getAltura(Nodo* n) {
        return n ? n->altura : 0;
    }

    int getBalance(Nodo* n) {
        return n ? getAltura(n->izq) - getAltura(n->der) : 0;
    }

    Nodo* rotacionDerecha(Nodo* y) {
        Nodo* x = y->izq;
        Nodo* T2 = x->der;
        x->der = y;
        y->izq = T2;
        y->altura = std::max(getAltura(y->izq), getAltura(y->der)) + 1;
        x->altura = std::max(getAltura(x->izq), getAltura(x->der)) + 1;
        return x;
    }

    Nodo* rotacionIzquierda(Nodo* x) {
        Nodo* y = x->der;
        Nodo* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        x->altura = std::max(getAltura(x->izq), getAltura(x->der)) + 1;
        y->altura = std::max(getAltura(y->izq), getAltura(y->der)) + 1;
        return y;
    }

    Nodo* insertarRecursivo(Nodo* nodo, T dato) {
        if (!nodo) return new Nodo(dato);

        K claveNueva = getClave(dato);
        K claveActual = getClave(nodo->dato);

        if (claveNueva < claveActual)
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        else if (claveNueva > claveActual)
            nodo->der = insertarRecursivo(nodo->der, dato);
        else
            return nodo; // Evitamos duplicados

        nodo->altura = 1 + std::max(getAltura(nodo->izq), getAltura(nodo->der));
        int balance = getBalance(nodo);

        // Rotaciones para balancear el árbol
        if (balance > 1 && claveNueva < getClave(nodo->izq->dato))
            return rotacionDerecha(nodo);
        if (balance < -1 && claveNueva > getClave(nodo->der->dato))
            return rotacionIzquierda(nodo);
        if (balance > 1 && claveNueva > getClave(nodo->izq->dato)) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && claveNueva < getClave(nodo->der->dato)) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    T buscarRecursivo(Nodo* nodo, K claveBuscada) {
        if (!nodo) return T{}; // Si no existe, retorna nulo

        K claveActual = getClave(nodo->dato);
        
        if (claveBuscada == claveActual) return nodo->dato;
        if (claveBuscada < claveActual) return buscarRecursivo(nodo->izq, claveBuscada);
        return buscarRecursivo(nodo->der, claveBuscada);
    }
Nodo* minValorNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual->izq != nullptr)
            actual = actual->izq;
        return actual;
    }

    Nodo* eliminarRecursivo(Nodo* raiz, K clave) {
        if (raiz == nullptr) return raiz;

        if (clave < getClave(raiz->dato))
            raiz->izq = eliminarRecursivo(raiz->izq, clave);
        else if (clave > getClave(raiz->dato))
            raiz->der = eliminarRecursivo(raiz->der, clave);
        else {
            if ((raiz->izq == nullptr) || (raiz->der == nullptr)) {
                Nodo* temp = raiz->izq ? raiz->izq : raiz->der;
                if (temp == nullptr) {
                    temp = raiz;
                    raiz = nullptr;
                } else
                    *raiz = *temp;
                delete temp;
            } else {
                Nodo* temp = minValorNodo(raiz->der);
                raiz->dato = temp->dato;
                raiz->der = eliminarRecursivo(raiz->der, getClave(temp->dato));
            }
        }

        if (raiz == nullptr) return raiz;

        raiz->altura = 1 + std::max(getAltura(raiz->izq), getAltura(raiz->der));
        int balance = getBalance(raiz);

        if (balance > 1 && getBalance(raiz->izq) >= 0) return rotacionDerecha(raiz);
        if (balance > 1 && getBalance(raiz->izq) < 0) {
            raiz->izq = rotacionIzquierda(raiz->izq);
            return rotacionDerecha(raiz);
        }
        if (balance < -1 && getBalance(raiz->der) <= 0) return rotacionIzquierda(raiz);
        if (balance < -1 && getBalance(raiz->der) > 0) {
            raiz->der = rotacionDerecha(raiz->der);
            return rotacionIzquierda(raiz);
        }

        return raiz;
    }
    void destruirRecursivo(Nodo* nodo) {
        if (!nodo) return;
        destruirRecursivo(nodo->izq);
        destruirRecursivo(nodo->der);
        delete nodo;
    }
public:
    ~ArbolAVLClave() {
        destruirRecursivo(raiz);
    }
    ArbolAVLClave(std::function<K(T)> lambdaExtractor) {
        raiz = nullptr;
        getClave = lambdaExtractor;
    }

    void Insertar(T dato) {
        raiz = insertarRecursivo(raiz, dato);
    }

    T Buscar(K clave) {
        return buscarRecursivo(raiz, clave);
    }
    void Eliminar(K clave) {
        raiz = eliminarRecursivo(raiz, clave);
    }
};