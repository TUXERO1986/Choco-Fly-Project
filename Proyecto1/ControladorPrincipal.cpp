#include "ControladorPrincipal.h"
ControladorPrincipal::ControladorPrincipal() {
	controladorRutas = new ControladorRutas();
	controladorHoteles = new ControladorHoteles();
	controladorReservas = new ControladorReservas();
	controladorVuelos = new ControladorVuelos();
	controladorPaquetes = new ControladorPaquetes();
	controladorUsuarios = new ControladorUsuarios();
}
ControladorPrincipal::~ControladorPrincipal() {
	delete controladorRutas;
	delete controladorHoteles;
	delete controladorReservas	;
	delete controladorPaquetes;
}
void ControladorPrincipal::GenerarDatos(int cantidadVuelos, int cantidadHoteles, int cantidadPaquetes) {
	GenerarVuelos(cantidadVuelos);
	GenerarHoteles(cantidadHoteles);
	GenerarPaquetes(cantidadPaquetes);
}
void ControladorPrincipal::GenerarVuelos(int cantidadVuelos) {
	controladorVuelos->GenerarVuelos(cantidadVuelos, controladorRutas->getRutas());
}
void ControladorPrincipal::GenerarHoteles(int cantidadHoteles) {
	controladorHoteles->GenerarHoteles(cantidadHoteles, controladorRutas->getMapaCiudades());
}
void ControladorPrincipal::GenerarPaquetes(int cantidadPaquetes) {
	controladorPaquetes->GenerarPaquetes(cantidadPaquetes, controladorHoteles->getHoteles(), controladorVuelos->getVuelos());
}
void ControladorPrincipal::EliminarVuelo(int indiceVuelo) {
	controladorVuelos->getVuelos()->eliminaPos(indiceVuelo);
}
void ControladorPrincipal::EliminarHotel(int indiceHotel) {
	controladorHoteles->getHoteles()->eliminaPos(indiceHotel);
}
void ControladorPrincipal::EliminarPaquete(int indicePaquete) {
	controladorPaquetes->getPaquetes()->eliminaPos(indicePaquete);
}
void ControladorPrincipal::EliminarReserva(int indiceReserva) {
	controladorReservas->getReservasTotales()->eliminaPos(indiceReserva);
}
void ControladorPrincipal::ConsultarVuelos(string origen, string destino) {
	Lista<Ruta*>* rutasEncontradas = controladorRutas->BuscarRutaMasCorta(origen, destino);
	controladorVuelos->GenerarVuelosConEscala(origen, destino, rutasEncontradas);
}
void ControladorPrincipal::ComprarTicket(int indiceVuelo, Usuario* usuariActual) {
	cout << "Digite el numero de maletas de bodega que desea llevar: ";
	int equipaje;
	cin >> equipaje;
	cout << "Digite el numero de maletas de cabina que desea llevar: ";
	int equipajecabina;
	cin >> equipajecabina;
	Vuelo* vueloSeleccionado = controladorVuelos->ObtenerVueloPorPosicion(indiceVuelo);
	if (vueloSeleccionado != nullptr) {
		controladorReservas->AgregarReserva(new Ticket(usuariActual->getCodigo(), usuariActual->getNombre(), 
			vueloSeleccionado->getOrigen(), vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(),
			vueloSeleccionado->getPrecio(), vueloSeleccionado->getDistancia(), equipaje, equipajecabina));
		
	}
}
void ControladorPrincipal::ReservarHotel(int indiceHotel, string nombre,string codigo,int noches) {
	Hotel* hotelSeleccionado = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
	if (hotelSeleccionado != nullptr) {
		controladorReservas->AgregarReserva(new ReservaHotel(nombre, codigo, hotelSeleccionado->getNombre(), 
			hotelSeleccionado->getCiudad(), hotelSeleccionado->getPrecioNoche(),noches));
	}
}
void ControladorPrincipal::ReservarPaquete(int indicePaquete, Usuario* userActual) {
    Paquete* oferta = controladorPaquetes->getPaquetes()->obtenerPos(indicePaquete);
    Vuelo* vueloOferta = oferta->getVueloIncluido();
    Hotel* hotelOferta = oferta->getHotelIncluido();

    auto SumarDiasAFecha = [](string fecha, int dias) {
        size_t pos1 = fecha.find("-");
        size_t pos2 = fecha.find("-", pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) return fecha;

        int dia = stoi(fecha.substr(0, pos1));
        int mes = stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
        int anio = stoi(fecha.substr(pos2 + 1));
        int diasPorMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) diasPorMes[2] = 29;

        dia += dias;
        while (dia > diasPorMes[mes]) {
            dia -= diasPorMes[mes];
            mes++;
            if (mes > 12) {
                mes = 1;
                anio++;
                if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) diasPorMes[2] = 29;
                else diasPorMes[2] = 28;
            }
        }
        return to_string(dia) + "-" + to_string(mes) + "-" + to_string(anio);
        };
    int noches, maletasIda, maletasVuelta;

    cout << "--- PERSONALIZANDO TU PAQUETE ---" << endl;
    cout << "Cuantas noches desea hospedarse en el hotel " << hotelOferta->getNombre() << "?: ";
    cin >> noches;

    cout << "Cantidad de maletas de bodega para el vuelo de IDA: ";
    cin >> maletasIda;

    cout << "Cantidad de maletas de bodega para el vuelo de RETORNO: ";
    cin >> maletasVuelta;

    Ticket* ticketIda = new Ticket(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getOrigen(), vueloOferta->getDestino(),
        vueloOferta->getEscalas(), vueloOferta->getPrecio(),
        vueloOferta->getDistancia(), maletasIda, 1 
    );

    float precioTotalHotel = hotelOferta->getPrecioNoche() * noches;
    ReservaHotel* reservaHotel = new ReservaHotel(
        userActual->getCodigo(), userActual->getNombre(),
        hotelOferta->getNombre(), hotelOferta->getCiudad(),
        noches, precioTotalHotel
    );

    string fechaRetorno = SumarDiasAFecha(vueloOferta->getFecha(), noches);

    Ticket* ticketRetorno = new Ticket(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getDestino(), vueloOferta->getOrigen(), 
        "Directo", vueloOferta->getPrecio(), 
        vueloOferta->getDistancia(), maletasVuelta, 1
    );

    ReservaPaquete* nuevaReserva = new ReservaPaquete(
        userActual->getCodigo(),
        userActual->getNombre(),
        ticketIda,
        ticketRetorno,
        reservaHotel
    );

    controladorReservas->AgregarReserva(nuevaReserva);

    cout << "\n¡Reserva de paquete completada exitosamente!" << endl;
    cout << "Tu vuelo de retorno ha sido programado automaticamente para el: " << fechaRetorno << endl;
}
void ControladorPrincipal::MostrarVuelos() {
	controladorVuelos->MostrarVuelos();
}
void ControladorPrincipal::MostrarHoteles() {
	controladorHoteles->MostrarHoteles();
}
void ControladorPrincipal::MostrarPaquetes() {
	controladorPaquetes->MostrarPaquetes();
}
void ControladorPrincipal::MostrarReservasUsuario(Usuario* userActual) {
    controladorReservas->MostrarReservasUsuario(userActual->getCodigo());
}
void ControladorPrincipal::MostrarReservasAdmin() {
    controladorReservas->MostrarReservasAdmin();
}
void ControladorPrincipal::MostrarUsuariosAdmin() {
    controladorUsuarios->MostrarUsuariosAdmin();
}
Usuario* ControladorPrincipal::VerificarInicioSesion(string nombre, string correo, string password) {
	bool existeCuenta = controladorUsuarios->VerificarCuentaExistente(nombre, correo);
    Usuario* usuarioEncontrado = controladorUsuarios->VerificarCredenciales(nombre, correo, password);
    if (usuarioEncontrado != nullptr&&existeCuenta) {
        cout << "¡Inicio de sesión exitoso! Bienvenido, " << usuarioEncontrado->getNombre() << "!" << endl;
        return usuarioEncontrado;
    } else {
        if (existeCuenta) {
            cout << "Error: Contraseña incorrecta. Por favor, intenta nuevamente." << endl;
        } else {
			controladorUsuarios->AgregarUsuario(nombre, correo, password);
			cout << "¡Cuenta creada exitosamente! Bienvenido, " << nombre << "!" << endl;
			return controladorUsuarios->getUsuarios()->obtenerFinal();
        }   
    }
}
ControladorHoteles* ControladorPrincipal::getControladorHoteles() { return controladorHoteles; }
ControladorPaquetes* ControladorPrincipal::getControladorPaquetes() { return controladorPaquetes; }
ControladorReservas* ControladorPrincipal::getControladorReservas() { return controladorReservas; }
ControladorVuelos* ControladorPrincipal::getControladorVuelos() { return controladorVuelos; }
ControladorRutas* ControladorPrincipal::getControladorRutas() { return controladorRutas; }
