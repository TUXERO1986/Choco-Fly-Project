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
void ControladorArchivos::LeerArchivo(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadID*>* MapaCiudades) {
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
void ControladorArchivos::LeerArchivoVuelos(Lista<Vuelo*>* vuelos) {
    ifstream archivo("Vuelos.txt");
    if (!archivo.is_open()) return;

    string linea, origen, destino, escalas, fecha, distanciaStr, precioStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, escalas, ',') &&
            getline(ss, fecha, ',') && getline(ss, distanciaStr, ',') && getline(ss, precioStr)) {

            // Conversión directa sin try-catch
            float distancia = stof(distanciaStr);
            float precio = stof(precioStr);
            vuelos->agregaFinal(new Vuelo(origen, destino, escalas, fecha, distancia, precio));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoVuelos(Vuelo* v) {
    ofstream archivo("Vuelos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << v->getOrigen() << "," << v->getDestino() << ","
            << v->getEscalas() << "," << v->getFecha() << ","
            << v->getDistancia() << "," << v->getPrecio() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoHoteles(Lista<Hotel*>* hoteles) {
    ifstream archivo("Hoteles.txt");
    if (!archivo.is_open()) return;

    string linea, nombre, ciudad, puntStr, precioStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') && getline(ss, ciudad, ',') &&
            getline(ss, puntStr, ',') && getline(ss, precioStr)) {

            // Conversión directa sin try-catch
            float puntuacion = stof(puntStr);
            float precio = stof(precioStr);
            hoteles->agregaFinal(new Hotel(nombre, ciudad, puntuacion, precio));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoHoteles(Hotel* h) {
    ofstream archivo("Hoteles.txt", ios::app);
    if (archivo.is_open()) {
        archivo << h->getNombre() << "," << h->getCiudad() << ","
            << h->getPuntuacion() << "," << h->getPrecioNoche() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoPaquetes(Lista<Paquete*>* paquetes) {
    ifstream archivo("Paquetes.txt");
    if (!archivo.is_open()) return;

    string linea;
    string vOri, vDes, vEsc, vFec, vDistStr, vPrecStr;
    string hNom, hCiu, hPuntStr, hPrecStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, vOri, ',') && getline(ss, vDes, ',') && getline(ss, vEsc, ',') &&
            getline(ss, vFec, ',') && getline(ss, vDistStr, ',') && getline(ss, vPrecStr, ',') &&
            getline(ss, hNom, ',') && getline(ss, hCiu, ',') && getline(ss, hPuntStr, ',') &&
            getline(ss, hPrecStr)) {

            // Conversión e instanciación directa sin try-catch
            Vuelo* vueloObj = new Vuelo(vOri, vDes, vEsc, vFec, stof(vDistStr), stof(vPrecStr));
            Hotel* hotelObj = new Hotel(hNom, hCiu, stof(hPuntStr), stof(hPrecStr));

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
            << v->getFecha() << "," << v->getDistancia() << "," << v->getPrecio() << ","
            << h->getNombre() << "," << h->getCiudad() << ","
            << h->getPuntuacion() << "," << h->getPrecioNoche() << "\n";

        archivo.close();
    }
}
void ControladorArchivos::LeerArchivoTickets(Lista<Ticket*>* tickets) {
    ifstream archivo("Tickets.txt");
    if (!archivo.is_open()) return;

    string linea, nombre, origen, destino, escalas, precioStr, distStr, eqStr, eqCabStr;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        if (getline(ss, nombre, ',') && getline(ss, origen, ',') && getline(ss, destino, ',') &&
            getline(ss, escalas, ',') && getline(ss, precioStr, ',') && getline(ss, distStr, ',') &&
            getline(ss, eqStr, ',') && getline(ss, eqCabStr)) {

            // Conversión directa sin try-catch
            float precio = stof(precioStr);
            float distancia = stof(distStr);
            int equipaje = stoi(eqStr);
            int eqCabina = stoi(eqCabStr);

            tickets->agregaFinal(new Ticket(nombre, origen, destino, escalas, precio, distancia, equipaje, eqCabina));
        }
    }
    archivo.close();
}

void ControladorArchivos::GuardarDatoArchivoTickets(Ticket* t) {
    ofstream archivo("Tickets.txt", ios::app);
    if (archivo.is_open()) {
        archivo << t->getNombre() << "," << t->getOrigen() << "," << t->getDestino() << ","
            << t->getEscalas() << "," << t->getPrecio() << "," << t->getDistancia() << ","
            << t->getEquipaje() << "," << t->getEquipajeCabina() << "\n";
        archivo.close();
    }
}
void ControladorArchivos::VaciarArchivo() {
    // Abrir con ios::trunc elimina todo el contenido inmediatamente
    ofstream archivo(nombrearchivo, ios::trunc);
    if (archivo.is_open()) {
        archivo.close();
    }
}
