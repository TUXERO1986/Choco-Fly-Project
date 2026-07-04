#include "ControladorPrincipal.h"
ControladorPrincipal::ControladorPrincipal() {
	controladorRutas = new ControladorRutas();
	controladorHoteles = new ControladorHoteles();
	controladorReservas = new ControladorReservas();
	controladorVuelos = new ControladorVuelos();
	controladorPaquetes = new ControladorPaquetes();
	controladorUsuarios = new ControladorUsuarios();
    controladorRegistros= new ControladorRegistros();
}
ControladorPrincipal::~ControladorPrincipal() {
	delete controladorRutas;
	delete controladorHoteles;
	delete controladorReservas	;
	delete controladorPaquetes;
}
void ControladorPrincipal::GenerarDatos(int cantidadVuelos, int cantidadHoteles, int cantidadPaquetes) {
	generadorDataset->GenerarTodo(cantidadVuelos,cantidadHoteles,cantidadPaquetes,controladorRutas->getRutas());
    
}
void ControladorPrincipal::GenerarVuelos(int cantidadVuelos) {
	generadorDataset->GenerarVuelosAleatorios(cantidadVuelos, controladorRutas->getRutas());
}
void ControladorPrincipal::GenerarHoteles(int cantidadHoteles) {
	generadorDataset->GenerarHotelesAleatorios(cantidadHoteles, controladorRutas->getRutas());
}
void ControladorPrincipal::GenerarPaquetes(int cantidadPaquetes) {
	generadorDataset->GenerarPaquetesAleatorios(cantidadPaquetes, controladorRutas->getRutas());
}
void ControladorPrincipal::AgregarVuelo(string origen, string destino, string escalas, string fecha, float distancia) {
    controladorVuelos->AgregarNuevoVuelo(origen, destino, escalas, fecha, distancia);
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
                h->getHabitaciones()->
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
template<typename T>
void ControladorPrincipal::ConsultarCatalogoDinamico(Lista<T*>* lista, string titulo, std::function<bool(T*)> criterio) {
    MostrarResultadosPaginados<T>(
        lista, 
        titulo, 
        criterio, 
        [](T* item, int indice) {
            ColorUI::printGradient("  [ ID: " + to_string(indice) + " ]", { "#FFD700", "#FF4500" }, false, true);
            item->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FilrarVuelosPorOrigenDestino(string origen, string destino) {
    controladorVuelos->FiltrarVuelosPorOrigenDestino(origen, destino);
}
void ControladorPrincipal::FiltrarUsuariosPorNombre(string nombreBusqueda) {
    MostrarResultadosPaginados<Usuario>(
        controladorUsuarios->getUsuarios(), 
        "FILTRO DE USUARIOS POR NOMBRE: " + nombreBusqueda, 
        [nombreBusqueda](Usuario* u) { return u->getNombre() == nombreBusqueda; },
        [](Usuario* u, int indice) {
            ColorUI::printGradient("  [ ID DEL USUARIO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            u->MostrarDatosAdmin();
        }
    );
}
void ControladorPrincipal::FiltrarRutasPorOrigen(string ciudadBusqueda) {
    MostrarResultadosPaginados<Ruta>(
        controladorRutas->getRutas(), 
        "RUTAS CON ORIGEN: " + ciudadBusqueda, 
        [ciudadBusqueda](Ruta* r) { return r->getOrigen() == ciudadBusqueda; },
        [](Ruta* r, int indice) {
            ColorUI::printGradient("  [ ID DE RUTA: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            r->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarRutasPorDestino(string ciudadBusqueda) {
    MostrarResultadosPaginados<Ruta>(
        controladorRutas->getRutas(), 
        "RUTAS CON DESTINO: " + ciudadBusqueda, 
        [ciudadBusqueda](Ruta* r) { return r->getDestino() == ciudadBusqueda; },
        [](Ruta* r, int indice) {
            ColorUI::printGradient("  [ ID DE RUTA: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            r->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarHotelesPorCiudad(string ciudadBusqueda) {
    MostrarResultadosPaginados<Hotel>(
        controladorHoteles->getHoteles(), 
        "HOTELES EN: " + ciudadBusqueda, 
        [ciudadBusqueda](Hotel* h) { return h->getCiudad() == ciudadBusqueda; },
        [](Hotel* h, int indice) {
            ColorUI::printGradient("  [ ID DEL HOTEL: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            h->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarPaquetesPorDestino(string ciudadBusqueda) {
    MostrarResultadosPaginados<Paquete>(
        controladorPaquetes->getPaquetes(), 
        "PAQUETES CON DESTINO: " + ciudadBusqueda, 
        [ciudadBusqueda](Paquete* p) { return p->getVueloIncluido()->getDestino() == ciudadBusqueda; },
        [](Paquete* p, int indice) {
            ColorUI::printGradient("  [ ID DEL PAQUETE: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            p->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarPaquetesPorOrigen(string ciudadBusqueda) {
    MostrarResultadosPaginados<Paquete>(
        controladorPaquetes->getPaquetes(), 
        "PAQUETES CON ORIGEN: " + ciudadBusqueda, 
        [ciudadBusqueda](Paquete* p) { return p->getVueloIncluido()->getOrigen() == ciudadBusqueda; },
        [](Paquete* p, int indice) {
            ColorUI::printGradient("  [ ID DEL PAQUETE: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            p->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarVuelosPorFecha(string fechaBusqueda) {
    MostrarResultadosPaginados<Vuelo>(
        controladorVuelos->getVuelos(), 
        "VUELOS EN LA FECHA: " + fechaBusqueda, 
        [fechaBusqueda](Vuelo* v) { return v->getFecha() == fechaBusqueda; },
        [](Vuelo* v, int indice) {
            ColorUI::printGradient("  [ ID DEL VUELO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            v->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FitrarVuelosPorOrigen(string origenBusqueda) {
    MostrarResultadosPaginados<Vuelo>(
        controladorVuelos->getVuelos(), 
        "VUELOS CON ORIGEN: " + origenBusqueda, 
        [origenBusqueda](Vuelo* v) { return v->getOrigen() == origenBusqueda; },
        [](Vuelo* v, int indice) {
            ColorUI::printGradient("  [ ID DEL VUELO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            v->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarVuelosPorDestino(string destinoBusqueda) {
    MostrarResultadosPaginados<Vuelo>(
        controladorVuelos->getVuelos(), 
        "VUELOS CON DESTINO: " + destinoBusqueda, 
        [destinoBusqueda](Vuelo* v) { return v->getDestino() == destinoBusqueda; },
        [](Vuelo* v, int indice) {
            ColorUI::printGradient("  [ ID DEL VUELO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            v->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarReservasPorTipo(string tipo) {
    MostrarResultadosPaginados<Reserva>(
        controladorReservas->getReservasTotales(), 
        "RESERVAS DE TIPO: " + tipo, 
        [tipo](Reserva* r) { return r->getTipoReserva() == tipo; },
        [](Reserva* r, int indice) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(indice) + "]\n", ColorUI::Paletas::MoradoD, false);
            r->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarReservasPorUsuario(string codigoUsuario) {
    MostrarResultadosPaginados<Reserva>(
        controladorReservas->getReservasTotales(), 
        "RESERVAS DEL USUARIO: " + codigoUsuario, 
        [codigoUsuario](Reserva* r) { return r->getCodigoUsuario() == codigoUsuario; },
        [](Reserva* r, int indice) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(indice) + "]\n", ColorUI::Paletas::MoradoD, false);
            r->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarReservasPorTipoUsuario(string tipoBusqueda, string codigousuario) {
    MostrarResultadosPaginados<Reserva>(
        controladorReservas->getReservasTotales(), 
        "RESERVAS DE TIPO " + tipoBusqueda + " (USUARIO: " + codigousuario + ")", 
        [tipoBusqueda, codigousuario](Reserva* r) { return r->getCodigoUsuario() == codigousuario && r->getTipoReserva() == tipoBusqueda; },
        [](Reserva* r, int indice) {
            ColorUI::printGradient("\n[ID RESERVA #" + to_string(indice) + "]\n", ColorUI::Paletas::MoradoD, false);
            r->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarVuelosPorPresupuesto(float presupuestoMaximo) {
    MostrarResultadosPaginados<Vuelo>(
        controladorVuelos->getVuelos(), 
        "VUELOS HASTA $" + to_string(presupuestoMaximo), 
        [presupuestoMaximo](Vuelo* v) { return v->getPrecioBase() <= presupuestoMaximo; },
        [](Vuelo* v, int indice) {
            cout << "Vuelo #" << indice << " | Precio Desde: $" << v->getPrecioBase() << endl;
            v->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarHotelesPorPresupuesto(float presupuestoMaximo) {
    MostrarResultadosPaginados<Hotel>(
        controladorHoteles->getHoteles(), 
        "HOTELES HASTA $" + to_string(presupuestoMaximo), 
        [presupuestoMaximo](Hotel* h) { return h->getPrecioBase() <= presupuestoMaximo; },
        [](Hotel* h, int indice) {
            cout << "Hotel #" << indice << " | Precio Desde: $" << h->getPrecioBase() << endl;
            h->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarPaquetesPorPresupuesto(float presupuestoMaximo) {
    MostrarResultadosPaginados<Paquete>(
        controladorPaquetes->getPaquetes(), 
        "PAQUETES HASTA $" + to_string(presupuestoMaximo), 
        [presupuestoMaximo](Paquete* p) { return p->getPrecioBase() <= presupuestoMaximo; },
        [](Paquete* p, int indice) {
            cout << "Paquete #" << indice << " | Precio Desde: $" << p->getPrecioBase() << endl;
            p->MostrarDatos();
        }
    );
}
void ControladorPrincipal::FiltrarHotelesPorMayorCalificacion() {
    Lista<Hotel*>* originales = controladorHoteles->getHoteles();
    int n = originales->longitud();
    if (n == 0) {
        ColorUI::Alertas::MostrarInfo("No hay hoteles.");
        return;
    }

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

    MostrarResultadosPaginados<Hotel>(
        temp, 
        "HOTELES: DE MAYOR A MENOR CALIFICACION", 
        [](Hotel* h) { return true; },
        [](Hotel* h, int indice) {
            cout << "[ID PARA COMPRA: " << h->getId() << "]" << endl;
            h->MostrarDatos();
        }
    );
    delete temp; 
}

void ControladorPrincipal::FiltrarVuelosDeMayorAMenorPrecio() {
    ArbolAVL<Vuelo*>* arbolVuelos = controladorVuelos->getVuelosMenorPrecio();
    Lista<Vuelo*>* temp = new Lista<Vuelo*>();
    arbolVuelos->RecorrerInOrden([temp](Vuelo* v) {
        temp->agregaFinal(v);
    });

    MostrarResultadosPaginados<Vuelo>(
        temp, 
        "VUELOS: DE MAYOR A MENOR PRECIO", 
        [](Vuelo* v) { return true; },
        [](Vuelo* v, int indice) {
            cout << "[ID PARA COMPRA: " << v->getId() << "]" << endl;
            v->MostrarDatos();
        }
    );
    delete temp;
}

void ControladorPrincipal::FiltrarHotelesDeMayorAMenorPrecio() {
    ArbolAVL<Hotel*>* arbolHoteles = controladorHoteles->getHotelesMenorPrecio();
    Lista<Hotel*>* temp = new Lista<Hotel*>();
    arbolHoteles->RecorrerInOrden([temp](Hotel* h) {
        temp->agregaFinal(h);
    });

    MostrarResultadosPaginados<Hotel>(
        temp, 
        "HOTELES: DE MAYOR A MENOR PRECIO", 
        [](Hotel* h) { return true; },
        [](Hotel* h, int indice) {
            cout << "[ID PARA COMPRA: " << h->getId() << "]" << endl;
            h->MostrarDatos();
        }
    );
    delete temp;
}

void ControladorPrincipal::FiltrarPaquetesDeMayorAMenorPrecio() {
    ArbolAVL<Paquete*>* arbolPaquetes = controladorPaquetes->getPaquetesMenorPrecio();
    Lista<Paquete*>* temp = new Lista<Paquete*>();
    arbolPaquetes->RecorrerInOrden([temp](Paquete* p) {
        temp->agregaFinal(p);
    });

    MostrarResultadosPaginados<Paquete>(
        temp, 
        "PAQUETES: DE MAYOR A MENOR PRECIO", 
        [](Paquete* p) { return true; },
        [](Paquete* p, int indice) {
            cout << "[ID PARA COMPRA: " << p->getId() << "]" << endl;
            p->MostrarDatos();
        }
    );
    delete temp;
}
void ControladorPrincipal::FiltrarUsuarioPorCodigo(string codigo) {
    MostrarResultadosPaginados<Usuario>(
        controladorUsuarios->getUsuarios(), 
        "FILTRO DE USUARIOS POR CODIGO: " + codigo, 
        [codigo](Usuario* u) { return u->getCodigo() == codigo; },
        [](Usuario* u, int indice) {
            ColorUI::printGradient("  [ ID DEL USUARIO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            u->MostrarDatosAdmin();
        }
    );
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
        controladorReservas->AgregarReserva(new ReservaVuelo(userActual->getCodigo(), userActual->getNombre(),
            vueloSeleccionado->getOrigen(), vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(),
            vueloSeleccionado->getFecha(), vueloSeleccionado->getDistancia(), equipajeBoveda, 1 + equipajeCabina, clase, asiento,controladorReservas->getReservasTotales()->longitud()));
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
void ControladorPrincipal::ReservarHotel(int indiceHotel, Usuario* userActual, string fecha,int noches, int habitacion, int tipoO, int tipoC, int tipoS) {
    Hotel* hotelSeleccionado = controladorHoteles->getHoteles()->obtenerPos(indiceHotel);
    if (hotelSeleccionado != nullptr) {

        controladorReservas->AgregarReserva(new ReservaHotel(userActual->getCodigo(), userActual->getNombre(), hotelSeleccionado->getNombre(),
            hotelSeleccionado->getCiudad(), fecha,hotelSeleccionado->getPrecioBase(), noches, habitacion, tipoO, tipoC, tipoS,controladorReservas->getReservasTotales()->longitud()));
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
                h->getHabitaciones()->
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
        reservaHotel,controladorReservas->getReservasTotales()->longitud()
    );

    controladorReservas->AgregarReserva(nuevaReserva);
    controladorRegistros->AgregarRegistro(userActual->getNombre(),userActual->getCorreo(),"Usuario","Reserva (paquete)");
    ColorUI::Animaciones::mostrarSpinner("Procesando transaccion con el sistema central", 2000, "");
    cout << "\n"; ColorUI::Alertas::MostrarExito("Reserva de paquete completada exitosamente!");
    cout << "Tu vuelo de retorno ha sido programado automaticamente para el: " << fechaRetorno << endl;
}
void ControladorPrincipal::MostrarReservasUsuario(Usuario* userActual) {
    for (int i = 0; i < controladorReservas->getReservasTotales()->longitud(); i++) {
        Reserva* aux = controladorReservas->getReservasTotales()->obtenerPos(i);
        if (aux->getCodigoUsuario() == userActual->getCodigo()) {
            cout << "Reserva #" << i << ":" << endl;
            aux->MostrarDatos();
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
    return controladorVuelos->getVuelos()->obtenerPos(indiceVuelo)->VerificarAsiento(numeroAsiento);
}
bool ControladorPrincipal::VerificarHabitacion(int numeroHabitacion,int indiceHotel) {
    return controladorHoteles->getHoteles()->obtenerPos(indiceHotel)->verificarHabitacion(numeroHabitacion);
}
Usuario* ControladorPrincipal::VerificarInicioSesion(string nombre, string correo, string password) {
	bool existeCuenta = controladorUsuarios->VerificarCuentaExistente(nombre, correo);
    Usuario* usuarioEncontrado = controladorUsuarios->VerificarCredenciales(nombre, correo, password);
    if (usuarioEncontrado != nullptr&&existeCuenta) {
        LimpiarConsola();
        ColorUI::Animaciones::mostrarSpinner("Verificando credenciales seguras", 1200, "\t\t\t");
                    controladorRegistros->AgregarRegistro(nombre,correo,"Usuario","Inicio de sesion");
		cout << "\n\n\n"; ColorUI::Alertas::MostrarExito("Inicio de sesion exitoso! Bienvenido, " + usuarioEncontrado->getNombre() + "!", "\t\t\t");

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
                    controladorRegistros->AgregarRegistro(nombre,correo,"Usuario","registro con correoe existente");
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