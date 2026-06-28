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
void ControladorPrincipal::EliminarRuta(int indiceRuta) {
	controladorRutas->getRutas()->eliminaPos(indiceRuta);
    GuardarDatosEnArchivos();
}
void ControladorPrincipal::EliminarVuelo(int indiceVuelo) {
	controladorVuelos->getVuelos()->eliminaPos(indiceVuelo);
    GuardarDatosEnArchivos();
}
void ControladorPrincipal::EliminarHotel(int indiceHotel) {
	controladorHoteles->getHoteles()->eliminaPos(indiceHotel);
    GuardarDatosEnArchivos();
}
void ControladorPrincipal::EliminarPaquete(int indicePaquete) {
	controladorPaquetes->getPaquetes()->eliminaPos(indicePaquete);
    GuardarDatosEnArchivos();
}
void ControladorPrincipal::EliminarReserva(int indiceReserva) {

    Reserva* reservaACancelar = controladorReservas->
        getReservasTotales()->obtenerPos(indiceReserva);

    if (reservaACancelar->getTipoReserva() == "VUELO") {
        ReservaVuelo* ResVuelo= dynamic_cast<ReservaVuelo*>(reservaACancelar);

        for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
            Vuelo* v = controladorVuelos->getVuelos()->obtenerPos(i);
            if (v->getOrigen() == ResVuelo->getOrigen() && v->getDestino() ==
                ResVuelo->getDestino() && v->getFecha() == ResVuelo->getFecha()) {

                v->getControladorAsientos()->getAsientos()->obtenerPos(ResVuelo->getAsiento() - 1)->setDisponible(true);
                break;
            }
        }
    }
    else if (reservaACancelar->getTipoReserva() == "HOTEL") {
        ReservaHotel* resHotel = dynamic_cast<ReservaHotel*>(reservaACancelar);

        for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
            Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
            if (h->getNombre() == resHotel->getNombreHotel()) {
                h->getControladorHabitaciones()->getHabitaciones()->
                    obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
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

                if (v->getOrigen() == ReservaVueloIda->getOrigen() &&
                    v->getDestino() == ReservaVueloIda->getDestino() &&
                    v->getFecha() == ReservaVueloIda->getFecha()) {

                    v->getControladorAsientos()->getAsientos()->obtenerPos(ReservaVueloIda->getAsiento() - 1)->setDisponible(true);
                    break;
                }
            }
        }

        ReservaHotel* resHotel = resPaq->getHotelReservado();
        if (resHotel != nullptr) {
            for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
                Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
                if (h->getNombre() == resHotel->getNombreHotel()) {

                    h->getControladorHabitaciones()->getHabitaciones()->obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
                    break;
                }
            }
        }

    }

    controladorReservas->getReservasTotales()->eliminaPos(indiceReserva);

    GuardarDatosEnArchivos();

    ColorUI::Animaciones::mostrarSpinner("Deshaciendo transaccion y devolviendo recursos", 1200, "");
    ColorUI::Alertas::MostrarExito("Reserva cancelada con exito.");
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
void ControladorPrincipal::FiltrarReservasPorTipo(string tipo) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getTipoReserva() == tipo) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(i) + "]\n", ColorUI::Paletas::MoradoD, false);
            aux->MostrarReserva();
        }
    }
}
void ControladorPrincipal::FiltrarReservasPorUsuario(string codigoUsuario) {
    for(int i=0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == codigoUsuario) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(i) + "]\n", ColorUI::Paletas::MoradoD, false);
            aux->MostrarReserva();
        }
    }
}
void ControladorPrincipal::FiltrarReservasPorTipoUsuario(string tipoBusqueda, string codigousuario) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == codigousuario && aux->getTipoReserva() == tipoBusqueda) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(i) + "]\n", ColorUI::Paletas::MoradoD, false);
            aux->MostrarReserva();
        }
    }
}
void ControladorPrincipal::FiltrarVuelosPorPresupuesto(float presupuestoMaximo) {
    bool encontrados = false;
    cout << "\n=== HOTELES CON PRECIO POR NOCHES POR DEBAJO DE $" << presupuestoMaximo << " (PRECIO POR NOCHE) ===" << endl;

    for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
        Hotel* hotel = controladorHoteles->getHoteles()->obtenerPos(i);

        float precioBaseEstimado = hotel->getPrecioNoche();

        if (precioBaseEstimado <= presupuestoMaximo) {
            cout << "Vuelo #" << i << " | Precio Desde: $" << precioBaseEstimado << endl;
            hotel->MostrarHotel();
            cout << "-----------------------------------" << endl;
            encontrados = true;
        }
    }

    if (!encontrados) {
        cout << "No hay vuelos disponibles para ese presupuesto." << endl;
    }
}
void ControladorPrincipal::FiltrarHotelesPorPresupuesto(float presupuestoMaximo) {
    bool encontrados = false;
    cout << "\n=== VUELOS POR DEBAJO DE $" << presupuestoMaximo << " (Precio Base) ===" << endl;

    for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
        Vuelo* vuelo = controladorVuelos->getVuelos()->obtenerPos(i);

        float precioBaseEstimado = vuelo->getPrecioBase();

        if (precioBaseEstimado <= presupuestoMaximo) {
            cout << "Vuelo #" << i << " | Precio Desde: $" << precioBaseEstimado << endl;
            vuelo->MostrarVuelo();
            cout << "-----------------------------------" << endl;
            encontrados = true;
        }
    }

    if (!encontrados) {
        cout << "No hay vuelos disponibles para ese presupuesto." << endl;
    }
}
void ControladorPrincipal::FiltrarPaquetesPorPresupuesto(float presupuestoMaximo) {
    bool encontrados = false;
    cout << "\n=== PAQUETES POR DEBAJO DE $" << presupuestoMaximo << " (Precio Base) ===" << endl;

    for (int i = 0; i < controladorPaquetes->getPaquetes()->longitud(); i++) {
        Paquete* paquete = controladorPaquetes->getPaquetes()->obtenerPos(i);

        float precioBaseEstimado = paquete->getPrecioBase();

        if (precioBaseEstimado <= presupuestoMaximo) {
            cout << "Vuelo #" << i << " | Precio Desde: $" << precioBaseEstimado << endl;
            paquete->MostrarPaquete();
            cout << "-----------------------------------" << endl;
            encontrados = true;
        }
    }

    if (!encontrados) {
        cout << "No hay vuelos disponibles para ese presupuesto." << endl;
    }
}
void ControladorPrincipal::FiltrarHotelesPorMayorCalificacion() {
    Lista<Hotel*>* originales = controladorHoteles->getHoteles();
    int n = originales->longitud();
    if (n == 0) return;

    Lista<Hotel*>* temp = new Lista<Hotel*>();
    for (int i = 0; i < n; i++) temp->agregaFinal(originales->obtenerPos(i));

 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp->obtenerPos(j)->getPuntuacion() < temp->obtenerPos(j + 1)->getPuntuacion()) {
         
                Hotel* aux = temp->obtenerPos(j);
                temp->modificarPos(temp->obtenerPos(j + 1), j);
                temp->modificarPos(aux, j + 1);
            }
        }
    }

    cout << "\n=== HOTELES: DE MAYOR A MENOR CALIFICACION ===" << endl;
    for (int i = 0; i < n; i++) {
        Hotel* h = temp->obtenerPos(i);
        cout << "[ID PARA COMPRA: " << originales->getPos(h) << "]" << endl;
        h->MostrarHotel();
        cout << "-----------------------------------" << endl;
    }
    delete temp; 
}

void ControladorPrincipal::FiltrarVuelosDeMayorAMenorPrecio() {
 ArbolAVL<Vuelo*>* arbolVuelos = controladorVuelos->getVuelosMenorPrecio();
    
    cout << "\n=== VUELOS: DE MAYOR A MENOR PRECIO POR NOCHE ===" << endl;

    arbolVuelos->RecorrerInOrden([](Vuelo* v) {

        cout << "[ID PARA COMPRA: " << v->getId() << "]" << endl;
        v->MostrarVuelo();
        cout << "-----------------------------------" << endl;
    });
}

void ControladorPrincipal::FiltrarHotelesDeMayorAMenorPrecio() {
ArbolAVL<Hotel*>* arbolHoteles = controladorHoteles->getHotelesMenorPrecio();
    
    cout << "\n=== HOTELES: DE MAYOR A MENOR PRECIO POR NOCHE ===" << endl;

    arbolHoteles->RecorrerInOrden([](Hotel* h) {

        cout << "[ID PARA COMPRA: " << h->getId() << "]" << endl;
        h->MostrarHotel();
        cout << "-----------------------------------" << endl;
    });
}

void ControladorPrincipal::FiltrarPaquetesDeMayorAMenorPrecio() {
    ArbolAVL<Hotel*>* arbolHoteles = controladorHoteles->getHotelesMenorPrecio();
    
    cout << "\n=== PAQUETES: DE MAYOR A MENOR PRECIO POR NOCHE ===" << endl;

    arbolHoteles->RecorrerInOrden([](Hotel* h) {

        cout << "[ID PARA COMPRA: " << h->getId() << "]" << endl;
        h->MostrarHotel();
        cout << "-----------------------------------" << endl;
    });
}
void ControladorPrincipal::FiltrarUsuarioPorCodigo(string codigo) {
    for (int i = 0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
        Usuario* aux = controladorUsuarios->getUsuarios()->obtenerPos(i);
        if (aux->getCodigo() == codigo) {
            aux->MostrarDatosUsuarios();
            break;
        }
    }
}
void ControladorPrincipal::ObtenerIngresosTotales() {
	float ingresosTotales = controladorReservas->CalcularIngresosTotales();
    cout << "Los ingresos totales generados por las reservas son: $" << ingresosTotales << endl;
}
bool ControladorPrincipal::ConsultarVuelos(string origen, string destino) {
    if(controladorVuelos->VerificarVueloDirecto(origen, destino)) {
        cout << endl<<"¡Hay un vuelos directo disponible!" << endl;
        controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
        return true ;
    }
    else {
        Lista<Ruta*>* rutasEncontradas = controladorRutas->BuscarRutaMasCorta(origen, destino);
        if(controladorVuelos->GenerarVuelosConEscala(origen, destino, rutasEncontradas)) 
            controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
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
void ControladorPrincipal::ComprarTicket(int indiceVuelo, Usuario* usuariActual, int equipajeBoveda, int equipajeCabina, int asiento, int clase) {
    Vuelo* vueloSeleccionado = controladorVuelos->ObtenerVueloPorPosicion(indiceVuelo);
    if (vueloSeleccionado != nullptr) {
        controladorReservas->AgregarReserva(new ReservaVuelo(usuariActual->getCodigo(), usuariActual->getNombre(),
            vueloSeleccionado->getOrigen(), vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(),
            vueloSeleccionado->getFecha(), vueloSeleccionado->getDistancia(), equipajeBoveda, 1 + equipajeCabina, clase, asiento));

        Lista<Asiento*>* listaAsientos = vueloSeleccionado->getControladorAsientos()->getAsientos();
        for (int i = 0; i < listaAsientos->longitud(); i++) {
            if (listaAsientos->obtenerPos(i)->getNumero() == asiento) {
                listaAsientos->obtenerPos(i)->setDisponible(false); 
                break;
            }
        }

        GuardarDatosEnArchivos();
    }
}
void ControladorPrincipal::ReservarHotel(int indiceHotel, Usuario* userActual, string fecha,int noches, int habitacion, int tipoO, int tipoC, int tipoS) {
    Hotel* hotelSeleccionado = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
    if (hotelSeleccionado != nullptr) {

        controladorReservas->AgregarReserva(new ReservaHotel(userActual->getCodigo(), userActual->getNombre(), hotelSeleccionado->getNombre(),
            hotelSeleccionado->getCiudad(), fecha,hotelSeleccionado->getPrecioNoche(), noches, habitacion, tipoO, tipoC, tipoS));

        Lista<Habitacion*>* listaHabitaciones = hotelSeleccionado->getControladorHabitaciones()->getHabitaciones();
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

    int contadorUsuario = 0;
    int indiceGlobal = -1;
    Reserva* reservaACancelar = nullptr;

    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        if (controladorReservas->getReservasTotales()->obtenerPos(i)->getCodigoUsuario() == codigoUsuario) {
            if (contadorUsuario == indiceReservaLocal) {
                indiceGlobal = i;
                reservaACancelar = controladorReservas->getReservasTotales()->obtenerPos(i);
                break;
            }
            contadorUsuario++;
        }
    }

    if (indiceGlobal == -1) {
        ColorUI::Alertas::MostrarError("Indice de reserva no valido.");
        return false;
    }

    if (reservaACancelar->getTipoReserva() == "VUELO") {
        ReservaVuelo* ResVuelo = dynamic_cast<ReservaVuelo*>(reservaACancelar);

        for (int i = 0; i < controladorVuelos->getVuelos()->longitud(); i++) {
            Vuelo* v = controladorVuelos->getVuelos()->obtenerPos(i);
            if (v->getOrigen() == ResVuelo->getOrigen() && v->getDestino() == 
                ResVuelo->getDestino() && v->getFecha() == ResVuelo->getFecha()) {

                v->getControladorAsientos()->getAsientos()->obtenerPos(ResVuelo->getAsiento() - 1)->setDisponible(true);
                break;
            }
        }
    }
    else if (reservaACancelar->getTipoReserva() == "HOTEL") {
        ReservaHotel* resHotel = dynamic_cast<ReservaHotel*>(reservaACancelar);

        for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
            Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
            if (h->getNombre() == resHotel->getNombreHotel()) {
                h->getControladorHabitaciones()->getHabitaciones()->
                    obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
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

                if (v->getOrigen() == ReservaVueloIda->getOrigen() &&
                    v->getDestino() == ReservaVueloIda->getDestino() &&
                    v->getFecha() == ReservaVueloIda->getFecha()) {

                    v->getControladorAsientos()->getAsientos()->obtenerPos(ReservaVueloIda->getAsiento() - 1)->setDisponible(true);
                    break;
                }
            }
        }

        ReservaHotel* resHotel = resPaq->getHotelReservado();
        if (resHotel != nullptr) {
            for (int i = 0; i < controladorHoteles->getHoteles()->longitud(); i++) {
                Hotel* h = controladorHoteles->getHoteles()->obtenerPos(i);
                if (h->getNombre() == resHotel->getNombreHotel()) {
                    h->getControladorHabitaciones()->getHabitaciones()->obtenerPos(resHotel->getHabitacion() - 1)->setDisponible(true);
                    break;
                }
            }
        }

    }

    controladorReservas->getReservasTotales()->eliminaPos(indiceGlobal);

    GuardarDatosEnArchivos();
    ColorUI::Animaciones::mostrarSpinner("Deshaciendo transaccion y devolviendo recursos", 1200, "");
    return true;
    ColorUI::Alertas::MostrarExito("Reserva cancelada con exito.");
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
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento 
    );

    float precioTotalHotel = hotelOferta->getPrecioNoche() * noches;
    ReservaHotel* reservaHotel = new ReservaHotel(
        userActual->getCodigo(), userActual->getNombre(),
        hotelOferta->getNombre(), hotelOferta->getCiudad(),vueloOferta->getFecha(),
        noches, precioTotalHotel,1,1,1,1
    );

    string fechaRetorno = SumarDiasAFecha(vueloOferta->getFecha(), noches);

    ReservaVuelo* ReservaVueloRetorno = new ReservaVuelo(
        userActual->getCodigo(), userActual->getNombre(),
        vueloOferta->getDestino(), vueloOferta->getOrigen(), 
        "Directo",SumarDiasAFecha(vueloOferta->getFecha(), noches),
        vueloOferta->getDistancia(), maletasBodegaIda, 1,maletasBodegaRetorno,asiento
    );

    ReservaPaquete* nuevaReserva = new ReservaPaquete(
        userActual->getCodigo(),
        userActual->getNombre(),
        ReservaVueloIda,
        ReservaVueloRetorno,
        reservaHotel
    );

    controladorReservas->AgregarReserva(nuevaReserva);

    ColorUI::Animaciones::mostrarSpinner("Procesando transaccion con el sistema central", 2000, "");
    cout << "\n"; ColorUI::Alertas::MostrarExito("Reserva de paquete completada exitosamente!");
    cout << "Tu vuelo de retorno ha sido programado automaticamente para el: " << fechaRetorno << endl;
}
void ControladorPrincipal::MostrarReservasUsuario(Usuario* userActual) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == userActual->getCodigo()) {
            cout << "Reserva #" << i << ":" << endl;
            aux->MostrarReserva();
            cout << endl;
        }
    }
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
        LimpiarConsola();
        ColorUI::Animaciones::mostrarSpinner("Verificando credenciales seguras", 1200, "\t\t\t");
		cout << "\n\n\n"; ColorUI::Alertas::MostrarExito("Inicio de sesion exitoso! Bienvenido, " + usuarioEncontrado->getNombre() + "!", "\t\t\t");

        return usuarioEncontrado;
    } else {
        if (existeCuenta) {
			LimpiarConsola();
			cout << "\n\n\n"; ColorUI::Alertas::MostrarError("Contrasena incorrecta. Por favor, intenta nuevamente.", "\t\t\t");
            pausarConsola();
            return nullptr;
    
        } else {
            for (int i = 0; i < controladorUsuarios->getUsuarios()->longitud(); i++) {
                Usuario* aux = controladorUsuarios->getUsuarios()->obtenerPos(i);
                if (aux->getCorreo() == correo) {
                    LimpiarConsola();
					cout << "\n\n\n"; ColorUI::Alertas::MostrarError("ESTE CORREO YA ESTA REGISTRADO PRUEBE OTRO", "\t\t\t");
                    pausarConsola();
                    return nullptr;
                }
            }
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