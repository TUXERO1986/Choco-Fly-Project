#include "ControladorArchivos.h"
ControladorArchivos::ControladorArchivos(){}
ControladorArchivos::ControladorArchivos(string nombrearchivo){
	this->nombrearchivo = nombrearchivo;
    ObtenerIdCiudad = [](Lista<CiudadID*>* mapaciudades, string nombre) {
        for (unsigned int i = 0; i < mapaciudades->longitud(); i++) {
            CiudadID* aux = mapaciudades->obtenerPos(i);
            if (aux->getNombre() == nombre) {
                return aux->getId();
            }
        }
        return -1; 
		};
}
void ControladorArchivos::LeerArchivoRutas(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadID*>* MapaCiudades) {
    ifstream archivo(nombrearchivo);
    if (!archivo.is_open()) {
        cout << "No se puedo abrir el archivo" << std::endl;
        return;
    }

    string linea;
    int contadorId = 0; 



    while (getline(archivo, linea)) {
        stringstream ss(linea); 
        string origen, destino, distancia;

       

        if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, distancia)) {
            float dbdistancia = stof(distancia);
            Ruta* aux = new Ruta(origen, destino, dbdistancia);
            rutas->agregaFinal(aux);

            
            if (ObtenerIdCiudad(MapaCiudades, origen) == -1) {
                MapaCiudades->agregaFinal(new CiudadID(origen, contadorId++));
            }
            if (ObtenerIdCiudad(MapaCiudades, destino) == -1) {
                MapaCiudades->agregaFinal(new CiudadID(destino, contadorId++));
            }
        }
    }
    archivo.close();

    int totalCiudades = MapaCiudades->longitud();

    for (auto i = 0; i < totalCiudades; i++) {
        Lista<int>* fila = new Lista<int>(); 
        for (auto j = 0; j < totalCiudades; j++) {
            fila->agregaFinal(0);
        }
        conexiones->agregaFinal(fila);
    }

    for (auto i = 0; i < rutas->longitud(); i++) {
        Ruta* aux = rutas->obtenerPos(i);
        int idOrigen = ObtenerIdCiudad(MapaCiudades, aux->getOrigen());
        int idDestino = ObtenerIdCiudad(MapaCiudades, aux->getDestino());

        if (idOrigen != -1 && idDestino != -1) {

            Lista<int>* filaOrigen = conexiones->obtenerPos(idOrigen);

            filaOrigen->modificarPos(idDestino, 1);
            conexiones->obtenerPos(idDestino)->modificarPos(1, idOrigen);

            Lista<int>* filaDestino = conexiones->obtenerPos(idDestino);

            filaDestino->modificarPos(1, idOrigen);
            conexiones->obtenerPos(idOrigen)->modificarPos(1, idDestino);
        }
    }
}
void ControladorArchivos::GardarDatoArchivoRutas(Ruta* r) {
    ofstream archivo("Rutas.txt", ios::app);

    if (archivo.is_open()) {
        archivo << r->getOrigen() << "," << r->getDestino() << "," << r->getDistancia() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoVuelos(Lista<Vuelo*>* vuelos) {
    ifstream archivo("Vuelos.txt");
    if (!archivo.is_open()) return;

    string linea, origen, destino, escalas, fecha, distanciaStr, estadoAsientos; // Nueva variable

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        // Agregamos getline para estadoAsientos
        if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, escalas, ',') &&
            getline(ss, fecha, ',') && getline(ss, distanciaStr, ',') && getline(ss, estadoAsientos)) {

            float distancia = stof(distanciaStr);

            // 1. Instanciamos el controlador (Esto autogenera los 30 asientos disponibles)
            ControladorAsientos* ctrlAsientos = new ControladorAsientos();

            // 2. Le inyectamos los ocupados según el archivo
            ctrlAsientos->CargarEstadoAsientosString(estadoAsientos);

            // 3. Creamos el vuelo y lo agregamos
            vuelos->agregaFinal(new Vuelo(origen, destino, escalas, fecha, distancia, ctrlAsientos));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoVuelos(Vuelo* v) {
    ofstream archivo("Vuelos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << v->getOrigen() << "," << v->getDestino() << ","
            << v->getEscalas() << "," << v->getFecha() << ","
            << v->getDistancia() << ","
            << v->getControladorAsientos()->ObtenerEstadoAsientosString() << "\n"; // ¡AQUI!
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoHoteles(Lista<Hotel*>* hoteles) {
    ifstream archivo("Hoteles.txt");
    if (!archivo.is_open()) return;

    string linea, nombre, ciudad, puntStr, precioStr,estadoHabitaciones;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') && getline(ss, ciudad, ',') &&
            getline(ss, puntStr, ',') && getline(ss, precioStr, ',') && getline(ss, estadoHabitaciones)) {

            // Conversión directa sin try-catch
            float puntuacion = stof(puntStr);
            float precio = stof(precioStr);
            ControladorHabitaciones* ctrlHabtiaciones = new ControladorHabitaciones();
            ctrlHabtiaciones->CargarEstadoHabitacionesString(estadoHabitaciones);
            hoteles->agregaFinal(new Hotel(nombre, ciudad, puntuacion, precio,ctrlHabtiaciones));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoHoteles(Hotel* h) {
    ofstream archivo("Hoteles.txt", ios::app);
    if (archivo.is_open()) {
        archivo << h->getNombre() << "," << h->getCiudad() << ","
            << h->getPuntuacion() << "," << h->getPrecioNoche()<<","
            <<h->getControladorHabitaciones()->ObtenerEstadoHabitacionesString() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoPaquetes(Lista<Paquete*>* paquetes) {
    ifstream archivo("Paquetes.txt");
    if (!archivo.is_open()) return;

    string linea;
    string vOri, vDes, vEsc, vFec, vDistStr;
    string hNom, hCiu, hPuntStr, hPrecStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        // Leer los 9 campos que realmente se guardan: 
        // vOri, vDes, vEsc, vFec, vDist, hNom, hCiu, hPunt, hPrec
        if (getline(ss, vOri, ',') && getline(ss, vDes, ',') && getline(ss, vEsc, ',') &&
            getline(ss, vFec, ',') && getline(ss, vDistStr, ',') &&
            getline(ss, hNom, ',') && getline(ss, hCiu, ',') && getline(ss, hPuntStr, ',') &&
            getline(ss, hPrecStr)) {

            Vuelo* vueloObj = new Vuelo(vOri, vDes, vEsc, vFec, stof(vDistStr), new ControladorAsientos());
            Hotel* hotelObj = new Hotel(hNom, hCiu, stof(hPuntStr), stof(hPrecStr), new ControladorHabitaciones());

            paquetes->agregaFinal(new Paquete(vueloObj, hotelObj));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoPaquetes(Paquete* p) {
    ofstream archivo("Paquetes.txt", ios::app);
    if (archivo.is_open()) {
        Vuelo* v = p->getVueloIncluido();
        Hotel* h = p->getHotelIncluido();

        archivo << v->getOrigen() << "," << v->getDestino() << "," << v->getEscalas() << ","
            << v->getFecha() << "," << v->getDistancia() << ","
            << h->getNombre() << "," << h->getCiudad() << ","
            << h->getPuntuacion() << "," << h->getPrecioNoche() << "\n";

        archivo.close();
    }
}
void ControladorArchivos::GuardarDatoArchivoReservas(Reserva* nuevaReserva) {
    // ios::app abre el archivo y pone el cursor al final, sin borrar lo anterior
    ofstream archivo("Reservas.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nuevaReserva->aTextoArchivo() << "\n";
        archivo.close();
    }
}

void ControladorArchivos::LeerArchivoReservas(Lista<Reserva*>* listaDestino) {
    ifstream archivo("Reservas.txt");
    if (!archivo.is_open()) return;

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        string tipo, codUser, nomUser;

        getline(ss, tipo, ',');
        getline(ss, codUser, ',');

        if (tipo == "VUELO") {
            getline(ss, nomUser, ','); 

            string origen, destino, escalas, fecha, precioStr, distStr, eqStr, eqCabStr, eqClase, eqAsiento;

            if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, escalas, ',') &&
                getline(ss, fecha, ',') && getline(ss, precioStr, ',') && getline(ss, distStr, ',') &&
                getline(ss, eqStr, ',') && getline(ss, eqCabStr, ',') &&
                getline(ss, eqClase, ',') && getline(ss, eqAsiento)) {

                float distancia = stof(distStr);
                int equipaje = stoi(eqStr);
                int eqCab = stoi(eqCabStr);
                int clase = stoi(eqClase);
                int asiento = stoi(eqAsiento);
                listaDestino->agregaFinal(new Ticket(codUser, nomUser, origen, destino, escalas, fecha, distancia, equipaje, eqCab, clase, asiento));
            }
        }
        else if (tipo == "HOTEL") {
            getline(ss, nomUser, ','); 

            string nombreHotel, ciudad, fechaIng, nochesStr, precioStr, habStr, toStr, tcStr, tsStr;

            if (getline(ss, nombreHotel, ',') && getline(ss, ciudad, ',') && getline(ss, fechaIng, ',') &&
                getline(ss, precioStr, ',') && getline(ss, nochesStr, ',') && getline(ss, habStr, ',') &&
                getline(ss, toStr, ',') && getline(ss, tcStr, ',') && getline(ss, tsStr)) {

                float precio = stof(precioStr);
                int noches = stoi(nochesStr);
                listaDestino->agregaFinal(new ReservaHotel(codUser, nomUser, nombreHotel, ciudad, fechaIng, precio, noches, stoi(habStr), stoi(toStr), stoi(tcStr), stoi(tsStr)));
            }
        }
        else if (tipo == "PAQUETE") {

            getline(ss, nomUser, '|');

            string idaPart, retornoPart, hotelPart;

            if (getline(ss, idaPart, '|') &&
                getline(ss, retornoPart, '|') &&
                getline(ss, hotelPart)) {

                string basura; 

                stringstream ssIda(idaPart);
                string iOri, iDes, iEsc, iFec, iPre, iDist, iEq, iEqC, iEqCl, iEqA;

                getline(ssIda, basura, ','); 
                getline(ssIda, basura, ','); 
                getline(ssIda, basura, ','); 

                getline(ssIda, iOri, ',');
                getline(ssIda, iDes, ',');
                getline(ssIda, iEsc, ',');
                getline(ssIda, iFec, ',');
                getline(ssIda, iPre, ',');
                getline(ssIda, iDist, ',');
                getline(ssIda, iEq, ',');
                getline(ssIda, iEqC, ',');
                getline(ssIda, iEqCl, ',');
                getline(ssIda, iEqA, ',');

                stringstream ssRet(retornoPart);
                string rOri, rDes, rEsc, rFec, rPre, rDist, rEq, rEqC, rEqCl, rEqA;

                getline(ssRet, basura, ','); 
                getline(ssRet, basura, ','); 
                getline(ssRet, basura, ','); 

                getline(ssRet, rOri, ',');
                getline(ssRet, rDes, ',');
                getline(ssRet, rEsc, ',');
                getline(ssRet, rFec, ',');
                getline(ssRet, rPre, ',');
                getline(ssRet, rDist, ',');
                getline(ssRet, rEq, ',');
                getline(ssRet, rEqC, ',');
                getline(ssRet, rEqCl, ',');
                getline(ssRet, rEqA, ',');

                stringstream ssHot(hotelPart);
                string hNom, hCiu, hFi, hPre, hNoc, hHb, hTo, hTc, hTs;

                getline(ssHot, basura, ',');
                getline(ssHot, basura, ','); 
                getline(ssHot, basura, ','); 

                getline(ssHot, hNom, ',');
                getline(ssHot, hCiu, ',');
                getline(ssHot, hFi, ',');
                getline(ssHot, hPre, ',');
                getline(ssHot, hNoc, ',');
                getline(ssHot, hHb, ',');
                getline(ssHot, hTo, ',');
                getline(ssHot, hTc, ',');
                getline(ssHot, hTs, ',');

                Ticket* vueloIda = new Ticket(codUser, nomUser, iOri, iDes, iEsc, iFec, stof(iDist), stoi(iEq), stoi(iEqC), stoi(iEqCl), stoi(iEqA));
                Ticket* vueloRetorno = new Ticket(codUser, nomUser, rOri, rDes, rEsc, rFec, stof(rDist), stoi(rEq), stoi(rEqC), stoi(rEqCl), stoi(rEqA));
                ReservaHotel* hotelInterno = new ReservaHotel(codUser, nomUser, hNom, hCiu, hFi, stof(hNoc),
                    stoi(hPre), stoi(hHb), stoi(hTo), stoi(hTc), stoi(hTs));
                listaDestino->agregaFinal(new ReservaPaquete(codUser, nomUser, vueloIda, vueloRetorno, hotelInterno));
            }
        }
    }
    archivo.close();
}
void ControladorArchivos::LeerArchivoUsuarios(Lista<Usuario*>* usuarios) {
    ifstream archivo("Usuarios.txt");

    if (!archivo.is_open()) return;

    string linea, nombre, correo, password, codigo;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') &&
            getline(ss, correo, ',') &&
            getline(ss, password, ',') &&
            getline(ss, codigo)) {

            usuarios->agregaFinal(new Usuario(nombre, correo, password, codigo));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoUsuarios(Usuario* u) {

    ofstream archivo("Usuarios.txt", ios::app);

    if (archivo.is_open()) {
        archivo << u->getNombre() << ","
            << u->getCorreo() << ","
            << u->getPassword() << ","
            << u->getCodigo() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::VaciarArchivo() {

    ofstream archivo(nombrearchivo, ios::trunc);
    if (archivo.is_open()) {
        archivo.close();
    }
}
