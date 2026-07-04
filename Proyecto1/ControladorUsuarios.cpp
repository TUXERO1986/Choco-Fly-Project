#include "ControladorUsuarios.h"

ControladorUsuarios::ControladorUsuarios() {
    controladorArchivos = new ControladorArchivos(); 
    usuarios = new Lista<Usuario*>();

    miFuncionHashCorreo = [](string clave) -> unsigned int {
        unsigned int sumaHash = 0;
        for (int i = 0; i < clave.length(); i++) {
            sumaHash = (sumaHash * 31) + clave[i];
        }
        return sumaHash;
    };

    tablaUsuarios = new HashTable<string, Usuario*>(miFuncionHashCorreo, TAMANO_TABLA);
    
    controladorArchivos->LeerArchivoUsuarios(usuarios); 
    for (unsigned int i = 0; i < usuarios->longitud(); i++) {
        Usuario* aux = usuarios->obtenerPos(i);
        tablaUsuarios->Insertar(aux->getCorreo(), aux);
    }
}

ControladorUsuarios::~ControladorUsuarios() {

    for (unsigned int i = 0; i < usuarios->longitud(); i++) {
        delete usuarios->obtenerPos(i);
    }
    delete usuarios;
    
    delete tablaUsuarios;
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

    tablaUsuarios->Insertar(correo, nuevoUsuario);
    
    controladorArchivos->GuardarDatoArchivoUsuarios(nuevoUsuario);
}

void ControladorUsuarios::AgregarRegistro(string registro){
    registroUsuarios->apilar(registro);
}
Usuario* ControladorUsuarios::VerificarCredenciales(string nombre, string correo, string password) {

    Usuario* userAux = tablaUsuarios->Buscar(correo);

    if (userAux != nullptr && userAux->getPassword() == password) {
        return userAux;
    }
    
    return nullptr;
}

bool ControladorUsuarios::VerificarCuentaExistente(string nombre, string correo) {
    return tablaUsuarios->Buscar(correo) != nullptr;
}

void ControladorUsuarios::MostrarUsuarios() {
    for (int i = 0; i < usuarios->longitud(); i++) {
        Usuario* aux = usuarios->obtenerPos(i);
        cout << endl;
        aux->MostrarDatos();
        cout << endl;
    }
}

Lista<Usuario*>* ControladorUsuarios::getUsuarios() { return usuarios; }
HashTable<string,Usuario*>* ControladorUsuarios::gettablaUsuarios(){return tablaUsuarios;}
void ControladorUsuarios::setUsuarios(Lista<Usuario*>* usuarios) { this->usuarios = usuarios; }