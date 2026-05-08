#include "ControladorUsuarios.h"
ControladorUsuarios::ControladorUsuarios() {
	controladorArchivos = new ControladorArchivos("Usuarios.txt");
	usuarios = new Lista<Usuario*>();
	controladorArchivos->LeerArchivoUsuarios(usuarios);
}
ControladorUsuarios::~ControladorUsuarios() {
	for (int i = 0; i < usuarios->longitud(); i++) {
		delete usuarios->obtenerPos(i);
	}
	delete usuarios;
}
void ControladorUsuarios::AgregarUsuario(string nombre, string correo, string password) {

    string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int n = caracteres.length();

    for (int i = n - 1; i > 0; i--) {

        int j = rand() % (i + 1);

        char temp = caracteres[i];
        caracteres[i] = caracteres[j];
        caracteres[j] = temp;
    }

    string codigoGenerado = "U-" + caracteres.substr(0, 6);

    Usuario* nuevoUsuario = new Usuario(nombre, correo, password, codigoGenerado);

    usuarios->agregaFinal(nuevoUsuario);
    controladorArchivos->GuardarDatoArchivoUsuarios(nuevoUsuario);

}
Usuario* ControladorUsuarios::VerificarCredenciales(string nombre,string correo,string password) {
	for (int i = 0; i < usuarios->longitud(); i++) {
		Usuario* aux = usuarios->obtenerPos(i);
		cout << "verificarcredenciales" << aux->getNombre() << " " << nombre << endl;
		if (aux->getNombre() != nombre)continue;
		if (aux->getCorreo() == correo && aux->getPassword() == password) {
			return aux;
	}
		}
	return nullptr;
}
bool ControladorUsuarios::VerificarCuentaExistente(string nombre, string correo) {
	for (int i = 0; i < usuarios->longitud(); i++) {
		cout << "verificarcuentaexistente" << usuarios->obtenerPos(i)->getNombre() << " " << nombre << endl;
		Usuario* aux = usuarios->obtenerPos(i);
		if (aux->getNombre() == nombre && aux->getCorreo() == correo)
			return true;
	}
	return false;
}
void ControladorUsuarios::MostrarUsuariosUsuarios() {
	for (int i = 0; i < usuarios->longitud(); i++) {
		Usuario* aux = usuarios->obtenerPos(i);
		aux->MostrarDatosUsuarios();
	}
}
void ControladorUsuarios::MostrarUsuariosAdmin() {
	for (int i = 0; i < usuarios->longitud(); i++) {
		Usuario* aux = usuarios->obtenerPos(i);
		aux->MostrarDatosAdmin();
	}
}
Lista<Usuario*>* ControladorUsuarios::getUsuarios() { return usuarios; }
void ControladorUsuarios::setUsuarios(Lista<Usuario*>* usuarios) { this->usuarios = usuarios; }
