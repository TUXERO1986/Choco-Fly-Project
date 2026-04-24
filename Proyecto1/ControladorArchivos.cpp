#include "ControladorArchivos.h"
ControladorArchivos::ControladorArchivos(){}
ControladorArchivos::ControladorArchivos(std::string nombrearchivo){
	this->nombrearchivo = nombrearchivo;
}
void ControladorArchivos::LeerArchivo(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadesId*>* MapaCiudades) {
    std::ifstream archivo(nombrearchivo);
    if (!archivo.is_open()) {
        std::cout << "No se puedo abrir el archivo" << std::endl;
        return;
    }

    string linea;
    int contadorId = 0; // Se mantiene un solo contador global para todo el archivo

    auto getIdCiudad = [](Lista<CiudadesId*>* mapaciudades, string nombre) {
        for (int i = 0; i < mapaciudades->longitud(); i++) {
            CiudadesId* aux = mapaciudades->obtenerPos(i);
            if (aux->getNombre() == nombre) {
                return aux->getId();
            }
        }
        return -1; 
        };

    while (getline(archivo, linea)) {
        stringstream ss(linea); 
        string origen, destino, aerolinea, precio, distancia;

       

        if (getline(ss, origen, ',') && getline(ss, destino, ',') && getline(ss, aerolinea, ',')
            && getline(ss, precio, ',') && getline(ss, distancia, ',')) {

            float dbprecio = stof(precio);
            float dbdistancia = stof(distancia);
            Ruta* aux = new Ruta(origen, destino, aerolinea, dbprecio, dbdistancia);
            rutas->agregaFinal(aux);

            
            if (getIdCiudad(MapaCiudades, origen) == -1) {
                MapaCiudades->agregaFinal(new CiudadesId(origen, contadorId++));
            }
            if (getIdCiudad(MapaCiudades, destino) == -1) {
                MapaCiudades->agregaFinal(new CiudadesId(destino, contadorId++));
            }
        }
    }
    archivo.close();

    int totalCiudades = MapaCiudades->longitud();

    for (int i = 0; i < totalCiudades; i++) {
        Lista<int>* fila = new Lista<int>(); 
        for (int j = 0; j < totalCiudades; j++) {
            fila->agregaFinal(0);           
        }
        conexiones->agregaFinal(fila);       
    }

    for (int i = 0; i < rutas->longitud(); i++) {
        Ruta* aux = rutas->obtenerPos(i);
        int idOrigen = getIdCiudad(MapaCiudades, aux->getOrigen());
        int idDestino = getIdCiudad(MapaCiudades, aux->getDestino());

        if (idOrigen != -1 && idDestino != -1) {

            Lista<int>* filaOrigen = conexiones->obtenerPos(idOrigen);

            filaOrigen->modificarPos(idDestino, 1);
            conexiones->obtenerPos(idDestino)->modificarPos(idOrigen, 1);
        }
    }
}
