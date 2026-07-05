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
    Nodo<T>* _merge(Nodo<T>* l1, Nodo<T>* l2, std::function<bool(T, T)> comp);
    Nodo<T>* _getMid(Nodo<T>* head);
    Nodo<T>* _mergeSort(Nodo<T>* head, std::function<bool(T, T)> comp);

    void _quickSort(T* arr, int low, int high, std::function<bool(T, T)> comp);
    int _partition(T* arr, int low, int high, std::function<bool(T, T)> comp);

    void _heapify(T* arr, int n, int i, std::function<bool(T, T)> comp);
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
    
    void MergeSort(std::function<bool(T, T)> comp);
    void QuickSort(std::function<bool(T, T)> comp);
    void HeapSort(std::function<bool(T, T)> comp);

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
        return T{};
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

template <class T>
Nodo<T>* Lista<T>::_merge(Nodo<T>* l1, Nodo<T>* l2, std::function<bool(T, T)> comp) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (comp(l1->getElemento(), l2->getElemento())) {
        l1->setSig(_merge(l1->getSig(), l2, comp));
        return l1;
    } else {
        l2->setSig(_merge(l1, l2->getSig(), comp));
        return l2;
    }
}

template <class T>
Nodo<T>* Lista<T>::_getMid(Nodo<T>* head) {
    Nodo<T>* slow = head;
    Nodo<T>* fast = head->getSig();
    while (fast && fast->getSig()) {
        slow = slow->getSig();
        fast = fast->getSig()->getSig();
    }
    return slow;
}

template <class T>
Nodo<T>* Lista<T>::_mergeSort(Nodo<T>* head, std::function<bool(T, T)> comp) {
    if (!head || !head->getSig()) return head;
    
    Nodo<T>* mid = _getMid(head);
    Nodo<T>* nextToMid = mid->getSig();
    mid->setSig(nullptr);
    
    Nodo<T>* left = _mergeSort(head, comp);
    Nodo<T>* right = _mergeSort(nextToMid, comp);
    
    return _merge(left, right, comp);
}

template <class T>
void Lista<T>::MergeSort(std::function<bool(T, T)> comp) {
    if (lon > 1) {
        ini = _mergeSort(ini, comp);
    }
}

template <class T>
int Lista<T>::_partition(T* arr, int low, int high, std::function<bool(T, T)> comp) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <class T>
void Lista<T>::_quickSort(T* arr, int low, int high, std::function<bool(T, T)> comp) {
    if (low < high) {
        int pi = _partition(arr, low, high, comp);
        _quickSort(arr, low, pi - 1, comp);
        _quickSort(arr, pi + 1, high, comp);
    }
}

template <class T>
void Lista<T>::QuickSort(std::function<bool(T, T)> comp) {
    if (lon <= 1) return;
    
    T* arr = new T[lon];
    Nodo<T>* aux = ini;
    for (uint i = 0; i < lon; i++) {
        arr[i] = aux->getElemento();
        aux = aux->getSig();
    }
    
    _quickSort(arr, 0, lon - 1, comp);
    
    aux = ini;
    for (uint i = 0; i < lon; i++) {
        aux->setElemento(arr[i]);
        aux = aux->getSig();
    }
    delete[] arr;
}

template <class T>
void Lista<T>::_heapify(T* arr, int n, int i, std::function<bool(T, T)> comp) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && comp(arr[largest], arr[l])) largest = l;
    if (r < n && comp(arr[largest], arr[r])) largest = r;
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        _heapify(arr, n, largest, comp);
    }
}

template <class T>
void Lista<T>::HeapSort(std::function<bool(T, T)> comp) {
    if (lon <= 1) return;
    
    T* arr = new T[lon];
    Nodo<T>* aux = ini;
    for (uint i = 0; i < lon; i++) {
        arr[i] = aux->getElemento();
        aux = aux->getSig();
    }
    
    for (int i = lon / 2 - 1; i >= 0; i--) {
        _heapify(arr, lon, i, comp);
    }
    
    for (int i = lon - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        _heapify(arr, i, 0, comp);
    }
    
    aux = ini;
    for (uint i = 0; i < lon; i++) {
        aux->setElemento(arr[i]);
        aux = aux->getSig();
    }
    delete[] arr;
}
