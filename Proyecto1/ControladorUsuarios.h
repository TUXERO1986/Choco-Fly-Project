#pragma once
#include "Usuario.h"
#include "Lista.h"
#include "ControladorArchivos.h"
#include "Color.h"

using namespace ColorUI;

class ControladorUsuarios {
private:

    static const int TAMANO_TABLA = 100; 
    Lista<Usuario*>* tablaHash[TAMANO_TABLA]; 
    Lista<Usuario*>* usuarios; 
    ControladorArchivos* controladorArchivos;

    int FuncionHashPropia(string clave); 

public:
    ControladorUsuarios();
    ~ControladorUsuarios();
    
    void AgregarUsuario(string nombre, string correo, string password);
    Usuario* VerificarCredenciales(string nombre, string correo, string password);
    bool VerificarCuentaExistente(string nombre, string correo);
    
    void MostrarUsuarios();
    Lista<Usuario*>* getUsuarios();
    void setUsuarios(Lista<Usuario*>* usuarios);
};