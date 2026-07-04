#include "AdminPantallas.h"
#include "AnimacionConsola.h"

using namespace std;
using namespace ColorUI;

AdminPantallas::AdminPantallas(ControladorPrincipal* ptrPrincipal) {
    principal = ptrPrincipal;
}
void AdminPantallas::MenuAgregar() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Agregar Vuelo Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[2] Agregar Hotel Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[3] Agregar Ruta Nueva", Exito, false);
        ColorUI::printGradient("\n\t\t\t[4] Agregar Paquete Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[5] Agregar Reserva Nueva", Exito, false);
        ColorUI::printGradient("\n\t\t\t[6] Agregar Usuario Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);

        opcion = _getch();
        LimpiarConsola();

        switch (opcion) {
        case '1': {
            string origen, destino, escalas, fecha;
            float distancia;

            ColorUI::printGradient("\t=== NUEVO VUELO ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tOrigen: ", Exito, false, false);

            cin >> ws; getline(cin, origen);
            ColorUI::printGradient("\tDestino: ", Exito, false, false);
            getline(cin, destino);
            ColorUI::printGradient("\tEscalas (Ej. 'Directo' o 'Lima-Bogota'): ", Exito, false, false);
            getline(cin, escalas);
            ColorUI::printGradient("\tFecha (Ej. 15-05-2026): ", Exito, false, false);
            getline(cin, fecha);
            ColorUI::printGradient("\tDistancia en KM: ", Exito, false, false);

            while (!(cin >> distancia)) {
                cin.clear();
                cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido para la distancia: ", Alerta, false, false);
            }
            cin.ignore(1000, '\n');

            AnimacionConsola::BarraProgresoAvion("Guardando vuelo en el sistema", 800);
            principal->AgregarVuelo(origen, destino, escalas, fecha, distancia);

            cout << "\n";
            Alertas::MostrarExito("Vuelo agregado exitosamente a la base de datos.");
            pausarConsola();
        } break;

        case '2': {
            string nombre, ciudad;
            float puntuacion, precio;

            ColorUI::printGradient("\t=== NUEVO HOTEL ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tNombre del Hotel: ", Exito, false, false);
            cin >> ws; getline(cin, nombre);
            ColorUI::printGradient("\tCiudad: ", Exito, false, false);
            getline(cin, ciudad);

            ColorUI::printGradient("\tPuntuacion (Ej. 4.5): ", Exito, false, false);
            while (!(cin >> puntuacion)) {
                cin.clear(); cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido: ", Alerta, false, false);
            }

            ColorUI::printGradient("\tPrecio por noche: $", Exito, false, false);
            while (!(cin >> precio)) {
                cin.clear(); cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido: ", Alerta, false, false);
            }
            cin.ignore(1000, '\n');

            AnimacionConsola::BarraProgresoAvion("Guardando hotel en el sistema", 800);
            principal->AgregarHotel(nombre, ciudad, puntuacion, precio);

            cout << "\n";
            Alertas::MostrarExito("Hotel agregado exitosamente a la base de datos.");
            pausarConsola();
        } break;

        case '3': {
            string origen, destino;
            float distancia;
            ColorUI::printGradient("\t=== NUEVA RUTA CONEXION ===", TemaPrincipal, false);
            ColorUI::printGradient("\n\tCiudad Origen: ", Exito, false, false);
            cin >> ws; getline(cin, origen);
            ColorUI::printGradient("\tCiudad Destino: ", Exito, false, false);
            getline(cin, destino);
            ColorUI::printGradient("\tDistancia (Km): ", Exito, false, false);
            distancia = LeerOpcion();

            AnimacionConsola::BarraProgresoAvion("Registrando ruta de conexion", 1000);
            principal->AgregarRuta(origen, destino, distancia);
            Alertas::MostrarExito("Ruta conectada exitosamente.");
            pausarConsola();
        } break;
        case '4': {
            ColorUI::printGradient("\t=== AGREGAR PAQUETE ===", TemaPrincipal, false);
            
            Lista<Vuelo*>* listaVuelos = principal->getControladorVuelos()->getVuelos();
            if (listaVuelos->longitud() == 0) {
                ColorUI::printGradient("\nNo hay vuelos disponibles para crear un paquete.\n", Alerta, false);
                pausarConsola();
                break;
            }
            principal->ConsultarCatalogoDinamico<Vuelo>(listaVuelos, "SELECCION DE VUELO PARA PAQUETE", [](Vuelo* v){return true;});

            ColorUI::printGradient("\nIngresa el ID del vuelo a incluir: ", Exito, false, false);
            int idxVuelo = LeerOpcion();
            if (idxVuelo < 0 || idxVuelo >= listaVuelos->longitud()) {
                ColorUI::printGradient("\nIndice de vuelo invalido.\n", Alerta, false);
                pausarConsola();
                break;
            }

            Lista<Hotel*>* listaHoteles = principal->getControladorHoteles()->getHoteles();
            if (listaHoteles->longitud() == 0) {
                ColorUI::printGradient("\nNo hay hoteles disponibles para crear un paquete.\n", Alerta, false);
                pausarConsola();
                break;
            }
            principal->ConsultarCatalogoDinamico<Hotel>(listaHoteles, "SELECCION DE HOTEL PARA PAQUETE", [](Hotel* h){return true;});

            ColorUI::printGradient("\nIngresa el ID del hotel a incluir: ", Exito, false, false);
            int idxHotel = LeerOpcion();
            if (idxHotel < 0 || idxHotel >= listaHoteles->longitud()) {
                ColorUI::printGradient("\nIndice de hotel invalido.\n", Alerta, false);
                pausarConsola();
                break;
            }

            Vuelo* vueloSel = listaVuelos->obtenerPos(idxVuelo);
            Hotel* hotelSel = listaHoteles->obtenerPos(idxHotel);
            if (hotelSel->getCiudad() != vueloSel->getDestino()) {
                ColorUI::printGradient("\nAdvertencia: la ciudad del hotel no coincide con el destino del vuelo.\n", Alerta, false);
                ColorUI::printGradient("Presiona '1' para continuar de todas formas o cualquier otra tecla para cancelar: ", Alerta, false, false);
                char conf = _getch();
                if (conf != '1') {
                    ColorUI::printGradient("\nOperacion cancelada.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
            }

            principal->AgregarPaquete(vueloSel, hotelSel);
            ColorUI::printGradient("\nPaquete agregado correctamente.\n", gege, false);
            pausarConsola();
        }break;
        case '5': {
            ColorUI::printGradient("\t=== AGREGAR RESERVA ===", TemaPrincipal, false);
         
            Lista<Usuario*>* listaUsuarios = principal->getControladorUsuarios()->getUsuarios();
            if (listaUsuarios->longitud() == 0) {
                ColorUI::printGradient("\nNo hay usuarios registrados. Crea un usuario primero.\n", Alerta, false);
                pausarConsola();
                break;
            }
            
            principal->ConsultarCatalogoDinamico<Usuario>(listaUsuarios, "SELECCION DE USUARIO PARA RESERVA", [](Usuario* u){return true;});
            ColorUI::printGradient("\nIngresa el ID del usuario: ", Exito, false, false);
            int idxUser = LeerOpcion();
            if (idxUser < 0 || idxUser >= listaUsuarios->longitud()) {
                ColorUI::printGradient("\nIndice de usuario invalido.\n", Alerta, false);
                pausarConsola();
                break;
            }
            Usuario* usuarioSel = listaUsuarios->obtenerPos(idxUser);

            ColorUI::printGradient("\nTipo de reserva: [1] VUELO | [2] HOTEL | [3] PAQUETE\nElige: ", Exito, false, false);
            int tipo = LeerOpcion();

            if (tipo == 1) {
                Lista<Vuelo*>* listaVuelos = principal->getControladorVuelos()->getVuelos();
                if (listaVuelos->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay vuelos disponibles.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                principal->ConsultarCatalogoDinamico<Vuelo>(listaVuelos, "SELECCION DE VUELO", [](Vuelo* v){return true;});
                ColorUI::printGradient("\nID de vuelo a reservar: ", Exito, false, false);
                int idxV = LeerOpcion();
                if (idxV < 0 || idxV >= listaVuelos->longitud()) {
                    ColorUI::printGradient("\nIndice de vuelo invalido.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                ColorUI::printGradient("\nEquipaje bodega (cantidad): ", Exito, false, false);
                int eqB = LeerOpcion();
                ColorUI::printGradient("\nEquipaje cabina (cantidad): ", Exito, false, false);
                int eqC = LeerOpcion();
                ColorUI::printGradient("\nAsiento (numero): ", Exito, false, false);
                int asiento = LeerOpcion();
                ColorUI::printGradient("\nClase (1=Economy,2=Business...): ", Exito, false, false);
                int clase = LeerOpcion();

                principal->ComprarTicket(idxV, usuarioSel, eqB, eqC, asiento, clase);
                ColorUI::printGradient("\nTicket reservado correctamente.\n", gege, false);
                pausarConsola();
            }
            else if (tipo == 2) {
                Lista<Hotel*>* listaHoteles = principal->getControladorHoteles()->getHoteles();
                if (listaHoteles->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay hoteles disponibles.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                principal->ConsultarCatalogoDinamico<Hotel>(listaHoteles, "SELECCION DE HOTEL", [](Hotel* h){return true;});
                ColorUI::printGradient("\nID de hotel a reservar: ", Exito, false, false);
                int idxH = LeerOpcion();
                if (idxH < 0 || idxH >= listaHoteles->longitud()) {
                    ColorUI::printGradient("\nIndice de hotel invalido.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                string fecha;
                ColorUI::printGradient("\nFecha ingreso (Ej. 15-05-2026): ", Exito, false, false);
                getline(cin, fecha);
                ColorUI::printGradient("\nNoches: ", Exito, false, false);
                int noches = LeerOpcion();
                ColorUI::printGradient("\nNumero de habitacion: ", Exito, false, false);
                int habitacion = LeerOpcion();
                ColorUI::printGradient("\nTipo O (int): ", Exito, false, false);
                int tipoO = LeerOpcion();
                ColorUI::printGradient("\nTipo C (int): ", Exito, false, false);
                int tipoC = LeerOpcion();
                ColorUI::printGradient("\nTipo S (int): ", Exito, false, false);
                int tipoS = LeerOpcion();

                principal->ReservarHotel(idxH, usuarioSel, fecha, noches, habitacion, tipoO, tipoC, tipoS);
                ColorUI::printGradient("\nReserva de hotel creada correctamente.\n", gege, false);
                pausarConsola();
            }
            else if (tipo == 3) {
                Lista<Paquete*>* listaPaquetes = principal->getControladorPaquetes()->getPaquetes();
                if (listaPaquetes->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay paquetes disponibles.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                principal->ConsultarCatalogoDinamico<Paquete>(listaPaquetes, "SELECCION DE PAQUETE", [](Paquete* p){return true;});
                ColorUI::printGradient("\nID de paquete a reservar: ", Exito, false, false);
                int idxP = LeerOpcion();
                if (idxP < 0 || idxP >= listaPaquetes->longitud()) {
                    ColorUI::printGradient("\nIndice de paquete invalido.\n", Alerta, false);
                    pausarConsola();
                    break;
                }
                ColorUI::printGradient("\nNoches: ", Exito, false, false);
                int noches = LeerOpcion();
                ColorUI::printGradient("\nMaletas bodega ida: ", Exito, false, false);
                int maletasIda = LeerOpcion();
                ColorUI::printGradient("\nMaletas bodega retorno: ", Exito, false, false);
                int maletasRet = LeerOpcion();
                ColorUI::printGradient("\nClase (int): ", Exito, false, false);
                int claseP = LeerOpcion();
                ColorUI::printGradient("\nAsiento (numero): ", Exito, false, false);
                int asientoP = LeerOpcion();

                principal->ReservarPaquete(idxP, usuarioSel, noches, maletasIda, maletasRet, claseP, asientoP);
                ColorUI::printGradient("\nReserva de paquete creada correctamente.\n", gege, false);
                pausarConsola();
            }
            else {
                ColorUI::printGradient("\nTipo de reserva invalido.\n", Alerta, false);
                pausarConsola();
            }
        }break;
        case '6': {//agregar usuario
            ColorUI::printGradient("\t=== AGREGAR USUARIO ===", TemaPrincipal, false);
            string nombre, correo, password;
            ColorUI::printGradient("\nNombre: ", Exito, false, false);
            cin >> ws; getline(cin, nombre);
            ColorUI::printGradient("\nCorreo: ", Exito, false, false);
            getline(cin, correo);
            ColorUI::printGradient("\nPassword: ", Exito, false, false);
            getline(cin, password);

            principal->AgregarUsuario(nombre, correo, password);
            ColorUI::printGradient("\nUsuario agregado correctamente.\n", gege, false);
            pausarConsola();
        }break;
        case '0': return;
        }
    } while (true);
}
int AdminPantallas::LeerOpcion() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        ColorUI::printGradient("\tError: Ingresa un numero valido: ", Alerta, false, false);
    }
    cin.ignore(1000, '\n');
    return x;
}
void AdminPantallas::MenuPrincipalAdmin() {
    char opcion;
    do {
        LimpiarConsola();
        cout << BLINK;
        ColorUI::printGradient(PanelControlADM, Tux, false);
        cout << RESET;
        gotoxy(0, 8);
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Reportes y Base de Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Mantenimiento (Agregar Datos)", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Generacion Masiva de Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[0] Cerrar Sesion", Alerta, false);

        opcion = _getch();

        switch (opcion) {
        case '1': MenuReportes(); break;
        case '2': MenuMantenimiento(); break;
        case '3': GenerarDatosAleatorios(); break;
        case '0':
            LimpiarConsola();
            return;
            break;
        default: break;
        }
    } while (opcion != '4');
}
void AdminPantallas::MenuReportes() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient(reportesADM, MoradoD, false);
        gotoxy(0, 8);
        cout << endl;
        ColorUI::printGradient("\n\t\t[1] FILTRAR VUELOS", Exito, false);
        ColorUI::printGradient("\n\t\t[2] FILTRAR HOTELES", Exito, false);
        ColorUI::printGradient("\n\t\t[3] FILTRAR PAQUETES", Exito, false);
        ColorUI::printGradient("\n\t\t[4] FILTRAR RUTAS", Exito, false);
        ColorUI::printGradient("\n\t\t[5] FILTRAR RESERVAS", Exito, false);
        ColorUI::printGradient("\n\t\t[6] FILTRAR USUARIOS REGISTRADOS", Exito, false);
        ColorUI::printGradient("\n\t\t[7] VER INGRESOS TOTALES", Exito, false);
        ColorUI::printGradient("\n\t\t[0] Volver", Alerta, false);

        opcion = _getch();
        LimpiarConsola();

        switch (opcion) {
        case '1': MenuFiltrosVuelos();break;
        case '2': MenuFiltrosHoteles(); break;
        case '3': MenuFiltrosPaquetes(); break;
        case '4': FiltroRutas(); break;
        case '5': MenuFiltrosReservas(); break;
        case '6': MenuFiltrosUsuarios(); break;
        case '7':
            principal->ObtenerIngresosTotales();
            cout << "\n";
            pausarConsola();
            break;
        case '0': return;
        }
    } while (true);
}
void AdminPantallas::FiltroRutas() {
    LimpiarConsola();
    ColorUI::printGradient("=== FILTRAR RUTAS ===", TemaPrincipal, false);
    ColorUI::printGradient("\n[1]Filtrar rutas por Origen: ", Exito, false, false);
    ColorUI::printGradient("\n[2]Filtrar rutas por Destino: ", Exito, false, false);
    ColorUI::printGradient("\n[3]Mostrar todas las rutas: ", Exito, false, false);
    ColorUI::printGradient("\n[0]Salir", Exito, false, false);
    cout << "\n";

    char opcion = _getch();
    switch (opcion) {
    case '1': {
        string ciudadBusqueda;
        ColorUI::printGradient("\nDigite el origen a filtrar (ej. Lima): ", Exito, false, false);
        getline(cin, ciudadBusqueda);
        if (ciudadBusqueda.empty()) {
            ColorUI::printGradient("\nNo ingresaste un origen. Se mostraron todas las rutas.\n", Alerta, false);
            principal->ConsultarCatalogoDinamico<Ruta>(principal->getControladorRutas()->getRutas(), "TODAS LAS RUTAS", [](Ruta* r){ return true; });
        }
        else {
            principal->ConsultarCatalogoDinamico<Ruta>(
                principal->getControladorRutas()->getRutas(),
                "RUTAS DESDE: " + ciudadBusqueda,
                [ciudadBusqueda](Ruta* r){ return r->getOrigen() == ciudadBusqueda; }
            );
        }
        pausarConsola();
    } break;
    case '2': {
        string ciudadBusqueda;
        ColorUI::printGradient("\nDigite el destino a filtrar (ej. Lima): ", Exito, false, false);
        getline(cin, ciudadBusqueda);
        if (ciudadBusqueda.empty()) {
            ColorUI::printGradient("\nNo ingresaste un destino. Se mostraron todas las rutas.\n", Alerta, false);
            principal->ConsultarCatalogoDinamico<Ruta>(principal->getControladorRutas()->getRutas(), "TODAS LAS RUTAS", [](Ruta* r){ return true; });
        }
        else {
            principal->ConsultarCatalogoDinamico<Ruta>(
                principal->getControladorRutas()->getRutas(),
                "RUTAS HACIA: " + ciudadBusqueda,
                [ciudadBusqueda](Ruta* r){ return r->getDestino() == ciudadBusqueda; }
            );
        }
        pausarConsola();
    } break;
    case '3':
        principal->ConsultarCatalogoDinamico<Ruta>(principal->getControladorRutas()->getRutas(), "TODAS LAS RUTAS", [](Ruta* r){ return true; });
        pausarConsola();
        break;
    case '4':
    case '0':
        return;
    }
}
void AdminPantallas::MenuFiltrosReservas() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient("\n================FILTROS RESERVAS==============", Exito, false);
        ColorUI::printGradient("\n[1] RESERVAS POR TIPO", Exito, false);
        ColorUI::printGradient("\n[2] RESERVAS POR TIPO USUARIO", Exito, false);
        ColorUI::printGradient("\n[3] RESERVAS POR USUARIO", Exito, false);
        ColorUI::printGradient("\n[4] MOSTRAR TODAS LAS RESERVAS", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string reserva;
            cout << "Digite el tipo de reservas a buscar (VUELO-HOTEL-PAQUETE): " << endl; cin >> reserva; cin.ignore();
            principal->ConsultarCatalogoDinamico<Reserva>(
                principal->getControladorReservas()->getReservasTotales(),
                "RESERVAS TIPO: " + reserva,
                [reserva](Reserva* r){ return r->getTipoReserva() == reserva; }
            );
            pausarConsola();
            break;
        }
        case '2': {
            string reserva, codigousuario;
            cout << "Digite el tipo de reservas a buscar (VUELO-HOTEL-PAQUETE): " << endl; cin >> reserva; cin.ignore();
            principal->ConsultarCatalogoDinamico<Usuario>(principal->getControladorUsuarios()->getUsuarios(), "LISTA DE USUARIOS", [](Usuario* u){ return true; });
            cout << "Digite el codigo de usuario: " << endl; cin >> codigousuario; cin.ignore();
            
            principal->ConsultarCatalogoDinamico<Reserva>(
                principal->getControladorReservas()->getReservasTotales(),
                "RESERVAS TIPO: " + reserva + " | USUARIO: " + codigousuario,
                [reserva, codigousuario](Reserva* r){ return r->getTipoReserva() == reserva && r->getCodigoUsuario() == codigousuario; }
            );
            pausarConsola();
            break;
        }
        case '3': {
            string codigousuario;
            principal->ConsultarCatalogoDinamico<Usuario>(principal->getControladorUsuarios()->getUsuarios(), "LISTA DE USUARIOS", [](Usuario* u){ return true; });
            cout << "Digite el codigo de usuario: " << endl; cin >> codigousuario; cin.ignore();
            
            principal->ConsultarCatalogoDinamico<Reserva>(
                principal->getControladorReservas()->getReservasTotales(),
                "RESERVAS DEL USUARIO: " + codigousuario,
                [codigousuario](Reserva* r){ return r->getCodigoUsuario() == codigousuario; }
            );
            pausarConsola();
            break;
        }
        case '4': {
            principal->ConsultarCatalogoDinamico<Reserva>(principal->getControladorReservas()->getReservasTotales(), "TODAS LAS RESERVAS", [](Reserva* r){ return true; });
            pausarConsola();
            break;
        }
        case '0': {
            return;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosVuelos() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient("\n================FILTROS VUELOS==============", Exito, false);
        ColorUI::printGradient("\n[1] VUELOS POR ORIGEN", Exito, false);
        ColorUI::printGradient("\n[2] VUELOS POR DESTINO", Exito, false);
        ColorUI::printGradient("\n[3] VUELOS POR FECHA", Exito, false);
        ColorUI::printGradient("\n[4] VUELOS POR PRESUPUESTO", Exito, false);
        ColorUI::printGradient("\n[5] MOSTRAR TODOS LOS VUELOS", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
      case '1': {
            vector<string> origenes;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string o = vuelos->obtenerPos(i)->getOrigen();
                bool existe = false;
                for(string& org : origenes) { if(org == o) existe = true; }
                if(!existe) origenes.push_back(o);
            }
            if (origenes.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE ORIGEN ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<origenes.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << origenes[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= origenes.size()) {
                string origen = origenes[sel-1];
                principal->ConsultarCatalogoDinamico<Vuelo>(vuelos, "VUELOS DESDE: "+origen,[origen](Vuelo* v){return v->getOrigen()==origen;});
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '2': {
            vector<string> destinos;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string o = vuelos->obtenerPos(i)->getDestino();
                bool existe = false;
                for(string& org : destinos) { if(org == o) existe = true; }
                if(!existe) destinos.push_back(o);
            }
            if (destinos.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<destinos.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << destinos[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= destinos.size()) {
                Lista<Vuelo*>* temp = principal->getControladorVuelos()->getVuelos();
                string destino = destinos[sel-1];
                principal->ConsultarCatalogoDinamico<Vuelo>(temp,"VUELOS A "+destino,[destino](Vuelo* v){return v->getDestino()==destino;});
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '3': {
            vector<string> fechas;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string f = vuelos->obtenerPos(i)->getFecha();
                bool existe = false;
                for(string& org : fechas) { if(org == f) existe = true; }
                if(!existe) fechas.push_back(f);
            }
            if (fechas.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE FECHA ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<fechas.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << fechas[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= fechas.size()) {
                string fecha=fechas[sel-1];
                principal->ConsultarCatalogoDinamico<Vuelo>(vuelos,"VUELOS EN LA FECHA: "+fecha,[fecha](Vuelo* v){return v->getFecha()==fecha;});
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '4': {
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO\n", Exito, false); cin >> presupuesto; cin.ignore();
            principal->ConsultarCatalogoDinamico<Vuelo>(principal->getControladorVuelos()->getVuelos(),
            "VUELOS DESDE: "+to_string(presupuesto)+"$",[presupuesto](Vuelo* v){return v->getPrecioBase()<=presupuesto;});
            pausarConsola();
            break;
        }
        case '5': {

            principal->ConsultarCatalogoDinamico<Vuelo>(principal->getControladorVuelos()->getVuelos(),
            "VUELOS DISPONIBLES: ",[](Vuelo* v){return true;});
            pausarConsola();
            break;
        }
        case '0': {
            return;
            break;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosPaquetes() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient("\n================FILTROS PAQUETES==============", Exito, false);
        ColorUI::printGradient("\n[1] PAQUETES POR ORIGEN", Exito, false);
        ColorUI::printGradient("\n[2] PAQUETES POR DESTINO", Exito, false);
        ColorUI::printGradient("\n[3] MOSTRAR TODOS LOS PAQUETES", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string origen;
            cout << "Digite el origen: " << endl; getline(cin, origen);
            principal->ConsultarCatalogoDinamico<Paquete>(
                principal->getControladorPaquetes()->getPaquetes(),
                "PAQUETES CON ORIGEN: " + origen,
                [origen](Paquete* p){ return p->getVueloIncluido()->getOrigen() == origen; }
            );
            pausarConsola();
            break;
        }
        case '2': {
            string destino;
            cout << "Digite el destino: " << endl; getline(cin, destino);
            principal->ConsultarCatalogoDinamico<Paquete>(
                principal->getControladorPaquetes()->getPaquetes(),
                "PAQUETES CON DESTINO: " + destino,
                [destino](Paquete* p){ return p->getVueloIncluido()->getDestino() == destino; }
            );
            pausarConsola();
            break;
        }
        case '3': {
            principal->ConsultarCatalogoDinamico<Paquete>(principal->getControladorPaquetes()->getPaquetes(), "TODOS LOS PAQUETES", [](Paquete* p){ return true; });
            pausarConsola();
            break;
        }
        case '0': {
            return;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosHoteles() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient("\n================FILTROS HOTELES==============", Exito, false);
        ColorUI::printGradient("\n[1] HOTELES POR CIUDAD", Exito, false);
        ColorUI::printGradient("\n[2] MOSTRAR TODOS LOS HOTELES", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string ciudad;
            cout << "Digite la ciudad: " << endl; getline(cin, ciudad);
            principal->ConsultarCatalogoDinamico<Hotel>(
                principal->getControladorHoteles()->getHoteles(),
                "HOTELES EN: " + ciudad,
                [ciudad](Hotel* h){ return h->getCiudad() == ciudad; }
            );
            pausarConsola();
            break;
        }
        case '2': {
            principal->ConsultarCatalogoDinamico<Hotel>(principal->getControladorHoteles()->getHoteles(), "TODOS LOS HOTELES", [](Hotel* h){ return true; });
            pausarConsola();
            break;
        }
        case '0': {
            return;
        }
        }
    } while (true);
}

void AdminPantallas::MenuFiltrosUsuarios() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient("\n================FILTROS USUARIOS==============", Exito, false);
        ColorUI::printGradient("\n[1] FILTRAR USUARIOS POR NOMBRE", Exito, false);
        ColorUI::printGradient("\n[2] MOSTRAR TODOS LOS USUARIOS", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string nombre;
            cout << "Digite el nombre: " << endl; cin >> nombre; cin.ignore();
            principal->ConsultarCatalogoDinamico<Usuario>(
                principal->getControladorUsuarios()->getUsuarios(),
                "USUARIOS CON NOMBRE: " + nombre,
                [nombre](Usuario* u){ return u->getNombre() == nombre; }
            );
            pausarConsola();
            break;
        }
        case '2': {
            principal->ConsultarCatalogoDinamico<Usuario>(principal->getControladorUsuarios()->getUsuarios(), "TODOS LOS USUARIOS REGISTRADOS", [](Usuario* u){ return true; });
            pausarConsola();
            break;
        }
        case '0': {
            return;
        }
        }
    } while (true);
}
void AdminPantallas::MenuMantenimiento() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Agregar Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t[2] Eliminar Datos", Alerta, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);
        opcion = _getch();
        LimpiarConsola();
        switch (opcion) {
        case '1': MenuAgregar(); break;
        case '2': MenuEliminar(); break;
        case '0': return;
        default: break;
        }
    } while (true);
}
void AdminPantallas::GenerarDatosAleatorios() {
    LimpiarConsola();
    ColorUI::printGradient(datos, dato, false);
    gotoxy(0, 8);
    cout << "\n\tEsta opcion llenara la base de datos con informacion de prueba.\n";
    cout << "\tPresiona '1' para confirmar o '0' para cancelar.\n";

    char confirmacion = _getch();
    if (confirmacion == '1') {
        int cantidad;
        cout << "\tDigite la cantidad de datos a generar: "; cin >> cantidad; cin.ignore();
        AnimacionConsola::BarraProgresoAvion("Generando e inyectando datos aleatorios masivos", 2500, "\t");
        principal->GenerarDatos(cantidad, cantidad, cantidad);
        ColorUI::printGradient("\n\tDatos generados con exito!\n", gege, false);
    }
    else {
        ColorUI::printGradient("\n\tOperacion cancelada.\n", Alerta, false);
    }
    pausarConsola();
}
void AdminPantallas::MenuEliminar() {
    char opcion;
    do {
        LimpiarConsola();
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Eliminar un Registro (Vuelo/Hotel/etc)", Alerta, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);

        opcion = _getch();
        LimpiarConsola();
        switch (opcion) {
        case '1': {
            ColorUI::printGradient(eliminacion, Alerta, false);
            gotoxy(0, 7);
            ColorUI::printGradient("\n\n\t\t\t[1] Vuelo | [2] Hotel | [3] Usuario", Exito, false, false);
            ColorUI::printGradient("\n\n\t\t\t[4] Reserva | [5] Ruta |[0] Cancelar\n\t\t\tOpcion: ", Exito, false, false);
            char delOpt = _getch();

            if (delOpt == '0') break;
            LimpiarConsola();
            
            if (delOpt == '1') {
                principal->ConsultarCatalogoDinamico<Vuelo>(principal->getControladorVuelos()->getVuelos(), "CATALOGO DE VUELOS (SELECCIONE ID PARA ELIMINAR)", [](Vuelo* v){return true;});
            } else if (delOpt == '2') {
                principal->ConsultarCatalogoDinamico<Hotel>(principal->getControladorHoteles()->getHoteles(), "CATALOGO DE HOTELES (SELECCIONE ID PARA ELIMINAR)", [](Hotel* h){return true;});
            } else if (delOpt == '3') {
                principal->ConsultarCatalogoDinamico<Usuario>(principal->getControladorUsuarios()->getUsuarios(), "CATALOGO DE USUARIOS (SELECCIONE ID PARA ELIMINAR)", [](Usuario* u){return true;});
            } else if (delOpt == '4') {
                principal->ConsultarCatalogoDinamico<Reserva>(principal->getControladorReservas()->getReservasTotales(), "CATALOGO DE RESERVAS GLOBALES (SELECCIONE ID PARA ELIMINAR)", [](Reserva* r){return true;});
            } else if (delOpt == '5') {
                principal->ConsultarCatalogoDinamico<Ruta>(principal->getControladorRutas()->getRutas(), "CATALOGO DE RUTAS (SELECCIONE ID PARA ELIMINAR)", [](Ruta* r){return true;});
            }

            cout << "\n\n\t\t\tIngresa el ID numerico a eliminar: ";
            int idTarget = LeerOpcion();

            if (delOpt == '1') principal->EliminarVuelo(idTarget);
            else if (delOpt == '2') principal->EliminarHotel(idTarget);
            else if (delOpt == '3') principal->EliminarUsuario(idTarget);
            else if (delOpt == '4') principal->EliminarReserva(idTarget);
            else if (delOpt == '5') principal->EliminarRuta(idTarget);

            ColorUI::printGradient("\n\t\t\tRegistro eliminado (si el ID era valido).\n", gege, false);
            pausarConsola();
        } break;

        case '0': return;
        }
    } while (true);
}