#include "ControladorRutas.h"
ControladorRutas::ControladorRutas() {
	controladorArchivos = new ControladorArchivos("Rutas.txt");
	rutas = new Lista<Ruta*>();
	conexiones = new Lista<Lista<int>*>();
	MapaCiudades = new Lista<CiudadID*>();
    ObtenerIdCiudad = [](Lista<CiudadID*>* mapaciudades, string nombre) {
        for (unsigned int i = 0; i < mapaciudades->longitud(); i++) {
            CiudadID* aux = mapaciudades->obtenerPos(i);
            if (aux->getNombre() == nombre) {
                return aux->getId();
            }
        }
        return -1;
        };
	controladorArchivos->LeerArchivo(conexiones, rutas, MapaCiudades);
}
 Lista<Ruta*>* ControladorRutas::BuscarRutaMasCorta(string origen, string destino) {

     int idOri = ObtenerIdCiudad(MapaCiudades, origen);
     int idDes = ObtenerIdCiudad(MapaCiudades, destino);

     if (idOri == -1 || idDes == -1) return nullptr;
     if (idOri == idDes) return nullptr;

     Cola<EstadoRuta*>* cola = new Cola<EstadoRuta*>();

     Lista<bool>* visitados = new Lista<bool>();
     for (unsigned int i = 0; i < MapaCiudades->longitud(); i++) 
         visitados->agregaFinal(false);
     
     cola->encolar(new EstadoRuta(idOri, 0));
     visitados->modificarPos(true, idOri); 

     while (!cola->estaVacia()) {

         EstadoRuta* actual = cola->desencolar();

         if (actual->idCiudadActual == idDes) 
             return actual->vuelosTomados;
         
         Lista<int>* filaActual = conexiones->obtenerPos(actual->idCiudadActual);

         for (unsigned int i = 0; i < MapaCiudades->longitud(); i++) {

             if (filaActual->obtenerPos(i) == 1 && visitados->obtenerPos(i) == false) {

                 visitados->modificarPos(true, i);

                 string nombreOrigen = MapaCiudades->obtenerPos(actual->idCiudadActual)->getNombre();
                 string nombreDestino = MapaCiudades->obtenerPos(i)->getNombre();

                 Ruta* rutaEncontrada = nullptr;
                 for (unsigned int r = 0; r < rutas->longitud(); r++) {
                     Ruta* aux = rutas->obtenerPos(r);
                     if (aux->getOrigen() == nombreOrigen && aux->getDestino() == nombreDestino) {
                         rutaEncontrada = aux;
                         break; 
                     }
                 }

                 cola->encolar(new EstadoRuta(i, actual->cantidadSaltos + 1, actual->vuelosTomados, rutaEncontrada));
             }
         }
     }

     return nullptr;
}
void ControladorRutas::AgregarNuevaRuta(string origen, string destino, float distancia) {
	Ruta* ruta = new Ruta(origen, destino, distancia);
	rutas->agregaFinal(ruta);
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
void ControladorRutas::MostrarTodasLasRutas() {

    for (int i = 0; i < rutas->longitud(); i++) {
        Ruta* ruta = rutas->obtenerPos(i);
        ruta->MostrarDatos();
        cout << "-------------------------\n";
    }

}