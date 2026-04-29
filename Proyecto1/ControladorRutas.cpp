#include "ControladorRutas.h"
ControladorRutas::ControladorRutas() {
	controladorArchivos = new ControladorArchivos("Rutas.txt");
	rutas = new Lista<Ruta*>();
	conexiones = new Lista<Lista<int>*>();
	MapaCiudades = new Lista<CiudadId*>();
	controladorArchivos->LeerArchivo(conexiones, rutas, MapaCiudades);
}
string ControladorRutas::BuscarRutaMasCorta(string origen, string destino) {

    auto getIdCiudad = [](Lista<CiudadId*>* mapaciudades, string nombre) {
        for (auto i = 0; i < mapaciudades->longitud(); i++) {
            CiudadId* aux = mapaciudades->obtenerPos(i);
            if (aux->getNombre() == nombre) {
                return aux->getId();
            }
        }
        return -1;
    };
    int idOri = getIdCiudad(MapaCiudades, origen);
    int idDes = getIdCiudad(MapaCiudades, destino);

    if (idOri == -1 || idDes == -1) return "Error: Una de las ciudades no existe.\r\n";
    if (idOri == idDes) return "El origen y destino son el mismo.\r\n";

    
    Cola<EstadoRuta*>* cola = new Cola<EstadoRuta*>();

    
    Lista<bool>* visitados = new Lista<bool>();
    for (int i = 0; i < MapaCiudades->longitud(); i++) {
        visitados->agregaFinal(false);
    }

    
    cola->encolar(new EstadoRuta(idOri, origen, 0));
    visitados->modificarPos(idOri, true); 

    
    while (!cola->estaVacia()) {

        EstadoRuta* actual = cola->desencolar();

        
        if (actual->idCiudadActual == idDes) {
            int numeroEscalas = actual->cantidadSaltos - 1; 
            std::string resultado = "Ruta encontrada (" + std::to_string(numeroEscalas) + " escalas): " + actual->recorrido + "\r\n";
            return resultado; 
        }

        Lista<int>* filaActual = conexiones->obtenerPos(actual->idCiudadActual);

        for (int i = 0; i < MapaCiudades->longitud(); i++) {

            if (filaActual->obtenerPos(i) == 1 && visitados->obtenerPos(i) == false) {

                visitados->modificarPos(i, true);

                std::string nombreSiguienteCiudad = MapaCiudades->obtenerPos(i)->getNombre();
                std::string nuevaRuta = actual->recorrido + " -> " + nombreSiguienteCiudad;

                cola->encolar(new EstadoRuta(i, nuevaRuta, actual->cantidadSaltos + 1));
            }
        }
    }

    return "No hay ninguna ruta posible entre " + origen + " y " + destino + ".\r\n";
}
void ControladorRutas::AgregarNuevaRuta(string origen, string destino, string aerolinea, float precio, float distancia) {
    // Aquí iría la lógica para agregar una nueva ruta a tus estructuras
}
void ControladorRutas::MostrarTodasLasRutas() {

    for (int i = 0; i < rutas->longitud(); i++) {
        Ruta* ruta = rutas->obtenerPos(i);
        ruta->MostrarDatos();
        cout << "-------------------------\n";
    }

}