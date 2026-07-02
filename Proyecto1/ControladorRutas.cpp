#include "ControladorRutas.h"

ControladorRutas::ControladorRutas() {
    controladorArchivos = new ControladorArchivos("Rutas.txt");
    rutas = new Lista<Ruta*>();
    conexiones = new Lista<Lista<int>*>();
    MapaCiudades = new Lista<CiudadID*>();
    
    // Inicializamos nuestro nuevo motor de Grafos
    grafoRutas = new CGrafo<string>("");

    ObtenerIdCiudad = [](Lista<CiudadID*>* mapaciudades, string nombre) {
        for (unsigned int i = 0; i < mapaciudades->longitud(); i++) {
            CiudadID* aux = mapaciudades->obtenerPos(i);
            if (aux->getNombre() == nombre) {
                return aux->getId();
            }
        }
        return -1;
    };

    controladorArchivos->LeerArchivoRutas(conexiones, rutas, MapaCiudades);

    // ==========================================================
    // INYECCIÓN DE DATOS AL GRAFO (Se ejecuta al iniciar el app)
    // ==========================================================
    
    // 1. Agregar los vértices (Ciudades) respetando su ID original
    for (unsigned int i = 0; i < MapaCiudades->longitud(); i++) {
        grafoRutas->adicionarVertice(MapaCiudades->obtenerPos(i)->getNombre());
    }

    // 2. Agregar los Arcos (Rutas) con la distancia como Peso
    for (unsigned int i = 0; i < rutas->longitud(); i++) {
        Ruta* r = rutas->obtenerPos(i);
        int idOri = ObtenerIdCiudad(MapaCiudades, r->getOrigen());
        int idDes = ObtenerIdCiudad(MapaCiudades, r->getDestino());

        if (idOri != -1 && idDes != -1) {
            // Asumimos grafo no dirigido (rutas de ida y vuelta con la misma distancia)
            grafoRutas->adicionarArco(idOri, idDes, r->getDistancia());
            grafoRutas->adicionarArco(idDes, idOri, r->getDistancia());
        }
    }
}

Lista<Ruta*>* ControladorRutas::BuscarRutaMasCorta(string origen, string destino) {

    int idOri = ObtenerIdCiudad(MapaCiudades, origen);
    int idDes = ObtenerIdCiudad(MapaCiudades, destino);

    if (idOri == -1 || idDes == -1 || idOri == idDes) return nullptr;

    // Ejecutamos el algoritmo de Dijkstra
    float costoTotalMinimo = 0.0f;
    Lista<int>* caminoIDs = grafoRutas->Dijkstra(idOri, idDes, costoTotalMinimo);

    // Si Dijkstra no encontró ruta o devolvió una lista inválida
    if (caminoIDs == nullptr || caminoIDs->longitud() < 2) {
        if (caminoIDs != nullptr) delete caminoIDs;
        return nullptr;
    }

    // Reconstruimos el resultado a partir de los IDs obtenidos
    Lista<Ruta*>* rutaFinal = new Lista<Ruta*>();

    for (unsigned int i = 0; i < caminoIDs->longitud() - 1; i++) {
        int idCiudadActual = caminoIDs->obtenerPos(i);
        int idCiudadSiguiente = caminoIDs->obtenerPos(i + 1);

        string nombreActual = MapaCiudades->obtenerPos(idCiudadActual)->getNombre();
        string nombreSiguiente = MapaCiudades->obtenerPos(idCiudadSiguiente)->getNombre();

        // Buscamos el objeto Ruta* real que conecta estas dos ciudades
        for (unsigned int r = 0; r < rutas->longitud(); r++) {
            Ruta* aux = rutas->obtenerPos(r);
            // Validamos ambas direcciones por si acaso
            if ((aux->getOrigen() == nombreActual && aux->getDestino() == nombreSiguiente) ||
                (aux->getOrigen() == nombreSiguiente && aux->getDestino() == nombreActual)) {
                
                rutaFinal->agregaFinal(aux);
                break; // Pasamos al siguiente salto del camino
            }
        }
    }

    delete caminoIDs; // Evitamos fugas de memoria
    return rutaFinal;
}

void ControladorRutas::AgregarNuevaRuta(string origen, string destino, float distancia) {
    Ruta* ruta = new Ruta(origen, destino, distancia);
    rutas->agregaFinal(ruta);
    controladorArchivos->GardarDatoArchivoRutas(ruta);

    // Actualizamos el Grafo en tiempo real (si el admin agrega una ruta, el grafo la aprende)
    int idOri = ObtenerIdCiudad(MapaCiudades, origen);
    int idDes = ObtenerIdCiudad(MapaCiudades, destino);

    // Si la ciudad no existía, la agregamos
    if (idOri == -1) {
        idOri = MapaCiudades->longitud();
        MapaCiudades->agregaFinal(new CiudadID(origen, idOri));
        grafoRutas->adicionarVertice(origen);
    }
    if (idDes == -1) {
        idDes = MapaCiudades->longitud();
        MapaCiudades->agregaFinal(new CiudadID(destino, idDes));
        grafoRutas->adicionarVertice(destino);
    }

    // Insertamos la nueva conexión matemática
    grafoRutas->adicionarArco(idOri, idDes, distancia);
    grafoRutas->adicionarArco(idDes, idOri, distancia);
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