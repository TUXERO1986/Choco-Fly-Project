#pragma once
template <class T>
class Nodo
{
private:
	T elemento;
	Nodo* sig;
public:
	Nodo();
	Nodo(T);
	
	void setElemento(T);
	void setSig(Nodo*);
	T getElemento();
	Nodo* getSig();
	bool esVacio();
};

