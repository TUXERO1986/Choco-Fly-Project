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
void ControladorPrincipal::AgregarVuelo(string origen, string destino, string escalas, string fecha, float distancia) {
    controladorVuelos->AgregarNuevoVuelo(origen, destino, escalas, fecha, distancia, new ControladorAsientos());
}
void ControladorPrincipal::AgregarHotel(string nombre, string ciudad, float puntuacion, float precioNoche) {
    controladorHoteles->AgregarNuevoHotel(nombre, ciudad, puntuacion, precioNoche);
}
void ControladorPrincipal::AgregarPaquete(Vuelo* vueloIda, Hotel* hotel) {
    controladorPaquetes->AgregarNuevoPaquete(vueloIda, hotel);
}
void ControladorPrincipal::AgregarReserva(Reserva* nuevaReserva) {
    controladorReservas->AgregarReserva(nuevaReserva);
}
void ControladorPrincipal::AgregarUsuario(string nombre, string correo, string password) {
    controladorUsuarios->AgregarUsuario(nombre, correo, password);
}
void ControladorPrincipal::AgregarRuta(string origen, string destino, float distancia) {
    controladorRutas->AgregarNuevaRuta(origen, destino, distancia);
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
void ControladorPrincipal::EliminarUsuario(int indiceUsuario) {
    controladorUsuarios->getUsuarios()->eliminaPos(indiceUsuario);
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
void ControladorPrincipal::MostrarReservas() {
    controladorReservas->MostrarReservas();
}
void ControladorPrincipal::MostrarUsuarios() {
    controladorUsuarios->MostrarUsuarios();
}
void ControladorPrincipal::MostrarRutas() {
    controladorRutas->MostrarRutas();
}
void ControladorPrincipal::FilrarVuelosPorOrigenDestino(string origen, string destino) {
    controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
}
void ControladorPrincipal::FiltrarUsuariosPorNombre(string nombreBusqueda) {
    for(int i=0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
        Usuario* aux = controladorUsuarios->getUsuarios()->obtenerPos(i);
        if (aux->getNombre() == nombreBusqueda) {
            cout << "Usuario #" << i << ":" << endl;
            aux->MostrarDatosAdmin();
            cout << endl;
        }
	}
}
void ControladorPrincipal::FiltrarRutasPorOrigen(string ciudadBusqueda) {
    for(int i=0; i < controladorRutas->getRutas()->longitud(); i++) {
        Ruta* aux = controladorRutas->getRutas()->obtenerPos(i);
        if (aux->getOrigen() == ciudadBusqueda) {
            cout << "Ruta #" << i << ":" << endl;
            aux->MostrarDatos();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarRutasPorDestino(string ciudadBusqueda) {
    for(int i=0; i < controladorRutas->getRutas()->longitud(); i++) {
        Ruta* aux = controladorRutas->getRutas()->obtenerPos(i);
        if (aux->getDestino() == ciudadBusqueda) {
            cout << "Ruta #" << i << ":" << endl;
            aux->MostrarDatos();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarHotelesPorCiudad(string ciudadBusqueda) {
    for(int i=0; i < controladorHoteles->getHoteles()->longitud(); i++) {
        Hotel* aux = controladorHoteles->getHoteles()->obtenerPos(i);
        if (aux->getCiudad() == ciudadBusqueda) {
            cout << "Hotel #" << i << ":" << endl;
            aux->MostrarHotel();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarPaquetesPorDestino(string ciudadBusqueda) {
    for(int i=0; i < controladorPaquetes->getPaquetes()->longitud(); i++) {
        Paquete* aux = controladorPaquetes->getPaquetes()->obtenerPos(i);
        if (aux->getVueloIncluido()->getDestino() == ciudadBusqueda) {
            cout << "Paquete #" << i << ":" << endl;
            aux->MostrarPaquete();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarPaquetesPorOrigen(string ciudadBusqueda) {
    for(int i=0; i < controladorPaquetes->getPaquetes()->longitud(); i++) {
        Paquete* aux = controladorPaquetes->getPaquetes()->obtenerPos(i);
        if (aux->getVueloIncluido()->getOrigen() == ciudadBusqueda) {
            cout << "Paquete #" << i << ":" << endl;
            aux->MostrarPaquete();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarVuelosPorFecha(string fechaBusqueda) {
    for(int i=0; i < controladorVuelos->getVuelos()->longitud(); i++) {
        Vuelo* aux = controladorVuelos->getVuelos()->obtenerPos(i);
        if (aux->getFecha() == fechaBusqueda) {
            cout << "Vuelo #" << i << ":" << endl;
            aux->MostrarVuelo();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FitrarVuelosPorOrigen(string origenBusqueda) {
    for(int i=0; i < controladorVuelos->getVuelos()->longitud(); i++) {
        Vuelo* aux = controladorVuelos->getVuelos()->obtenerPos(i);
        if (aux->getOrigen() == origenBusqueda) {
            cout << "Vuelo #" << i << ":" << endl;
            aux->MostrarVuelo();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarVuelosPorDestino(string destinoBusqueda) {
    for(int i=0; i < controladorVuelos->getVuelos()->longitud(); i++) {
        Vuelo* aux = controladorVuelos->getVuelos()->obtenerPos(i);
        if (aux->getDestino() == destinoBusqueda) {
            cout << "Vuelo #" << i << ":" << endl;
            aux->MostrarVuelo();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarReservasPorUsuario(string codigoUsuario) {
    for(int i=0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == codigoUsuario) {
            cout << "Reserva #" << i << ":" << endl;
            aux->MostrarReserva();
            cout << endl;
        }
    }
}
void ControladorPrincipal::FiltrarReservasPorTipoUsuario(string tipoBusqueda, string codigousuario) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == codigousuario&&aux->getTipoReserva()==tipoBusqueda) {
            cout << "Reserva #" << i << ":" << endl;
            aux->MostrarReserva();
            cout << endl;
        }
    }
}
void ControladorPrincipal::ObtenerIngresosTotales() {
	float ingresosTotales = controladorReservas->CalcularIngresosTotales();
    cout << "Los ingresos totales generados por las reservas son: $" << ingresosTotales << endl;
}
void ControladorPrincipal::ConsultarVuelos(string origen, string destino) {
    if(controladorVuelos->VerificarVueloDirecto(origen, destino)) {
        cout << endl<<"¡Hay un vuelos directo disponible!" << endl;
        controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
        return;
    }
    else {
        Lista<Ruta*>* rutasEncontradas = controladorRutas->BuscarRutaMasCorta(origen, destino);
        if(controladorVuelos->GenerarVuelosConEscala(origen, destino, rutasEncontradas)) 
            controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
        
    }
}
void ControladorPrincipal::ComprarTicket(int indiceVuelo, Usuario* usuariActual, int equipajeBoveda, int equipajeCabina, int asiento, int clase) {
	Vuelo* vueloSeleccionado = controladorVuelos->ObtenerVueloPorPosicion(indiceVuelo);
	if (vueloSeleccionado != nullptr) {
		controladorReservas->AgregarReserva(new Ticket(usuariActual->getCodigo(), usuariActual->getNombre(), 
			vueloSeleccionado->getOrigen(), vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(), 
            vueloSeleccionado->getDistancia(), equipajeBoveda, 1+equipajeCabina,clase,asiento));
		
	}
}
void ControladorPrincipal::ReservarHotel(int indiceHotel, Usuario* userActual,int noches,int habitacion,int tipoO,int tipoC,int tipoS) {
	Hotel* hotelSeleccionado = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
	if (hotelSeleccionado != nullptr) {
		controladorReservas->AgregarReserva(new ReservaHotel(userActual->getNombre(), userActual->getCodigo(), hotelSeleccionado->getNombre(),
			hotelSeleccionado->getCiudad(), hotelSeleccionado->getPrecioNoche(),noches,habitacion,tipoO,tipoC,tipoS));
	}
}
void ControladorPrincipal::ReservarPaquete(int indicePaquete, Usuario* userActual,int noches,
    int maletasBodegaIda,int maletasBodegaRetorno,int clase,int asiento) {
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

    Ticket* ticketIda = new Ticket(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getOrigen(), vueloOferta->getDestino(),
        vueloOferta->getEscalas(),
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento 
    );

    float precioTotalHotel = hotelOferta->getPrecioNoche() * noches;
    ReservaHotel* reservaHotel = new ReservaHotel(
        userActual->getCodigo(), userActual->getNombre(),
        hotelOferta->getNombre(), hotelOferta->getCiudad(),
        noches, precioTotalHotel,1,1,1,1
    );

    string fechaRetorno = SumarDiasAFecha(vueloOferta->getFecha(), noches);

    Ticket* ticketRetorno = new Ticket(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getDestino(), vueloOferta->getOrigen(), 
        "Directo", 
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento
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
void ControladorPrincipal::MostrarReservasUsuario(Usuario* userActual) {
    controladorReservas->MostrarReservasUsuario(userActual->getCodigo());
}
void ControladorPrincipal::MostrarAsientos(int indiceVuelo) {
    controladorVuelos->getVuelos()->obtenerPos(indiceVuelo)->MostrarAsientos();
}
void ControladorPrincipal::MostrarHabitaciones(int indiceHabtitacion) {
    controladorHoteles->getHoteles()->obtenerPos(indiceHabtitacion)->MostrarHabitaciones();
}
bool ControladorPrincipal::VerificarAsiento(int numeroAsiento,int indiceVuelo) {
    return controladorVuelos->getVuelos()->obtenerPos(indiceVuelo)->getControladorAsientos()->VerificarAsiento(numeroAsiento);
}
bool ControladorPrincipal::VerificarHabitacion(int numeroHabitacion,int indiceHotel) {
    return controladorHoteles->getHoteles()->obtenerPos(indiceHotel)->getControladorHabitaciones()->verificarHabitacion(numeroHabitacion);
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
            return nullptr;
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
ControladorUsuarios* ControladorPrincipal::getControladorUsuarios() { return controladorUsuarios; }