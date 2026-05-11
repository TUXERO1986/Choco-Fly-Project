#include "AdminPantallas.h"
#include <iostream>
#include "Windows.h"

using namespace std;
using namespace ColorUI;

AdminPantallas::AdminPantallas(ControladorPrincipal* ptrPrincipal) {
    principal = ptrPrincipal;
}
void AdminPantallas::MenuAgregar() {
    char opcion;
    do {
        system("cls");
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
        system("cls");

        switch (opcion) {
        case '1': {
            string origen, destino, escalas, fecha;
            float distancia;

            ColorUI::printGradient("\t=== NUEVO VUELO ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tOrigen: ", Exito, false, false);
            
            
            
            
            
            getline(cin, origen);
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

            principal->AgregarVuelo(origen, destino, escalas, fecha, distancia);

            cout << "\n";
            ColorUI::printGradient("\tVuelo agregado exitosamente a la base de datos.\n", gege, false);
            system("pause>0");
        } break;

        case '2': {
            string nombre, ciudad;
            float puntuacion, precio;

            ColorUI::printGradient("\t=== NUEVO HOTEL ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tNombre del Hotel: ", Exito, false, false);
            getline(cin, nombre);
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

            principal->AgregarHotel(nombre, ciudad, puntuacion, precio);

            cout << "\n";
            ColorUI::printGradient("\tHotel agregado exitosamente a la base de datos.\n", gege, false);
            system("pause>0");
        } break;

        case '3': {
            string origen, destino;
            float distancia;
            ColorUI::printGradient("\t=== NUEVA RUTA CONEXION ===", TemaPrincipal, false);
            ColorUI::printGradient("\n\tCiudad Origen: ", Exito, false, false);
            getline(cin, origen);
            ColorUI::printGradient("\tCiudad Destino: ", Exito, false, false);
            getline(cin, destino);
            ColorUI::printGradient("\tDistancia (Km): ", Exito, false, false);
            distancia = LeerOpcion();

            principal->AgregarRuta(origen, destino, distancia);
            ColorUI::printGradient("\n\tRuta conectada exitosamente.\n", gege, false);
            system("pause>0");
        } break;
        case '4': {
     
            ColorUI::printGradient("\t=== AGREGAR PAQUETE ===", TemaPrincipal, false);
            cout << "\n\nVuelos disponibles:\n";
            Lista<Vuelo*>* listaVuelos = principal->getControladorVuelos()->getVuelos();
            if (listaVuelos->longitud() == 0) {
                ColorUI::printGradient("\nNo hay vuelos disponibles para crear un paquete.\n", Alerta, false);
                system("pause>0");
                break;
            }
            for (int i = 0; i < listaVuelos->longitud(); i++) {
                cout << "[" << i << "] ";
                listaVuelos->obtenerPos(i)->MostrarVuelo();
                cout << "------------------------\n";
            }

            ColorUI::printGradient("\nIngresa el indice del vuelo a incluir: ", Exito, false, false);
            int idxVuelo = LeerOpcion();
            if (idxVuelo < 0 || idxVuelo >= listaVuelos->longitud()) {
                ColorUI::printGradient("\nIndice de vuelo invalido.\n", Alerta, false);
                system("pause>0");
                break;
            }


            cout << "\nHoteles disponibles:\n";
            Lista<Hotel*>* listaHoteles = principal->getControladorHoteles()->getHoteles();
            if (listaHoteles->longitud() == 0) {
                ColorUI::printGradient("\nNo hay hoteles disponibles para crear un paquete.\n", Alerta, false);
                system("pause>0");
                break;
            }
            for (int i = 0; i < listaHoteles->longitud(); i++) {
                cout << "[" << i << "] ";
                listaHoteles->obtenerPos(i)->MostrarHotel();
                cout << "------------------------\n";
            }

            ColorUI::printGradient("\nIngresa el indice del hotel a incluir: ", Exito, false, false);
            int idxHotel = LeerOpcion();
            if (idxHotel < 0 || idxHotel >= listaHoteles->longitud()) {
                ColorUI::printGradient("\nIndice de hotel invalido.\n", Alerta, false);
                system("pause>0");
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
                    system("pause>0");
                    break;
                }
            }

            principal->AgregarPaquete(vueloSel, hotelSel);
            ColorUI::printGradient("\nPaquete agregado correctamente.\n", gege, false);
            system("pause>0");
        }break;
        case '5': {
            ColorUI::printGradient("\t=== AGREGAR RESERVA ===", TemaPrincipal, false);
         
            Lista<Usuario*>* listaUsuarios = principal->getControladorUsuarios()->getUsuarios();
            if (listaUsuarios->longitud() == 0) {
                ColorUI::printGradient("\nNo hay usuarios registrados. Crea un usuario primero.\n", Alerta, false);
                system("pause>0");
                break;
            }
            cout << "\nUsuarios:\n";
            for (int i = 0; i < listaUsuarios->longitud(); i++) {
                Usuario* u = listaUsuarios->obtenerPos(i);
                cout << "[" << i << "] " << u->getNombre() << " | " << u->getCorreo() << " | " << u->getCodigo() << "\n";
            }
            ColorUI::printGradient("\nIngresa el indice del usuario: ", Exito, false, false);
            int idxUser = LeerOpcion();
            if (idxUser < 0 || idxUser >= listaUsuarios->longitud()) {
                ColorUI::printGradient("\nIndice de usuario invalido.\n", Alerta, false);
                system("pause>0");
                break;
            }
            Usuario* usuarioSel = listaUsuarios->obtenerPos(idxUser);

           
            ColorUI::printGradient("\nTipo de reserva: [1] VUELO | [2] HOTEL | [3] PAQUETE\nElige: ", Exito, false, false);
            int tipo = LeerOpcion();

            if (tipo == 1) {
             
                Lista<Vuelo*>* listaVuelos = principal->getControladorVuelos()->getVuelos();
                if (listaVuelos->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay vuelos disponibles.\n", Alerta, false);
                    system("pause>0");
                    break;
                }
                cout << "\nVuelos:\n";
                for (int i = 0; i < listaVuelos->longitud(); i++) {
                    cout << "[" << i << "] ";
                    listaVuelos->obtenerPos(i)->MostrarVuelo();
                    cout << "------------------------\n";
                }
                ColorUI::printGradient("\nIndice de vuelo a reservar: ", Exito, false, false);
                int idxV = LeerOpcion();
                if (idxV < 0 || idxV >= listaVuelos->longitud()) {
                    ColorUI::printGradient("\nIndice de vuelo invalido.\n", Alerta, false);
                    system("pause>0");
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
                system("pause>0");
            }
            else if (tipo == 2) {
                
                Lista<Hotel*>* listaHoteles = principal->getControladorHoteles()->getHoteles();
                if (listaHoteles->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay hoteles disponibles.\n", Alerta, false);
                    system("pause>0");
                    break;
                }
                cout << "\nHoteles:\n";
                for (int i = 0; i < listaHoteles->longitud(); i++) {
                    cout << "[" << i << "] ";
                    listaHoteles->obtenerPos(i)->MostrarHotel();
                    cout << "------------------------\n";
                }
                ColorUI::printGradient("\nIndice de hotel a reservar: ", Exito, false, false);
                int idxH = LeerOpcion();
                if (idxH < 0 || idxH >= listaHoteles->longitud()) {
                    ColorUI::printGradient("\nIndice de hotel invalido.\n", Alerta, false);
                    system("pause>0");
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
                system("pause>0");
            }
            else if (tipo == 3) {
             
                Lista<Paquete*>* listaPaquetes = principal->getControladorPaquetes()->getPaquetes();
                if (listaPaquetes->longitud() == 0) {
                    ColorUI::printGradient("\nNo hay paquetes disponibles.\n", Alerta, false);
                    system("pause>0");
                    break;
                }
                cout << "\nPaquetes:\n";
                for (int i = 0; i < listaPaquetes->longitud(); i++) {
                    cout << "[" << i << "] ";
                    listaPaquetes->obtenerPos(i)->MostrarPaquete();
                    cout << "------------------------\n";
                }
                ColorUI::printGradient("\nIndice de paquete a reservar: ", Exito, false, false);
                int idxP = LeerOpcion();
                if (idxP < 0 || idxP >= listaPaquetes->longitud()) {
                    ColorUI::printGradient("\nIndice de paquete invalido.\n", Alerta, false);
                    system("pause>0");
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
                system("pause>0");
            }
            else {
                ColorUI::printGradient("\nTipo de reserva invalido.\n", Alerta, false);
                system("pause>0");
            }
        }break;
        case '6': {//agregar usuario
            ColorUI::printGradient("\t=== AGREGAR USUARIO ===", TemaPrincipal, false);
            string nombre, correo, password;
            ColorUI::printGradient("\nNombre: ", Exito, false, false);
            getline(cin, nombre);
            ColorUI::printGradient("\nCorreo: ", Exito, false, false);
            getline(cin, correo);
            ColorUI::printGradient("\nPassword: ", Exito, false, false);
            getline(cin, password);

            principal->AgregarUsuario(nombre, correo, password);
            ColorUI::printGradient("\nUsuario agregado correctamente.\n", gege, false);
            system("pause>0");
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
        system("cls");
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
            system("cls");
            return;
            break;
        default: break;
        }
    } while (opcion != '4');
}
void AdminPantallas::MenuReportes() {
    char opcion;
    do {
        system("cls");
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
        system("cls");

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
            system("pause>0");
            break;
        case '0': return;
        }
    } while (true);
}
void AdminPantallas::FiltroRutas() {
    system("cls");
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
            principal->MostrarRutas();
        }
        else {
            principal->FiltrarRutasPorOrigen(ciudadBusqueda);
        }
        system("pause>0");
    } break;
    case '2': {
        string ciudadBusqueda;
        ColorUI::printGradient("\nDigite el destino a filtrar (ej. Lima): ", Exito, false, false);
        getline(cin, ciudadBusqueda);
        if (ciudadBusqueda.empty()) {
            ColorUI::printGradient("\nNo ingresaste un destino. Se mostraron todas las rutas.\n", Alerta, false);
            principal->MostrarRutas();
        }
        else {
            principal->FiltrarRutasPorDestino(ciudadBusqueda);
        }
        system("pause>0");
    } break;
    case '3':
        principal->MostrarRutas();
        system("pause>0");
        break;
    case '4':
        return;
        break;
    }
}
void AdminPantallas::MenuFiltrosReservas() {
    char opcion;
    do {
        system("cls");
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
            cout << "Diigite el tipo de reservas a buscar(VUELO-HOTEL-PAQUETE: " << endl; cin >> reserva; cin.ignore();
            principal->FiltrarReservasPorTipo(reserva);
            system("pause>0");
            break;
        }
        case '2': {
            string reserva,codigousuario;
            cout << "Diigite el tipo de reservas a buscar (VUELO-HOTEL-PAQUETE): " << endl; cin >> reserva; cin.ignore();
            principal->MostrarUsuarios();
            cout << "Diigite el codigo de usuario: " << endl; cin >> codigousuario; cin.ignore();
            principal->FiltrarReservasPorTipoUsuario(reserva,codigousuario);
            system("pause>0");
            break;
        }
        case '3': {
            string codigousuario;
            principal->MostrarUsuarios();
            cout << "Diigite el codigo de usuario: " << endl; cin >> codigousuario; cin.ignore();
            principal->FiltrarReservasPorUsuario(codigousuario);
            system("pause>0");
            break;
        }
        case '4': {
            principal->MostrarReservas();
            system("pause>0");
            break;
        }
        case '0': {
            return;
            break;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosVuelos() {
    char opcion;
    do {
        system("cls");
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
            string origen;
            cout << "Diigite el origen: " << endl; getline(cin,origen);
            principal->FitrarVuelosPorOrigen(origen);
            system("pause>0");
            break;
        }
        case '2': {
            string destino;
            cout << "Diigite el destino: " << endl; getline(cin,destino);
            principal->FiltrarVuelosPorDestino(destino);
            system("pause>0");
            break;
        }
        case '3': {
            string fecha;
            cout << "Diigite la fecha (DD-MM-AAAA): " << endl; cin >> fecha; cin.ignore();
            principal->FiltrarVuelosPorFecha(fecha);
            system("pause>0");
            break;
        }
        case '4': {
            float presupuesto;
            cout << "Diigite el presupuesto: " << endl; cin >> presupuesto; cin.ignore();
            principal->FiltrarVuelosPorPresupuesto(presupuesto);
            system("pause>0");
            break;
        }
        case '5': {
            principal->MostrarVuelos();
            system("pause>0");
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
        system("cls");
        ColorUI::printGradient("\n================FILTROS PAQUETES==============", Exito, false);
        ColorUI::printGradient("\n[1] PAQUETES POR ORIGEN", Exito, false);
        ColorUI::printGradient("\n[2] PAQUETES POR DESTINO", Exito, false);
        ColorUI::printGradient("\n[3] MOSTRAR TODOS LOS PAQUETES", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string origen;
            cout << "Diigite el origen: " << endl; getline(cin,origen);
            principal->FiltrarPaquetesPorOrigen(origen);
            system("pause>0");
            break;
        }
        case '2': {
            string ;
            string destino;
            cout << "Diigite el origen: " << endl; getline(cin,destino);
            principal->FiltrarPaquetesPorDestino(destino);
            system("pause>0");
            break;
        }
        case '3': {
            principal->MostrarPaquetes();
            system("pause>0");
            break;
        }
        case '0': {
            return;
            break;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosHoteles() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS HOTELES==============", Exito, false);
        ColorUI::printGradient("\n[1] HOTELES POR CIUDAD", Exito, false);
        ColorUI::printGradient("\n[2] MOSTRAR TODOS LOS HOTELES", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string ciudad;
            cout << "Diigite la ciudad: " << endl; getline(cin,ciudad);
            principal->FiltrarHotelesPorCiudad(ciudad);
            system("pause>0");
            break;
        }
        case '2': {
            principal->MostrarHoteles();
            system("pause>0");
            break;
        }
        case '0': {
            return;
            break;
        }
        }
    } while (true);
}
void AdminPantallas::MenuFiltrosUsuarios() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS USUARIOS==============", Exito, false);
        ColorUI::printGradient("\n[1] FILTRAR USUARIOS POR NOMBRE", Exito, false);
        ColorUI::printGradient("\n[2] MOSTRAR TODOS LOS USUARIOS", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string nombre;
            cout << "Diigite el nombre: " << endl; cin >> nombre; cin.ignore();
            principal->FiltrarUsuariosPorNombre(nombre);
            system("pause>0");
            break;
        }
        case '2': {
            principal->MostrarUsuarios();
            system("pause>0");
            break;
        }
        case '0': {
            return;
            break;
        }
        }
    } while (true);
}
void AdminPantallas::MenuMantenimiento() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Agregar Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t[2] Eliminar Datos", Alerta, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);
        opcion = _getch();
        system("cls");
        switch (opcion) {
        case '1': MenuAgregar(); break;
        case '2': MenuEliminar(); break;
        case '0': return;
        default: break;
        }
    } while (true);
}
void AdminPantallas::GenerarDatosAleatorios() {
    system("cls");
    ColorUI::printGradient(datos, dato, false);
    gotoxy(0, 8);
    cout << "\n\tEsta opcion llenara la base de datos con informacion de prueba.\n";
    cout << "\tPresiona '1' para confirmar o '0' para cancelar.\n";

    char confirmacion = _getch();
    if (confirmacion == '1') {
        int cantidad;
        cout << "\tDigite la cantidad de datos a generar: "; cin >> cantidad; cin.ignore();
        principal->GenerarDatos(cantidad, cantidad, cantidad);
        ColorUI::printGradient("\n\tDatos generados con exito!\n", gege, false);
    }
    else {
        ColorUI::printGradient("\n\tOperacion cancelada.\n", Alerta, false);
    }
    system("pause>0");
}
void AdminPantallas::MenuEliminar() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Eliminar un Registro (Vuelo/Hotel/etc)", Alerta, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);

        opcion = _getch();
        system("cls");
        switch (opcion) {
        case '1': {
            ColorUI::printGradient(eliminacion, Alerta, false);
            gotoxy(0, 7);
            ColorUI::printGradient("\n\n\t\t\t[1] Vuelo | [2] Hotel | [3] Usuario", Exito, false, false);
            ColorUI::printGradient("\n\n\t\t\t[4] Reserva | [5] Ruta |[0] Cancelar\n\t\t\tOpcion: ", Exito, false, false);
            char delOpt = _getch();

            if (delOpt == '0') break;
            system("cls");
            cout << "\n\n\t\t\tIngresa el ID numerico a eliminar: ";
            int idTarget = LeerOpcion();

            if (delOpt == '1') principal->EliminarVuelo(idTarget);
            else if (delOpt == '2') principal->EliminarHotel(idTarget);
            else if (delOpt == '3') principal->EliminarUsuario(idTarget);
            else if (delOpt == '4') principal->EliminarReserva(idTarget);
            else if (delOpt == '5') principal->EliminarRuta(idTarget);

            ColorUI::printGradient("\n\t\t\tRegistro eliminado (si el ID era valido).\n", gege, false);
            system("pause>0");
        } break;

        case '0': return;
        }
    } while (true);
}