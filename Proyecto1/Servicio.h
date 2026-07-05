#pragma once
#include <iostream>
#include <string>

using namespace std;

class Servicio {
protected:
    int id;
    string tipoServicio; 
    float precioBase;

public:

    Servicio(int id, string tipoServicio, float precioBase);

    virtual ~Servicio();

    int getId();
    string getTipoServicio();
    float getPrecioBase();

    virtual string aTextoArchivo()=0;
    virtual void MostrarDatos() = 0;
};