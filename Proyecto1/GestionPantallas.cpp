#include "GestionPantallas.h"
#include <iostream>
#include "Windows.h"

using namespace ColorUI;


GestionPantallas::GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario) {
    principal = ptrPrincipal;
    userActual = ptrUsuario;
}

int GestionPantallas::LeerOpcion() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        ColorUI::printGradient("\tError: Ingresa un numero valido: ", Alerta, false, false);
    }
    cin.ignore(1000, '\n');
    return x;
}

void GestionPantallas::Menuprincipal() {
    char opcion;
    do {
        system("cls");
        cout << BLINK;
        ColorUI::printGradient(chocofly, TemaPrincipal, false);
        cout << RESET;
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] CATALOGOS DE SERVICIOS", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] RESERVAR UN SERVICIO", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] VERIFICAR MIS DATOS", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] MI HISTORIAL DE RESERVAS", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] CANCELAR RESERVA", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] CALIFICAR HOTEL", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[7] CREDITOS", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[0] Cerrar Sesion", Alerta, false);

        opcion = _getch();

        switch (opcion) {
        case '1': system("cls"); MenuCatalogos();system("cls"); break;
        case '2': system("cls"); MenuReservas(); system("cls"); break;
        case '3': system("cls"); MenuDatosUsuario();system("cls");break;
        case '4': system("cls"); HistorialReservas();system("cls"); break;
        case '5': system("cls"); MenuCancelarReserva(); system("cls"); break;
        case '6': system("cls"); MenuCalificacionHotel();system("cls"); break;
        case '7': system("cls"); creditos(); system("cls"); break;
        case '0':
            system("cls");
            ColorUI::printGradient("Cerrando sesion...", Alerta, false);
            system("cls");
            return;
            break;
        default: cout << "Opcion no valida" << endl; break;
        }
    } while (true);
}

void GestionPantallas::MenuReservaHotel() {
    string ciudad,fechaIngreso;
    int idHotel, noches, habitacion, tipoO, tipoC, tipoS;

    ColorUI::printGradient("=== RESERVA DE HOTELES ===", TemaPrincipal, false);
    ColorUI::printGradient("\nIngrese la ciudad destino para buscar hoteles:\nCiudad: ", Exito, false, false);
     getline(cin, ciudad);

    cout << "\n";
    principal->FiltrarHotelesPorCiudad(ciudad);
    if (!principal->VerificarHoteles(ciudad)) {
        cout << "No hay hoteles disponibles" << endl;
        return;
    }
    ColorUI::printGradient("\n================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del hotel que deseas reservar (o -1 para salir): ", Exito, false, false);
    idHotel = LeerOpcion();
    if (idHotel == -1) return;

    if (idHotel < 0 || idHotel >= principal->getControladorHoteles()->getHoteles()->longitud()) {
        ColorUI::printGradient("ID de hotel invalido.", Alerta, false);
        system("pause>0");
        return;
    }

    system("cls");
    cout << "\n\tMAPA DE HABITACIONES DEL HOTEL\n\n";

    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarHabitacion(i, idHotel);

        string textoHab = "[";
        if (i < 10) textoHab += "0";
        textoHab += to_string(i) + "]";

        if (disponible) {
            ColorUI::printGradient(textoHab, Register, false, false); 
        }
        else {
            ColorUI::printGradient("[XX]", Alerta, false, false); 
        }

        if (i % 5 == 0) cout << "\n\n";
        else cout << "   ";
    }

    ColorUI::printGradient("\n\nNumero de habitacion deseada: ", Exito, false, false);
    habitacion = LeerOpcion();
    ColorUI::printGradient("Cantidad de noches: ", Exito, false, false);
    noches = LeerOpcion();
    ColorUI::printGradient("Fecha de Ingreso (DD-MM-AAAA): ", Exito, false, false);
    cin >> fechaIngreso;
    cin.ignore();
    ColorUI::printGradient("DIGITE EL TIPO DE HABITACION (1-INDIVIDUAL,2-SUITE.3-PRESIDENCIAL): ", Exito, false, false);
    cin >> tipoO;
    cin.ignore();
    ColorUI::printGradient("DIGITE EL TIPO DE CAMA (1-INDIVIDUAL,2-MATRIMONIAL.3-QUEEN): ", Exito, false, false);
    cin >> tipoC;
    cin.ignore();
    ColorUI::printGradient("DIGITE EL TIPO DE SERVICIOS (1-BASICO,2-PREMIUM,3-VIP): ", Exito, false, false);
    cin >> tipoS;
    cin.ignore();

    char opcion;
    do {
        cout << "\n";
        ColorUI::printGradient("ESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
        opcion = _getch();

        if (opcion == '2') {
            cout << "\n";
            ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
            system("pause>0");
            return;
        }
        else if (opcion != '1') {
            cout << "\n";
            ColorUI::printGradient("ERROR: DIGITE OPCION CORRECTA", Alerta, false);
        }
    } while (opcion != '1');
    principal->ReservarHotel(idHotel, userActual, fechaIngreso,noches, habitacion, tipoO, tipoC, tipoS);

    system("cls");
    ColorUI::printGradient("RESERVA DE HOTEL COMPLETADA", gege, false);
    cout << "\n";
    system("pause>0");
}

void GestionPantallas::MenuReservaPaquete() {
    string ciudad;
    int idPaquete, noches, equipajeIda, equipajeRetorno, asiento, clase;

    ColorUI::printGradient("=== RESERVA DE PAQUETES TURISTICOS ===", TemaPrincipal, false);
    ColorUI::printGradient("\nIngrese la ciudad destino:\nCiudad: ", Exito, false, false);
     getline(cin, ciudad);

    cout << "\n";
    principal->FiltrarPaquetesPorDestino(ciudad);
    if (!principal->VerificarPaquetes(ciudad)) {
        cout << "No hay paquetes disponibles" << endl;
        return;
    }
    ColorUI::printGradient("\n================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del paquete que deseas comprar (o -1 para salir): ", Exito, false, false);
    idPaquete = LeerOpcion();
    if (idPaquete == -1) return;

  
    if (idPaquete < 0 || idPaquete >= principal->getControladorPaquetes()->getPaquetes()->longitud()) {
        ColorUI::printGradient("ID de paquete invalido. Abortando compra...", Alerta, false);
        system("pause>0");
        return;
    }

    ColorUI::printGradient("Cantidad de noches de estadia en hotel incluido: ", Exito, false, false);
    noches = LeerOpcion();

    ColorUI::printGradient("Cantidad de equipaje para la IDA: ", Exito, false, false);
    equipajeIda = LeerOpcion();

    ColorUI::printGradient("Cantidad de equipaje para el RETORNO: ", Exito, false, false);
    equipajeRetorno = LeerOpcion();

    ColorUI::printGradient("Numero de asiento preferido en vuelo IDA y RETORNO: ", Exito, false, false);
    asiento = LeerOpcion();
    ColorUI::printGradient("DIGITE LA CLASE: ", Exito, false, false);
    clase = LeerOpcion();
    char opcion;

    do {
        cout << "\n";
        ColorUI::printGradient("ESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
        opcion = _getch();

        if (opcion == '2') {
            cout << "\n";
            ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
            system("pause>0");
            return;
        }
        else if (opcion != '1') {
            cout << "\n";
            ColorUI::printGradient("ERROR: DIGITE OPCION CORRECTA", Alerta, false);
        }
    } while (opcion != '1');
    principal->ReservarPaquete(idPaquete, userActual, noches, equipajeIda, equipajeRetorno, clase, asiento);

    system("cls");
    ColorUI::printGradient("PAQUETE COMPRADO CON EXITO", gege, false);
    cout << "\n";
    system("pause>0");
}
void GestionPantallas::MenuCalificacionHotel() {
    string ciudad,nombre;
    float calificaion;
    int id;
    ColorUI::printGradient("\n\t\t\t\t\tDIGITE LA CIUDAD DEL HOTEL", Exito, false);
    
     getline(cin,ciudad);
    
    principal->FiltrarHotelesPorCiudad(ciudad);
    ColorUI::printGradient("\n\t\t\t\t\tDIGITE EL NOMBRE DEL HOTEL", Exito, false);
     getline(cin,nombre);
    
    ColorUI::printGradient("\n\t\t\t\t\tDIGITE LA CALIFICACION (1.0-5.0)", Exito, false);
    cin >> calificaion; cin.ignore();
  
    principal->CalificarHotel(nombre, calificaion);
    system("pause>0");

}
void GestionPantallas::MenuReservaVuelo() {
    int indiceVuelo, equipaje, cabina, asiento, clase;
    string origen, destino, nombre;

    ColorUI::printGradient("=== COMPRA DE TICKETS ===", TemaPrincipal, false);

    ColorUI::printGradient("\nOrigen: ", Exito, false, false);
     getline(cin, origen);
    if (origen == "0") return;
    ColorUI::printGradient("Destino: ", Alerta, false, false);
     getline(cin, destino);

    cout << "\n";
    if (!principal->ConsultarVuelos(origen, destino)) {
        system("pause>0");
        return;
    }

    ColorUI::printGradient("================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del vuelo que deseas reservar (o -1 para salir): ", Exito, false, false);
    indiceVuelo = LeerOpcion();

    if (indiceVuelo == -1) return;

    if (indiceVuelo < 0 || indiceVuelo >= principal->getControladorVuelos()->getVuelos()->longitud()) {
        ColorUI::printGradient("ID de vuelo invalido. Abortando compra...", Alerta, false);
        system("pause>0");
        return;
    }

    system("cls");
    ColorUI::printGradient("=== SELECCION DE ASIENTO ===", TemaPrincipal, false);
    cout << "\n\tMAPA DE ASIENTOS DEL VUELO\n\n";
    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarAsiento(i, indiceVuelo);
        string textoAsiento = "[";
        if (i < 10) textoAsiento += "0";
        textoAsiento += to_string(i) + "]";

        if (disponible) {
            ColorUI::printGradient(textoAsiento, Exito, false, false); 
        }
        else {
            ColorUI::printGradient("[XX]", Alerta, false, false); 
        }

        if (i % 6 == 0) {
            cout << "\n\n"; 
        }
        else if (i % 3 == 0) {
            ColorUI::printGradient("   ||   ", TemaPrincipal, false, false); 
        }
        else {
            cout << " "; 
        }
    }

    bool asientoValido = false;
    while (!asientoValido) {
        ColorUI::printGradient("\n\nIngresa el numero del asiento que deseas (1-30): ", Exito, false, false);
        asiento = LeerOpcion();
        if (principal->VerificarAsiento(asiento, indiceVuelo)) {
            asientoValido = true;
        }
        else {
            ColorUI::printGradient("El asiento seleccionado no existe o ya esta ocupado.", Alerta, false);
        }
    }

    system("cls");

    cout << endl;
    ColorUI::printGradient("Ingresa la cantidad de equipaje en bodega: ", Exito, false, false);
    equipaje = LeerOpcion();

    cout << endl;
    ColorUI::printGradient("Ingresa la cantidad de equipaje en cabina: ", Exito, false, false);
    cabina = LeerOpcion();

    cout << endl;
    ColorUI::printGradient("Ingresa que clase deseas adquirir (1-ECONOMICA, 2-ECONOMICA PREMIUM, 3-EJECUTIVA, 4-PRIMERA CLASE):", Exito, false, false);
    clase = LeerOpcion();
    char opcion;
    do {
        cout << "\n"; 
        ColorUI::printGradient("ESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
        opcion = _getch();

        if (opcion == '2') {
            cout << "\n";
            ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
            system("pause>0");
            return; 
        }
        else if (opcion != '1') {
            cout << "\n";
            ColorUI::printGradient("ERROR: DIGITE OPCION CORRECTA", Alerta, false);
        }
    } while (opcion != '1');
    principal->ComprarTicket(indiceVuelo, userActual, equipaje, cabina, asiento, clase);

    system("cls");
    ColorUI::printGradient("TICKET COMPRADO CON EXITO", gege, false);
    system("pause>0");
    ColorUI::printGradient("El asiento [" + to_string(asiento) + "] ha sido reservado para " + userActual->getNombre(), Exito, false);
    cout << "\n";
    system("pause>0");
}
void GestionPantallas::MenuFiltrosReservas() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS RESERVAS==============", Exito, false);
        ColorUI::printGradient("\n[1] RESERVAS POR TIPO USUARIO", Exito, false);
        ColorUI::printGradient("\n[2] MOSTRAR TODAS MIS RESERVAS", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            system("cls");
            string reserva;
            ColorUI::printGradient("\nDIGITE EL TIPO DE RESERVA A BUSCAR (VUELO-HOTEL-PAQUETE)\n", Exito, false); cin >> reserva;
            principal->FiltrarReservasPorTipoUsuario(reserva, userActual->getCodigo());
            system("pause>0");
            break;
        }
        case '2': {
            system("cls");
            principal->FiltrarReservasPorUsuario(userActual->getCodigo());
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
void GestionPantallas::MenuFiltrosVuelos() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS VUELOS==============", Exito, false);
        ColorUI::printGradient("\n[1] VUELOS POR ORIGEN", Exito, false);
        ColorUI::printGradient("\n[2] VUELOS POR DESTINO", Exito, false);
        ColorUI::printGradient("\n[3] VUELOS POR FECHA", Exito, false);
        ColorUI::printGradient("\n[4] VUELOS POR PRESUPUESTO", Exito, false);
        ColorUI::printGradient("\n[5] VUELOS DE POR PRECIO (MAYOR A MENOR)", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            string origen;
            ColorUI::printGradient("\nDIGITE EL ORIGEN\n", Exito, false);  getline(cin,origen);
            principal->FitrarVuelosPorOrigen(origen);
            system("pause>0");
            break;
        }
        case '2': {
            string destino;
            ColorUI::printGradient("\nDIGITE EL DESTINO\n", Exito, false);  getline(cin,destino);
            principal->FiltrarVuelosPorDestino(destino);
            system("pause>0");
            break;
        }
        case '3': {
            string fecha;
            principal->MostrarUsuarios();
            ColorUI::printGradient("\nDIGITE LA FECHA (DD-MM-AAAA)\n", Exito, false); cin >> fecha; cin.ignore();
            principal->FiltrarVuelosPorFecha(fecha);
            system("pause>0");
            break;
        }
        case '4': {
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO\n", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarVuelosPorPresupuesto(presupuesto);
            system("pause>0");
            break;
        }
        case '5': {
            principal->FiltrarVuelosDeMayorAMenorPrecio();
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
void GestionPantallas::MenuFiltrosPaquetes() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS PAQUETES==============", Exito, false);
        ColorUI::printGradient("\n[1] PAQUETES POR ORIGEN", Exito, false);
        ColorUI::printGradient("\n[2] PAQUETES POR DESTINO", Exito, false);
        ColorUI::printGradient("\n[3] PAQUETES POR PRECIO (MAYOR A MENOR)", Exito, false);
        ColorUI::printGradient("\n[4] PAQUETES POR PRESUPUESTO", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            system("cls");
            string origen;
            cout << "Diigite el origen: " << endl;  getline(cin,origen);
            principal->FiltrarPaquetesPorOrigen(origen);
            system("pause>0");
            break;
        }
        case '2': {
            system("cls");
            string destino;
            cout << "Diigite el origen: " << endl;  getline(cin,destino);
            principal->FiltrarPaquetesPorDestino(destino);
            system("pause>0");
            break;
        }
        case '3': {
            system("cls");
            principal->FiltrarPaquetesDeMayorAMenorPrecio();
            system("pause>0");
            break;
        }
        case '4': {
            system("cls");
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarPaquetesPorPresupuesto(presupuesto);
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
void GestionPantallas::MenuFiltrosHoteles() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS HOTELES==============", Exito, false);
        ColorUI::printGradient("\n[1] HOTELES POR CIUDAD", Exito, false);
        ColorUI::printGradient("\n[2] HOTELES POR CALIFICACION (MAYOR A MENOR)", Exito, false);
        ColorUI::printGradient("\n[3] HOTELES POR PRECIO NOCHE (MAYOR A MENOR)", Exito, false);
        ColorUI::printGradient("\n[4] HOTELES POR PRESUPEUSTO", Exito, false);
        ColorUI::printGradient("\n[5] CALIFICAR UN HOTEL", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            system("cls");
            string ciudad;
            cout << "Diigite la ciudad: " << endl;  getline(cin,ciudad);
            principal->FiltrarHotelesPorCiudad(ciudad);
            system("pause>0");
            break;
        }
        case '2': {

            system("cls");
            principal->FiltrarHotelesPorMayorCalificacion();
            system("pause>0");
            break;
        }
        case '3': {
            system("cls");
            principal->FiltrarHotelesDeMayorAMenorPrecio();
            system("pause>0");
            break;
        }
        case '4': {
            system("cls");
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarHotelesPorPresupuesto(presupuesto);
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
void GestionPantallas::MenuDatosUsuario(){
    ColorUI::printGradient("\n\t\t\t\t\tDATOS DEL USUARIO ACTUAL\n", Exito, false);
    principal->FiltrarUsuarioPorCodigo(userActual->getCodigo()); 
    system("pause>0");
}
void GestionPantallas::MenuCatalogos(){
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================CATALOGO DE SERVICIOS==============", Exito, false);
        ColorUI::printGradient("\n[1] CATALOGO VUELOS DISPONIBLES", Exito, false);
        ColorUI::printGradient("\n[2] CATALOGO DE HOTELES DISPONIBLES", Exito, false);
        ColorUI::printGradient("\n[3] CATALOGO DE PQUETES DISPONIBLES", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            system("cls");
            MenuFiltrosVuelos();
            system("pause>0");
            break;
        }
        case '2': {
            system("cls");
            MenuFiltrosHoteles();
            system("pause>0");
            break;
        }
        case '3': {
            system("cls");
            MenuFiltrosPaquetes();
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
void GestionPantallas::MenuCancelarReserva() {
    int id;
    principal->FiltrarReservasPorUsuario(userActual->getCodigo());
    if (!principal->VerificarReservas(userActual->getCodigo())) {
        cout << "No hay reservas registrar a su nombre" << endl;
        system("pause>0");
        return;
    }
    do {
        ColorUI::printGradient("\nDIGITE EL ID DE LA RESERVA A ELIMINAR\n", Exito, false);
        cin >> id;
        cin.ignore();
    } while (!principal->CancelarReservaUsuario(userActual->getCodigo(), id));
    ColorUI::printGradient("\nEL MONTO SE REMBOLSARA EN SU CUENTA MAXIMO 10 DIAS HABILES", Exito, false);
    system("pause>0");
}
void GestionPantallas::MenuReservas() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient("\n================FILTROS HOTELES==============", Exito, false);
        ColorUI::printGradient("\n[1] RESERVAR TICKET DE VUELO", Exito, false);
        ColorUI::printGradient("\n[2] RESERVAR TICKET DE HOTEL", Exito, false);
        ColorUI::printGradient("\n[3] RESERVAR TICKET DE PAQUETE", Exito, false);
        ColorUI::printGradient("\n[0] SALIR", Exito, false);
        opcion = _getch();
        switch (opcion) {
        case '1': {
            system("cls");
            MenuReservaVuelo();
            system("pause>0");
            break;
        }
        case '2': {
            system("cls");
            MenuReservaHotel();
            system("pause>0");
            break;
        }
        case '3': {
            system("cls");
            MenuReservaPaquete();
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
void GestionPantallas::HistorialReservas() {
    ColorUI::printGradient("=== MI HISTORIAL DE RESERVAS ===", TemaPrincipal, false);
    MenuFiltrosReservas();
    cout << "\n";
    system("pause>0");
}