#include "ControladorRutas.h"

ControladorRutas::ControladorRutas() {
controladorArchivos = new ControladorArchivos("Rutas.txt");
    rutas = new Lista<Ruta*>();
    conexiones = new Lista<Lista<int>*>();
    MapaCiudades = new Lista<CiudadID*>();
    grafoRutas = new CGrafo<string>("");

    indiceCiudadesPorNombre = new ArbolAVLClave<CiudadID*, string>(
        [](CiudadID* c) { return c->getNombre(); }
    );

    controladorArchivos->LeerArchivoRutas(conexiones, rutas, MapaCiudades, indiceCiudadesPorNombre);

    for (unsigned int i = 0; i < MapaCiudades->longitud(); i++) {
        grafoRutas->adicionarVertice(MapaCiudades->obtenerPos(i)->getNombre());
    }

    for (unsigned int i = 0; i < rutas->longitud(); i++) {
        Ruta* r = rutas->obtenerPos(i);
        int idOri = ObtenerIdCiudadPorNombre(r->getOrigen());
        int idDes = ObtenerIdCiudadPorNombre(r->getDestino());
        if (idOri != -1 && idDes != -1) {
            grafoRutas->adicionarArco(idOri, idDes, r->getDistancia());
            grafoRutas->adicionarArco(idDes, idOri, r->getDistancia());
        }
    }
}

ControladorRutas::~ControladorRutas() {
    for (unsigned int i = 0; i < rutas->longitud(); i++) delete rutas->obtenerPos(i);
    delete rutas;
    for (unsigned int i = 0; i < MapaCiudades->longitud(); i++) delete MapaCiudades->obtenerPos(i);
    delete MapaCiudades;
    for (unsigned int i = 0; i < conexiones->longitud(); i++) delete conexiones->obtenerPos(i);
    delete conexiones;
    delete grafoRutas;
    delete indiceCiudadesPorNombre;
    delete controladorArchivos;
}

int ControladorRutas::ObtenerIdCiudadPorNombre(string nombre) {
    CiudadID* encontrado = indiceCiudadesPorNombre->Buscar(nombre);
    return encontrado != nullptr ? encontrado->getId() : -1;
}

void ControladorRutas::AgregarNuevaRuta(string origen, string destino, float distancia) {
    Ruta* ruta = new Ruta(origen, destino, distancia);
    rutas->agregaFinal(ruta);
    controladorArchivos->GardarDatoArchivoRutas(ruta);

    int idOri = ObtenerIdCiudadPorNombre(origen);
    int idDes = ObtenerIdCiudadPorNombre(destino);

    if (idOri == -1) {
        idOri = MapaCiudades->longitud();
        CiudadID* nueva = new CiudadID(origen, idOri);
        MapaCiudades->agregaFinal(nueva);
        indiceCiudadesPorNombre->Insertar(nueva);
        grafoRutas->adicionarVertice(origen);
    }
    if (idDes == -1) {
        idDes = MapaCiudades->longitud();
        CiudadID* nueva = new CiudadID(destino, idDes);
        MapaCiudades->agregaFinal(nueva);
        indiceCiudadesPorNombre->Insertar(nueva);
        grafoRutas->adicionarVertice(destino);
    }

    grafoRutas->adicionarArco(idOri, idDes, distancia);
    grafoRutas->adicionarArco(idDes, idOri, distancia);
}

Lista<Ruta*>* ControladorRutas::BuscarRutaMasCorta(string origen, string destino) {

    int idOri = ObtenerIdCiudadPorNombre(origen);
    int idDes = ObtenerIdCiudadPorNombre(destino);

    if (idOri == -1 || idDes == -1 || idOri == idDes) return nullptr;

    float costoTotalMinimo = 0.0f;
    Lista<int>* caminoIDs = grafoRutas->Dijkstra(idOri, idDes, costoTotalMinimo);

    if (caminoIDs == nullptr || caminoIDs->longitud() < 2) {
        if (caminoIDs != nullptr) delete caminoIDs;
        return nullptr;
    }

    Lista<Ruta*>* rutaFinal = new Lista<Ruta*>();

    for (unsigned int i = 0; i < caminoIDs->longitud() - 1; i++) {
        int idCiudadActual = caminoIDs->obtenerPos(i);
        int idCiudadSiguiente = caminoIDs->obtenerPos(i + 1);

        string nombreActual = MapaCiudades->obtenerPos(idCiudadActual)->getNombre();
        string nombreSiguiente = MapaCiudades->obtenerPos(idCiudadSiguiente)->getNombre();

        for (unsigned int r = 0; r < rutas->longitud(); r++) {
            Ruta* aux = rutas->obtenerPos(r);

            if ((aux->getOrigen() == nombreActual && aux->getDestino() == nombreSiguiente) ||
                (aux->getOrigen() == nombreSiguiente && aux->getDestino() == nombreActual)) {
                
                rutaFinal->agregaFinal(aux);
                break;
            }
        }
    }

    delete caminoIDs;
    return rutaFinal;
}

Lista<Ruta*>* ControladorRutas::getRutas() {
    return rutas;
}

Lista<Lista<int>*>* ControladorRutas::getConexiones() {
    return conexiones;
}

Lista<CiudadID*>* ControladorRutas::getMapaCiudades() {
    return MapaCiudades;
}

void ControladorRutas::MostrarRutas() {
    for (unsigned int i = 0; i < rutas->longitud(); i++) {
        Ruta* ruta = rutas->obtenerPos(i);
        ruta->MostrarDatos();
        cout << "-------------------------\n";
    }
}