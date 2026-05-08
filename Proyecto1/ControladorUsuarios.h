#pragma once
#include "Usuario.h"
#include "Lista.h"
#include "ControladorArchivos.h"
class ControladorUsuarios
{
private:
	Lista<Usuario*>* usuarios;
	ControladorArchivos* controladorArchivos;
public:
	ControladorUsuarios();
	~ControladorUsuarios();
	void AgregarUsuario(string nombre, string correo, string password);
	Usuario* VerificarCredenciales(string nombre,string correo,string password);
	bool VerificarCuentaExistente(string nombre,string correo);
	void MostrarUsuariosUsuarios();
	void MostrarUsuariosAdmin();
	Lista<Usuario*>* getUsuarios();
	void setUsuarios(Lista<Usuario*>* usuarios);
};

