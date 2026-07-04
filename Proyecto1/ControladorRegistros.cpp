#include "ControladorRegistros.h"

ControladorRegistros::ControladorRegistros() {
    registros = new Lista<Registro*>();
    ControladorArchivos* archivos= new ControladorArchivos("Registros.txt");
    archivos->LeerArchivoRegistros(registros);
    delete archivos;
}

ControladorRegistros::~ControladorRegistros() {
    for (uint i = 0; i < registros->longitud(); i++) {
        delete registros->obtenerPos(i);
    }
    delete registros;
}
std::string ControladorRegistros::ObtenerFechaHoraActual() {
    auto t = std::time(nullptr);
    std::tm tm_snapshot;

    #ifdef _WIN32
        localtime_s(&tm_snapshot, &t);
    #else
        localtime_r(&t, &tm_snapshot);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&tm_snapshot, "%d-%m-%Y %H:%M:%S");

    return oss.str();
}

void ControladorRegistros::AgregarRegistro(string nombre, string correo, string tipoUsuario, string accion) {
    string fechaHora=ObtenerFechaHoraActual();
    Registro* nuevoRegistro = new Registro(nombre,correo,tipoUsuario,accion,fechaHora);
    registros->agregaFinal(nuevoRegistro);
    ControladorArchivos* archivos= new ControladorArchivos("Registros.txt");
    archivos->GuardarDatoArchivoRegistros(nuevoRegistro);
    delete archivos;
}

void ControladorRegistros::MostrarDatos() {
    if (registros->longitud() == 0) {
        cout << "\n[!] El historial de acciones se encuentra vacio." << endl;
        return;
    }

    cout << "\n=========================================================" << endl;
    cout << "           HISTORIAL DE ACCIONES (MÁS RECIENTES)         " << endl;
    cout << "=========================================================" << endl;

    int ultimoIndice = static_cast<int>(registros->longitud()) - 1;

    for (int i = ultimoIndice; i >= 0; i--) {
        registros->obtenerPos(i)->MostrarRegistro();
    }
    cout << "=========================================================" << endl;
}

Lista<Registro*>* ControladorRegistros::getRegistros() {
    return registros;
}