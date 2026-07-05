#include "ControladorPrincipal.h"
ControladorPrincipal::ControladorPrincipal() {
	controladorRutas = new ControladorRutas();
	controladorHoteles = new ControladorHoteles();
	controladorReservas = new ControladorReservas();
	controladorVuelos = new ControladorVuelos();
	controladorPaquetes = new ControladorPaquetes();
	controladorUsuarios = new ControladorUsuarios();
    controladorRegistros= new ControladorRegistros();
    generadorDataset = new GeneradorDataset();
}
ControladorPrincipal::~ControladorPrincipal() {
	delete controladorRutas;
	delete controladorHoteles;
	delete controladorReservas;
    delete controladorVuelos;
	delete controladorPaquetes;
    delete controladorUsuarios;
    delete controladorRegistros;
    delete generadorDataset;
}
void ControladorPrincipal::GenerarDatos(int cantidadVuelos, int cantidadHoteles, int cantidadPaquetes) {
    GenerarVuelos(cantidadVuelos);
    GenerarHoteles(cantidadHoteles);
    GenerarPaquetes(cantidadVuelos);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Generacion masiva: " + to_string(cantidadVuelos) + " vuelos, " + to_string(cantidadHoteles) + " hoteles, " + to_string(cantidadPaquetes) + " paquetes");
}
void ControladorPrincipal::GenerarVuelos(int cantidadVuelos) {
	generadorDataset->GenerarVuelosAleatorios(cantidadVuelos, controladorRutas->getRutas(),controladorVuelos);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Genero " + to_string(cantidadVuelos) + " vuelos aleatorios");
}
void ControladorPrincipal::GenerarHoteles(int cantidadHoteles) {
	generadorDataset->GenerarHotelesAleatorios(cantidadHoteles, controladorRutas->getRutas(),controladorHoteles);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Genero " + to_string(cantidadHoteles) + " hoteles aleatorios");
}
void ControladorPrincipal::GenerarPaquetes(int cantidadPaquetes) {
	generadorDataset->GenerarPaquetesAleatorios(cantidadPaquetes, controladorRutas->getRutas(),controladorPaquetes,controladorVuelos->getVuelos(),controladorHoteles->getHoteles());
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Genero " + to_string(cantidadPaquetes) + " paquetes aleatorios");
}
void ControladorPrincipal::AgregarVuelo(string origen, string destino, string escalas, string fecha, float distancia) {
    controladorVuelos->AgregarNuevoVuelo(origen, destino, escalas, fecha, distancia);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Agrego Vuelo: " + origen + " -> " + destino);
}
void ControladorPrincipal::AgregarHotel(string nombre, string ciudad, float puntuacion, float precioNoche) {
    controladorHoteles->AgregarNuevoHotel(nombre, ciudad, puntuacion, precioNoche);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Agrego Hotel: " + nombre + " en " + ciudad);
}
void ControladorPrincipal::AgregarPaquete(Vuelo* vueloIda, Hotel* hotel) {
    controladorPaquetes->AgregarNuevoPaquete(vueloIda, hotel);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Agrego Paquete: Vuelo " + vueloIda->getOrigen() + "->" + vueloIda->getDestino() + " + Hotel " + hotel->getNombre());
}
void ControladorPrincipal::AgregarReserva(Reserva* nuevaReserva) {
    controladorReservas->AgregarReserva(nuevaReserva);
}
void ControladorPrincipal::AgregarUsuario(string nombre, string correo, string password) {
    controladorUsuarios->AgregarUsuario(nombre, correo, password);
}
void ControladorPrincipal::AgregarRuta(string origen, string destino, float distancia) {
    controladorRutas->AgregarNuevaRuta(origen, destino, distancia);
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Agrego Ruta: " + origen + " <-> " + destino);
}
void ControladorPrincipal::EliminarRuta(int indiceRuta) {
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Elimino Ruta ID: " + to_string(indiceRuta));
    
    Ruta* rutaABorrar = controladorRutas->getRutas()->obtenerPos(indiceRuta);
    controladorRutas->getRutas()->eliminaPos(indiceRuta);
    delete rutaABorrar;
    
    GuardarDatosEnArchivos();
}

void ControladorPrincipal::EliminarVuelo(int indiceVuelo) {
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Elimino Vuelo ID: " + to_string(indiceVuelo));
    
    Vuelo* vueloABorrar = controladorVuelos->getVuelos()->obtenerPos(indiceVuelo);
    controladorVuelos->getVuelos()->eliminaPos(indiceVuelo);
    delete vueloABorrar;
    
    GuardarDatosEnArchivos();
}

void ControladorPrincipal::EliminarHotel(int indiceHotel) {
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Elimino Hotel ID: " + to_string(indiceHotel));
    
    
    Hotel* hotelABorrar = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
    controladorHoteles->getHoteles()->eliminaPos(indiceHotel);
    delete hotelABorrar;
    
    GuardarDatosEnArchivos();
}

void ControladorPrincipal::EliminarPaquete(int indicePaquete) {
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Elimino Paquete ID: " + to_string(indicePaquete));
    
    Paquete* paqueteABorrar = controladorPaquetes->getPaquetes()->obtenerPos(indicePaquete);
    controladorPaquetes->getPaquetes()->eliminaPos(indicePaquete);
    delete paqueteABorrar;
    
    GuardarDatosEnArchivos();
}
void ControladorPrincipal::EliminarReserva(int indiceReserva) {

Reserva* reservaACancelar = controladorReservas->getReservasTotales()->obtenerPos(indiceReserva);
    if (reservaACancelar == nullptr) return;

    auto liberarVuelo = [&](ReservaVuelo* resVuelo) {
        if (resVuelo == nullptr) return;
        for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
            Vuelo* v = controladorVuelos->getVuelos()->obtenerPos(i);
            if (v->getOrigen() == resVuelo->getOrigen() && 
                v->getDestino() == resVuelo->getDestino() && 
                v->getFecha() == resVuelo->getFecha()) {
                
                v->getAsientos()->obtenerPos(resVuelo->getAsiento() - 1)->setDisponible(true);
                break;
            }
        }
    };

    auto liberarHotel = [&](ReservaHotel* resHotel) {
        if (resHotel == nullptr) return;
        for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
            Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
            if (h->getNombre() == resHotel->getNombreHotel()) {
                
                h->getHabitaciones()->obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
                break;
            }
        }
    };

    if (reservaACancelar->getTipoReserva() == "VUELO") {
        liberarVuelo(dynamic_cast<ReservaVuelo*>(reservaACancelar));
    }
    else if (reservaACancelar->getTipoReserva() == "HOTEL") {
        liberarHotel(dynamic_cast<ReservaHotel*>(reservaACancelar));
    }
    else if (reservaACancelar->getTipoReserva() == "PAQUETE") {
        ReservaPaquete* resPaq = dynamic_cast<ReservaPaquete*>(reservaACancelar);
        if (resPaq != nullptr) {
            liberarVuelo(resPaq->getVueloReservado());
            liberarHotel(resPaq->getHotelReservado());
        }
    }

    controladorReservas->getReservasTotales()->eliminaPos(indiceReserva);
    delete reservaACancelar;
    GuardarDatosEnArchivos();

    ColorUI::Animaciones::mostrarSpinner("Deshaciendo transaccion y devolviendo recursos", 1200, "");
    ColorUI::Alertas::MostrarExito("Reserva cancelada con exito.");
}
void ControladorPrincipal::EliminarUsuario(int indiceUsuario) {
    controladorRegistros->AgregarRegistro("ADMIN", "admin@chocofly.com", "Administrador", "Elimino Usuario ID: " + to_string(indiceUsuario));
    
    Usuario* usuarioABorrar = controladorUsuarios->getUsuarios()->obtenerPos(indiceUsuario);
    
    controladorUsuarios->getUsuarios()->eliminaPos(indiceUsuario);
    
    delete usuarioABorrar;
    
    GuardarDatosEnArchivos();

}

void ControladorPrincipal::ObtenerIngresosTotales() {
	float ingresosTotales = controladorReservas->CalcularIngresosTotales();
    cout << "Los ingresos totales generados por las reservas son: $" << ingresosTotales << endl;
}
bool ControladorPrincipal::ConsultarVuelos(string origen, string destino) {
    if(controladorVuelos->VerificarVueloDirecto(origen, destino)) {
        cout << endl << "¡Vuelos encontrados para esta ruta!" << endl;
        controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
        return true;
    }
    else {
        Lista<Ruta*>* rutasEncontradas = controladorRutas->BuscarRutaMasCorta(origen, destino);
        if(controladorVuelos->GenerarVuelosConEscala(origen, destino, rutasEncontradas)) {
            controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
            return true;
        }
        return false;
    }
}
bool ControladorPrincipal::VerificarHoteles(string ciudad) {
    for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
        Hotel* aux = controladorHoteles->getHoteles()->obtenerPos(i);
        if (aux->getCiudad() == ciudad) {
            return true;
        }
    }
    return false;
}
bool ControladorPrincipal::VerificarPaquetes(string destino) {
    for (int i = 0; i < controladorPaquetes->getPaquetes()->longitud(); i++) {
        Paquete* aux = controladorPaquetes->getPaquetes()->obtenerPos(i);
        if (aux->getVueloIncluido()->getDestino() == destino) {
            return true;
        }
    }
    return false;
}
void ControladorPrincipal::ComprarTicket(int indiceVuelo, Usuario* userActual, int equipajeBoveda, int equipajeCabina, int asiento, int clase) {
    Vuelo* vueloSeleccionado = controladorVuelos->ObtenerVueloPorPosicion(indiceVuelo);
    if (vueloSeleccionado != nullptr) {
        ReservaVuelo* nuevaReserva = new ReservaVuelo(userActual->getCodigo(), userActual->getNombre(),
            vueloSeleccionado->getOrigen(), vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(),
            vueloSeleccionado->getFecha(), vueloSeleccionado->getDistancia(), equipajeBoveda, 1 + equipajeCabina, clase, asiento, controladorReservas->getReservasTotales()->longitud());
            
        controladorReservas->AgregarReserva(nuevaReserva);
        userActual->getReservas()->agregaFinal(nuevaReserva); 
        controladorRegistros->AgregarRegistro(userActual->getNombre(),userActual->getCorreo(),"Usuario","Reserva (vuelo)");
        
        Lista<Asiento*>* listaAsientos = vueloSeleccionado->getAsientos();
        for (int i = 0; i < listaAsientos->longitud(); i++) {
            if (listaAsientos->obtenerPos(i)->getNumero() == asiento) {
                listaAsientos->obtenerPos(i)->setDisponible(false); 
                break;
            }
        }

        GuardarDatosEnArchivos();
    }
}
void ControladorPrincipal::ReservarHotel(int indiceHotel, Usuario* userActual, string fecha, int noches, int habitacion, int tipoO, int tipoC, int tipoS) {
    Hotel* hotelSeleccionado = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
    if (hotelSeleccionado != nullptr) {
        ReservaHotel* nuevaReserva = new ReservaHotel(userActual->getCodigo(), userActual->getNombre(), hotelSeleccionado->getNombre(),
            hotelSeleccionado->getCiudad(), fecha, hotelSeleccionado->getPrecioBase(), noches, habitacion, tipoO, tipoC, tipoS, controladorReservas->getReservasTotales()->longitud());
            
        controladorReservas->AgregarReserva(nuevaReserva);
        userActual->getReservas()->agregaFinal(nuevaReserva); 
        controladorRegistros->AgregarRegistro(userActual->getNombre(),userActual->getCorreo(),"Usuario","Reserva (hotel)");
        
        Lista<Habitacion*>* listaHabitaciones = hotelSeleccionado->getHabitaciones();
        for (int i = 0; i < listaHabitaciones->longitud(); i++) {
            if (listaHabitaciones->obtenerPos(i)->getNumero() == habitacion) {
                listaHabitaciones->obtenerPos(i)->setDisponible(false);
                break;
            }
        }

        GuardarDatosEnArchivos();
    }
}
bool ControladorPrincipal::VerificarReservas(string codigo) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario()== codigo) {
            return true;
        }
    }
    return false;
}
bool ControladorPrincipal::CancelarReservaUsuario(string codigoUsuario, int indiceReservaLocal) {
    Usuario* userTarget = nullptr;
    for(int i = 0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
        if(controladorUsuarios->getUsuarios()->obtenerPos(i)->getCodigo() == codigoUsuario) {
            userTarget = controladorUsuarios->getUsuarios()->obtenerPos(i);
            break;
        }
    }
    
    if(userTarget == nullptr || indiceReservaLocal < 0 || indiceReservaLocal >= userTarget->getReservas()->longitud()) {
        ColorUI::Alertas::MostrarError("Indice de reserva no valido.");
        return false;
    }

    Reserva* reservaACancelar = userTarget->getReservas()->obtenerPos(indiceReservaLocal);

    if (reservaACancelar->getTipoReserva() == "VUELO") {
        ReservaVuelo* ResVuelo = dynamic_cast<ReservaVuelo*>(reservaACancelar);
        for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
            Vuelo* v = controladorVuelos->getVuelos()->obtenerPos(i);
            if (v->getOrigen() == ResVuelo->getOrigen() && v->getDestino() == ResVuelo->getDestino() && v->getFecha() == ResVuelo->getFecha()) {
                v->getAsientos()->obtenerPos(ResVuelo->getAsiento() - 1)->setDisponible(true);
                break;
            }
        }
    }
    else if (reservaACancelar->getTipoReserva() == "HOTEL") {
        ReservaHotel* resHotel = dynamic_cast<ReservaHotel*>(reservaACancelar);
        for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
            Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
            if (h->getNombre() == resHotel->getNombreHotel()) {
                h->getHabitaciones()->obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
                break;
            }
        }
    }
    else if (reservaACancelar->getTipoReserva() == "PAQUETE") {
        ReservaPaquete* resPaq = dynamic_cast<ReservaPaquete*>(reservaACancelar);
        ReservaVuelo* ReservaVueloIda = resPaq->getVueloReservado();
        if (ReservaVueloIda != nullptr) {
            for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
                Vuelo* v = controladorVuelos->getVuelos()->obtenerPos(i);
                if (v->getOrigen() == ReservaVueloIda->getOrigen() && v->getDestino() == ReservaVueloIda->getDestino() && v->getFecha() == ReservaVueloIda->getFecha()) {
                    v->getAsientos()->obtenerPos(ReservaVueloIda->getAsiento() - 1)->setDisponible(true);
                    break;
                }
            }
        }
        ReservaHotel* resHotel = resPaq->getHotelReservado();
        if (resHotel != nullptr) {
            for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
                Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
                if (h->getNombre() == resHotel->getNombreHotel()) {
                    h->getHabitaciones()->obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
                    break;
                }
            }
        }
    }

    int posGlobal = controladorReservas->getReservasTotales()->getPos(reservaACancelar);
    if(posGlobal < controladorReservas->getReservasTotales()->longitud()) {
        controladorReservas->getReservasTotales()->eliminaPos(posGlobal);
    }
    
    userTarget->getReservas()->eliminaPos(indiceReservaLocal);

    GuardarDatosEnArchivos();
    controladorRegistros->AgregarRegistro(userTarget->getNombre(), "N/A", "Usuario", "Cancelo reserva: " + reservaACancelar->getTipoReserva());
    ColorUI::Animaciones::mostrarSpinner("Deshaciendo transaccion y devolviendo recursos", 1200, "");
    ColorUI::Alertas::MostrarExito("Reserva cancelada con exito.");
    return true;
}
void ControladorPrincipal::CalificarHotel(string nombreHotel, float nuevaPuntuacion) {
    if (nuevaPuntuacion < 1.0f || nuevaPuntuacion > 5.0f) {
        cout << "Por favor, ingresa una puntuacion valida (1.0 a 5.0)." << endl;
        return;
    }

    bool encontrado = false;
    for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
        Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);

        if (h->getNombre() == nombreHotel) {
            float puntuacionAntigua = h->getPuntuacion();

            float puntuacionActualizada = (puntuacionAntigua + nuevaPuntuacion) / 2.0f;
            h->setPuntuacion(puntuacionActualizada);

            GuardarDatosEnArchivos(); 

            controladorRegistros->AgregarRegistro("Usuario", "N/A", "Usuario", "Califico Hotel: " + nombreHotel + " con " + to_string(nuevaPuntuacion) + " estrellas");
            cout << "Gracias por tu calificacion! La calificacion de " << nombreHotel << " ha subido a " << puntuacionActualizada << " estrellas." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) cout << "No pudimos encontrar el hotel mencionado." << endl;
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

    ReservaVuelo* ReservaVueloIda = new ReservaVuelo(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getOrigen(), vueloOferta->getDestino(),
        vueloOferta->getEscalas(), vueloOferta->getFecha(),
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento ,-1
    );

    float precioTotalHotel = hotelOferta->getPrecioBase() * noches;
    ReservaHotel* reservaHotel = new ReservaHotel(
        userActual->getCodigo(), userActual->getNombre(),
        hotelOferta->getNombre(), hotelOferta->getCiudad(),vueloOferta->getFecha(),
        noches, precioTotalHotel,1,1,1,1,.1
    );

    string fechaRetorno = SumarDiasAFecha(vueloOferta->getFecha(), noches);

    ReservaVuelo* ReservaVueloRetorno = new ReservaVuelo(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getDestino(), vueloOferta->getOrigen(), 
        "Directo",SumarDiasAFecha(vueloOferta->getFecha(), noches),
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento,-1
    );

   ReservaPaquete* nuevaReserva = new ReservaPaquete(
        userActual->getCodigo(),
        userActual->getNombre(),
        ReservaVueloIda,
        ReservaVueloRetorno,
        reservaHotel, controladorReservas->getReservasTotales()->longitud()
    );

    controladorReservas->AgregarReserva(nuevaReserva);
    userActual->getReservas()->agregaFinal(nuevaReserva); 
    controladorRegistros->AgregarRegistro(userActual->getNombre(),userActual->getCorreo(),"Usuario","Reserva (paquete)");
    ColorUI::Animaciones::mostrarSpinner("Procesando transaccion con el sistema central", 2000, "");
    cout << "\n"; ColorUI::Alertas::MostrarExito("Reserva de paquete completada exitosamente!");
    cout << "Tu vuelo de retorno ha sido programado automaticamente para el: " << fechaRetorno << endl;
}
void ControladorPrincipal::MostrarAsientos(int indiceVuelo) {
    controladorVuelos->getVuelos()->obtenerPos(indiceVuelo)->MostrarAsientos();
}
void ControladorPrincipal::MostrarHabitaciones(int indiceHabtitacion) {
    controladorHoteles->getHoteles()->obtenerPos(indiceHabtitacion)->MostrarHabitaciones();
}
bool ControladorPrincipal::VerificarAsiento(int numeroAsiento,int indiceVuelo) {
    return controladorVuelos->getVuelos()->obtenerPos(indiceVuelo)->VerificarAsiento(numeroAsiento);
}
bool ControladorPrincipal::VerificarHabitacion(int numeroHabitacion,int indiceHotel) {
    return controladorHoteles->getHoteles()->obtenerPos(indiceHotel)->verificarHabitacion(numeroHabitacion);
}
Usuario* ControladorPrincipal::VerificarInicioSesion(string nombre, string correo, string password) {
    bool existeCuenta = controladorUsuarios->VerificarCuentaExistente(nombre, correo);
    Usuario* usuarioEncontrado = controladorUsuarios->VerificarCredenciales(nombre, correo, password);
    if (usuarioEncontrado != nullptr && existeCuenta) {
        LimpiarConsola();
        ColorUI::Animaciones::mostrarSpinner("Verificando credenciales seguras", 1200, "\t\t\t");
        controladorRegistros->AgregarRegistro(nombre, correo, "Usuario", "Inicio de sesion");
        cout << "\n\n\n"; ColorUI::Alertas::MostrarExito("Inicio de sesion exitoso! Bienvenido, " + usuarioEncontrado->getNombre() + "!", "\t\t\t");
        
        
        Lista<Reserva*>* temp = usuarioEncontrado->getReservas();
        if (temp != nullptr) {
            delete temp; 
        }

        Lista<Reserva*>* aux = new Lista<Reserva*>();
        Lista<Reserva*>* reservasTotales = controladorReservas->getReservasTotales();
        for(unsigned int i = 0; i < reservasTotales->longitud(); i++){
            if(reservasTotales->obtenerPos(i)->getCodigoUsuario() == usuarioEncontrado->getCodigo()) {
                aux->agregaFinal(reservasTotales->obtenerPos(i));
            }
        }
        usuarioEncontrado->setReservas(aux);

        return usuarioEncontrado;
    } else {
        if (existeCuenta) {
            LimpiarConsola();
            controladorRegistros->AgregarRegistro(nombre,correo,"Usuario","Contrasena incorrecta");
            cout << "\n\n\n"; ColorUI::Alertas::MostrarError("Contrasena incorrecta. Por favor, intenta nuevamente.", "\t\t\t");
            pausarConsola();
            return nullptr;
        } else {
            for (int i = 0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
                Usuario* aux = controladorUsuarios->getUsuarios()->obtenerPos(i);
                if (aux->getCorreo() == correo) {
                    LimpiarConsola();
                    controladorRegistros->AgregarRegistro(nombre,correo,"Usuario","registro con correo existente");
                    cout << "\n\n\n"; ColorUI::Alertas::MostrarError("ESTE CORREO YA ESTA REGISTRADO PRUEBE OTRO", "\t\t\t");
                    pausarConsola();
                    return nullptr;
                }
            }
            controladorRegistros->AgregarRegistro(nombre,correo,"Usuario","Nueva cuenta creada");
            controladorUsuarios->AgregarUsuario(nombre, correo, password);
            LimpiarConsola();
            ColorUI::Animaciones::mostrarSpinner("Creando cuenta y asignando espacio en el servidor", 1500, "\t\t\t");
            cout << "\n\n\n"; ColorUI::Alertas::MostrarExito("Cuenta Creada Exitosamente Bienvenido " + nombre + "!", "\t\t\t");
            return controladorUsuarios->getUsuarios()->obtenerFinal();
        }   
    }
    return nullptr;
}


void ControladorPrincipal::GuardarDatosEnArchivos() {
    ControladorArchivos arc;

    ofstream f1("Vuelos.txt", ios::trunc); f1.close();
    for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
        arc.GuardarDatoArchivoVuelos(controladorVuelos->getVuelos()->obtenerPos(i));
    }
    ofstream f2("Hoteles.txt", ios::trunc); f2.close();
    for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
        arc.GuardarDatoArchivoHoteles(controladorHoteles->getHoteles()->obtenerPos(i));
    }
    ofstream f3("Paquetes.txt", ios::trunc); f3.close();
    for (int i = 0; i < controladorPaquetes->getPaquetes()->longitud(); i++) {
        arc.GuardarDatoArchivoPaquetes(controladorPaquetes->getPaquetes()->obtenerPos(i));
    }

    ofstream f4("Usuarios.txt", ios::trunc); f4.close();
    for (int i = 0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
        arc.GuardarDatoArchivoUsuarios(controladorUsuarios->getUsuarios()->obtenerPos(i));
    }
    ofstream f5("Reservas.txt", ios::trunc); f5.close();
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        arc.GuardarDatoArchivoReservas(controladorReservas->getReservasTotales()->obtenerPos(i));
    }
    ofstream f6("Rutas.txt", ios::trunc); f6.close();
    for (int i = 0; i < controladorRutas->getRutas()->longitud(); i++) {
        arc.GardarDatoArchivoRutas(controladorRutas->getRutas()->obtenerPos(i));
    }
}

ControladorHoteles* ControladorPrincipal::getControladorHoteles() { return controladorHoteles; }
ControladorPaquetes* ControladorPrincipal::getControladorPaquetes() { return controladorPaquetes; }
ControladorReservas* ControladorPrincipal::getControladorReservas() { return controladorReservas; }
ControladorVuelos* ControladorPrincipal::getControladorVuelos() { return controladorVuelos; }
ControladorRutas* ControladorPrincipal::getControladorRutas() { return controladorRutas; }
ControladorUsuarios* ControladorPrincipal::getControladorUsuarios() { return controladorUsuarios; }
ControladorRegistros* ControladorPrincipal::getControladorRegistros() { return controladorRegistros; }