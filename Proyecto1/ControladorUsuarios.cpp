#include "ControladorUsuarios.h"
ControladorUsuarios::ControladorUsuarios() {
    controladorArchivos = new ControladorArchivos(); 
    usuarios = new Lista<Usuario*>();

    for (int i = 0; i < TAMANO_TABLA; i++) {
        tablaHash[i] = new Lista<Usuario*>();
    }

    controladorArchivos->LeerArchivoUsuarios(usuarios); 
}

ControladorUsuarios::~ControladorUsuarios() {

    for (int i = 0; i < TAMANO_TABLA; i++) {
        delete tablaHash[i];
    }

    for (int i = 0; i < usuarios->longitud(); i++) {
        delete usuarios->obtenerPos(i);
    }
    delete usuarios;
}
int ControladorUsuarios::FuncionHashPropia(string clave) {
    long long sumaHash = 0;

    for (int i = 0; i < clave.length(); i++) {
        sumaHash = (sumaHash * 31) + clave[i]; 
    }
    
    int indice = sumaHash % TAMANO_TABLA;
    if (indice < 0) {
        indice += TAMANO_TABLA; 
    }
    return indice;
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

    int indice = FuncionHashPropia(correo);
    tablaHash[indice]->agregaFinal(nuevoUsuario);

}
Usuario* ControladorUsuarios::VerificarCredenciales(string nombre, string correo, string password) {

    int indice = FuncionHashPropia(correo);
    
    Lista<Usuario*>* listaEnIndice = tablaHash[indice];

    for (int i = 0; i < listaEnIndice->longitud(); i++) {
        Usuario* userAux = listaEnIndice->obtenerPos(i);
        if (userAux->getCorreo() == correo && userAux->getPassword() == password) {
            return userAux;
        }
    }
    
    return nullptr;
}

bool ControladorUsuarios::VerificarCuentaExistente(string nombre, string correo) {
    int indice = FuncionHashPropia(correo);
    Lista<Usuario*>* listaEnIndice = tablaHash[indice];

    for (int i = 0; i < listaEnIndice->longitud(); i++) {
        if (listaEnIndice->obtenerPos(i)->getCorreo() == correo) {
            return true; 
        }
    }
    return false;
}
void ControladorUsuarios::MostrarUsuarios() {
	for (int i = 0; i < usuarios->longitud(); i++) {
		Usuario* aux = usuarios->obtenerPos(i);
		cout << endl;
		aux->MostrarDatosAdmin();
		cout << endl;
	}
}
Lista<Usuario*>* ControladorUsuarios::getUsuarios() { return usuarios; }
void ControladorUsuarios::setUsuarios(Lista<Usuario*>* usuarios) { this->usuarios = usuarios; }
