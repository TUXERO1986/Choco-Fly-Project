#include "Nodo.h"
template<class T>
Nodo<T>::Nodo() {
	sig = nullptr;
}
template<class T>
Nodo<T>::Nodo(T elemento) {
	this->elemento = elemento;
}
template<class T>
T Nodo<T>::getElemento() {
	return this->elemento;
}
template<class T>
Nodo<T>* Nodo<T>::getSig() {
	return this->sig;
}
template<class T>
void Nodo<T>::setElemento(T elemento) {
	this->elemento = elemento;
}
template<class T>
void Nodo<T>::setSig(Nodo* sig) {
	this->sig = sig;
}
template<class T>
bool Nodo<T>::esVacio() {
	return sig == nullptr;
}
