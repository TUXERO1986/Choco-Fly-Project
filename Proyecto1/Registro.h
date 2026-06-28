#pragma once
#include <iostream>
#include <string>

using namespace std;

class Registro {
private:
    string nombre;
    string correo;
    string tipoUsuario; 
    string accion;      
    string fechaHora;   

public:

    Registro(string nombre, string correo, string tipoUsuario, string accion, string fechaHora);
    ~Registro();

    string getNombre();
    string getCorreo();
    string getTipoUsuario();
    string getAccion();
    string getFechaHora();

    void setNombre(string nombre);
    void setCorreo(string correo);
    void setTipoUsuario(string tipoUsuario);
    void setAccion(string accion);
    void setFechaHora(string fechaHora);

    void MostrarRegistro();
};