#pragma once
#include "Usuario.h"
#include "TablaHash.h"
#include "ControladorArchivos.h"
#include "ArbolAVLClave.h"
#include "Color.h"
#include "Pila.h"

using namespace ColorUI;

class ControladorUsuarios {
private:
    const int TAMANO_TABLA = 126;
    function<unsigned int(string)> miFuncionHashCorreo;
    HashTable<string, Usuario*>* tablaUsuarios; 
    Lista<Usuario*>* usuarios; 
    Pila<string>* registroUsuarios;
    ArbolAVLClave<Usuario*, string>* indiceCorreos;
    ControladorArchivos* controladorArchivos;

    int FuncionHashPropia(string clave); 

public:
    ControladorUsuarios();
    ~ControladorUsuarios();
    
    void AgregarUsuario(string nombre, string correo, string password);
    void AgregarRegistro(string);

    Usuario* VerificarCredenciales(string nombre, string correo, string password);
    bool VerificarCuentaExistente(string nombre, string correo);
    
    void MostrarUsuarios();
    Lista<Usuario*>* getUsuarios();
    HashTable<string,Usuario*>* gettablaUsuarios();
    void setUsuarios(Lista<Usuario*>* usuarios);
}; 