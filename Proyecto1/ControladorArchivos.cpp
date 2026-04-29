#include "ControladorArchivos.h"
ControladorArchivos::ControladorArchivos(){}
ControladorArchivos::ControladorArchivos(string nombrearchivo){
	this->nombrearchivo = nombrearchivo;
}
void ControladorArchivos::LeerArchivo(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadId*>* MapaCiudades) {
    ifstream archivo(nombrearchivo);
    if (!archivo.is_open()) {
        cout << "No se puedo abrir el archivo" << std::endl;
        return;
    }

    string linea;
    int contadorId = 0; 

    auto getIdCiudad = [](Lista<CiudadId*>* mapaciudades, string nombre) {
        for (auto i = 0; i < mapaciudades->longitud(); i++) {
            CiudadId* aux = mapaciudades->obtenerPos(i);
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
            && getline(ss, precio, ',') && getline(ss, distancia)) {
            float dbprecio = stof(precio);
            float dbdistancia = stof(distancia);
            Ruta* aux = new Ruta(origen, destino, aerolinea, dbprecio, dbdistancia);
            rutas->agregaFinal(aux);

            
            if (getIdCiudad(MapaCiudades, origen) == -1) {
                MapaCiudades->agregaFinal(new CiudadId(origen, contadorId++));
            }
            if (getIdCiudad(MapaCiudades, destino) == -1) {
                MapaCiudades->agregaFinal(new CiudadId(destino, contadorId++));
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
        int idOrigen = getIdCiudad(MapaCiudades, aux->getOrigen());
        int idDestino = getIdCiudad(MapaCiudades, aux->getDestino());

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
