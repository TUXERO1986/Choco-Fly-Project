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
void ControladorArchivos::LeerArchivoRutas(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadID*>* MapaCiudades, ArbolAVLClave<CiudadID*, string>* indiceCiudadesPorNombre) {
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

            
            CiudadID* cOrigen = indiceCiudadesPorNombre->Buscar(origen);
            if (cOrigen == nullptr) {
                cOrigen = new CiudadID(origen, contadorId++);
                MapaCiudades->agregaFinal(cOrigen);
                indiceCiudadesPorNombre->Insertar(cOrigen);
            }

            CiudadID* cDestino = indiceCiudadesPorNombre->Buscar(destino);
            if (cDestino == nullptr) {
                cDestino = new CiudadID(destino, contadorId++);
                MapaCiudades->agregaFinal(cDestino);
                indiceCiudadesPorNombre->Insertar(cDestino);
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
        int idOrigen = indiceCiudadesPorNombre->Buscar(aux->getOrigen())->getId();
        int idDestino = indiceCiudadesPorNombre->Buscar(aux->getDestino())->getId();

        Lista<int>* filaOrigen = conexiones->obtenerPos(idOrigen);
        filaOrigen->modificarPos(idDestino, 1);
        conexiones->obtenerPos(idDestino)->modificarPos(1, idOrigen);
    }
}
void ControladorArchivos::LeerArchivoRegistros(Lista<Registro*>* registros) {
    ifstream archivo("Registros.txt");
    
    if (!archivo.is_open()) return;

    string linea, nombre, correo, tipoUsuario, accion, fechaHora;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') &&
            getline(ss, correo, ',') &&
            getline(ss, tipoUsuario, ',') &&
            getline(ss, accion, ',') &&
            getline(ss, fechaHora)) {

            registros->agregaFinal(new Registro(nombre, correo, tipoUsuario, accion, fechaHora));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoRegistros(Registro* r) {

    ofstream archivo("Registros.txt", ios::app);

    if (archivo.is_open()) {
        archivo << r->getNombre() << ","
                << r->getCorreo() << ","
                << r->getTipoUsuario() << ","
                << r->getAccion() << ","
                << r->getFechaHora() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::GardarDatoArchivoRutas(Ruta* r) {
    ofstream archivo("Rutas.txt", ios::app);

    if (archivo.is_open()) {
        archivo << r->getOrigen() << "," << r->getDestino() << "," << r->getDistancia() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoVuelos(Lista<Vuelo*>* vuelos,ArbolAVLMultiClave<Vuelo*, string>* indiceVuelosPorOrigen,ArbolAVL<Vuelo*>* vuelosMenorPrecio) {
    ifstream archivo("Vuelos.txt");
    if (!archivo.is_open()) return;

    string linea, origen, destino, escalas, fecha, distanciaStr, estadoAsientos; 

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);


        if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, escalas, ',') &&
            getline(ss, fecha, ',') && getline(ss, distanciaStr, ',') && getline(ss, estadoAsientos)) {

            float distancia = stof(distanciaStr);

           Vuelo* aux = new Vuelo(origen, destino, escalas, fecha, distancia,vuelos->longitud());
           aux->CargarEstadoAsientosString(estadoAsientos);

            
            vuelos->agregaFinal(aux);
            indiceVuelosPorOrigen->Insertar(aux);
            vuelosMenorPrecio->Insertar(aux);
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoVuelos(Vuelo* v) {
    ofstream archivo("Vuelos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << v->aTextoArchivo()<< "\n"; 
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoHoteles(Lista<Hotel*>* hoteles, ArbolAVLMultiClave<Hotel*, string>* indicePorCiudad,ArbolAVL<Hotel*>* hotelesMenorPrecio) {
    ifstream archivo("Hoteles.txt");
    if (!archivo.is_open()) return;

    string linea, nombre, ciudad, puntStr, precioStr,estadoHabitaciones;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') && getline(ss, ciudad, ',') &&
            getline(ss, puntStr, ',') && getline(ss, precioStr, ',') && getline(ss, estadoHabitaciones)) {

           
            float puntuacion = stof(puntStr);
            float precio = stof(precioStr);
            Hotel* aux = new Hotel(nombre, ciudad, puntuacion, precio,hoteles->longitud());
            aux->CargarEstadoHabitacionesString(estadoHabitaciones);
            hoteles->agregaFinal(aux);
            indicePorCiudad->Insertar(aux);
            hotelesMenorPrecio->Insertar(aux);
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoHoteles(Hotel* h) {
    ofstream archivo("Hoteles.txt", ios::app);
    if (archivo.is_open()) {
        archivo<<h->aTextoArchivo() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoPaquetes(Lista<Paquete*>* paquetes,ArbolAVLMultiClave<Paquete*, string>* indicePorDestino,ArbolAVL<Paquete*>* paquetesMenorPrecio) {
    ifstream archivo("Paquetes.txt");
    if (!archivo.is_open()) return;

    string linea;
    string vOri, vDes, vEsc, vFec, vDistStr;
    string hNom, hCiu, hPuntStr, hPrecStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);


        if (getline(ss, vOri, ',') && getline(ss, vDes, ',') && getline(ss, vEsc, ',') &&
            getline(ss, vFec, ',') && getline(ss, vDistStr, ',') &&
            getline(ss, hNom, ',') && getline(ss, hCiu, ',') && getline(ss, hPuntStr, ',') &&
            getline(ss, hPrecStr)) {

            Vuelo* vueloObj = new Vuelo(vOri, vDes, vEsc, vFec, stof(vDistStr),0);
            Hotel* hotelObj = new Hotel(hNom, hCiu, stof(hPuntStr), stof(hPrecStr),0);

            paquetes->agregaFinal(new Paquete(vueloObj, hotelObj,paquetes->longitud()));
            indicePorDestino->Insertar(new Paquete(vueloObj, hotelObj,paquetes->longitud()));
            paquetesMenorPrecio->Insertar(new Paquete(vueloObj, hotelObj,paquetes->longitud()));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoPaquetes(Paquete* p) {
    ofstream archivo("Paquetes.txt", ios::app);
    if (archivo.is_open()) {

        archivo <<p->aTextoArchivo()<< "\n";

        archivo.close();
    }
}
void ControladorArchivos::GuardarDatoArchivoReservas(Reserva* nuevaReserva) {

    ofstream archivo("Reservas.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nuevaReserva->aTextoArchivo() << "\n";
        archivo.close();
    }
}

void ControladorArchivos::LeerArchivoReservas(Lista<Reserva*>* listaDestino, ArbolAVLClave<Reserva*, int>* indiceReservasPorID) {
    ifstream archivo("Reservas.txt");
    if (!archivo.is_open()) return;

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        string tipo, codUser, nomUser;
        getline(ss, tipo, ',');
        getline(ss, codUser, ',');

        Reserva* nuevaReserva = nullptr;

        if (tipo == "VUELO") {
            getline(ss, nomUser, ','); 
            string origen, destino, escalas, fecha, precioStr, distStr, eqStr, eqCabStr, eqClase, eqAsiento,eqId;

            if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, escalas, ',') &&
                getline(ss, fecha, ',') && getline(ss, precioStr, ',') && getline(ss, distStr, ',') &&
                getline(ss, eqStr, ',') && getline(ss, eqCabStr, ',') &&
                getline(ss, eqClase, ',') && getline(ss, eqAsiento, ',') && getline(ss,eqId)) {

                nuevaReserva = new ReservaVuelo(codUser, nomUser, origen, destino, escalas, fecha, stof(distStr), stoi(eqStr), stoi(eqCabStr), stoi(eqClase), stoi(eqAsiento),stoi(eqId));
            }
        }
        else if (tipo == "HOTEL") {
            getline(ss, nomUser, ','); 
            string nombreHotel, ciudad, fechaIng, nochesStr, precioStr, habStr, toStr, tcStr, tsStr,idStr;

            if (getline(ss, nombreHotel, ',') && getline(ss, ciudad, ',') && getline(ss, fechaIng, ',') &&
                getline(ss, precioStr, ',') && getline(ss, nochesStr, ',') && getline(ss, habStr, ',') &&
                getline(ss, toStr, ',') && getline(ss, tcStr, ',') && getline(ss, tsStr,',')&& getline(ss,idStr)) {

                nuevaReserva = new ReservaHotel(codUser, nomUser, nombreHotel, ciudad, fechaIng, stof(precioStr), stoi(nochesStr), stoi(habStr), stoi(toStr), stoi(tcStr), stoi(tsStr),stoi(idStr));
            }
        }
        else if (tipo == "PAQUETE") {
            getline(ss, nomUser, '|');
            string idaPart, retornoPart, hotelPart,paquetePart;

            if (getline(ss, idaPart, '|') && getline(ss, retornoPart, '|') && getline(ss, hotelPart,'|')&& getline(ss, paquetePart)) {
                string basura, iOri, iDes, iEsc, iFec, iPre, iDist, iEq, iEqC, iEqCl, iEqA, iId;
                stringstream ssIda(idaPart);
                getline(ssIda, basura, ','); getline(ssIda, basura, ','); getline(ssIda, basura, ','); 
                getline(ssIda, iOri, ','); getline(ssIda, iDes, ','); getline(ssIda, iEsc, ','); getline(ssIda, iFec, ','); getline(ssIda, iPre, ','); getline(ssIda, iDist, ','); getline(ssIda, iEq, ','); getline(ssIda, iEqC, ','); getline(ssIda, iEqCl, ','); getline(ssIda, iEqA, ','); getline(ssIda,iId,',');

                string rOri, rDes, rEsc, rFec, rPre, rDist, rEq, rEqC, rEqCl, rEqA,rId;
                stringstream ssRet(retornoPart);
                getline(ssRet, basura, ','); getline(ssRet, basura, ','); getline(ssRet, basura, ','); 
                getline(ssRet, rOri, ','); getline(ssRet, rDes, ','); getline(ssRet, rEsc, ','); getline(ssRet, rFec, ','); getline(ssRet, rPre, ','); getline(ssRet, rDist, ','); getline(ssRet, rEq, ','); getline(ssRet, rEqC, ','); getline(ssRet, rEqCl, ','); getline(ssRet, rEqA, ','); getline(ssRet,rId,',');

                string hNom, hCiu, hFi, hPre, hNoc, hHb, hTo, hTc, hTs,hId;
                stringstream ssHot(hotelPart);
                getline(ssHot, basura, ','); getline(ssHot, basura, ','); getline(ssHot, basura, ','); 
                getline(ssHot, hNom, ','); getline(ssHot, hCiu, ','); getline(ssHot, hFi, ','); getline(ssHot, hPre, ','); getline(ssHot, hNoc, ','); getline(ssHot, hHb, ','); getline(ssHot, hTo, ','); getline(ssHot, hTc, ','); getline(ssHot, hTs, ','); getline(ssHot, hId, ',');
                
                stringstream ssPaq(paquetePart);
                string pId; getline(ssPaq, pId);

                ReservaVuelo* vueloIda = new ReservaVuelo(codUser, nomUser, iOri, iDes, iEsc, iFec, stof(iDist), stoi(iEq), stoi(iEqC), stoi(iEqCl), stoi(iEqA),stoi(iId));
                ReservaVuelo* vueloRetorno = new ReservaVuelo(codUser, nomUser, rOri, rDes, rEsc, rFec, stof(rDist), stoi(rEq), stoi(rEqC), stoi(rEqCl), stoi(rEqA),stoi(rId));
                ReservaHotel* hotelInterno = new ReservaHotel(codUser, nomUser, hNom, hCiu, hFi, stof(hNoc), stoi(hPre), stoi(hHb), stoi(hTo), stoi(hTc), stoi(hTs),stoi(hId));
                
                nuevaReserva = new ReservaPaquete(codUser, nomUser, vueloIda, vueloRetorno, hotelInterno,stoi(pId));
            }
        }

        if (nuevaReserva != nullptr) {
            listaDestino->agregaFinal(nuevaReserva);
            indiceReservasPorID->Insertar(nuevaReserva); 
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
