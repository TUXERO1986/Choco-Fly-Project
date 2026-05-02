#include "ControladorVuelos.h"
ControladorVuelos::ControladorVuelos() {
	controladorRutas = new ControladorRutas();
	vuelos = new Lista<Vuelo*>();
	ObtenerDia = [](string fecha) {
		size_t pos = fecha.find("-");
		if (pos != string::npos) {
			return stoi(fecha.substr(0, pos));
		}
		return -1; 
		};
	ObtenerMes = [](string fecha) {
		size_t pos1 = fecha.find("-");
		size_t pos2 = fecha.find("-", pos1 + 1);
		if (pos1 != string::npos && pos2 != string::npos) {
			return stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
		}
		return -1; 
		};

	//controladorArchivosVuelos->LeerArchivoVuelos(vuelos);
}
   float ControladorVuelos::CalcularPrecio(Lista<Vuelo*>* vuelosnecesarios, int i) {
        if (i<0)return 0.00;
		float precioBase = vuelosnecesarios->obtenerPos(i)->getPrecio();
		return  precioBase+ CalcularPrecio(vuelosnecesarios, i - 1);
   }
   float ControladorVuelos::CalcularDistancia(Lista<Ruta*>* rutasnecesarias, int i) {
       if (i < 0)return 0.00;
	   float distanciaBase = rutasnecesarias->obtenerPos(i)->getDistancia();
	   return distanciaBase + CalcularDistancia(rutasnecesarias, i - 1);
   }
ControladorVuelos::~ControladorVuelos() {
    for (int i = 0; i < vuelos->longitud(); i++) {
        delete vuelos->obtenerPos(i);
    }
    delete vuelos;
    delete controladorRutas;
}
void ControladorVuelos::MostrarVuelos() {
	for (int i = 0; i < vuelos->longitud(); i++) {
		Vuelo* aux = vuelos->obtenerPos(i);
		aux->MostrarVuelo();
		cout << "-----------------------------" << endl;
	}
}
void ControladorVuelos::AgregarNuevoVuelo(string origen, string destino, string escalas, string fecha, float precio) {
	Vuelo* nuevoVuelo = new Vuelo(origen, destino, escalas, fecha, precio);
	vuelos->agregaFinal(nuevoVuelo);
	//controladorArchivosVuelos->GuardarDatoArchivoVuelos(nuevoVuelo);
}
void ControladorVuelos::GenerarVuelos(int contador) {
	Lista<Ruta*>* rutas = controladorRutas->getRutas();
	for(int i=0; i < contador; i++) {
		int indiceRuta = rand() % rutas->longitud();
		Ruta* aux = rutas->obtenerPos(indiceRuta);
		string origen = aux->getOrigen();
		string destino = aux->getDestino();
		float distancia = aux->getDistancia();
		float precio = distancia * 0.07; 
		string fecha = to_string(5+(rand() % 4))+"-"+ to_string(3+(rand() % 5))+"-2026";
		string escalas = "Directo";
		AgregarNuevoVuelo(origen, destino, escalas, fecha, precio);
	}

}
bool ControladorVuelos::BuscarCadenaVuelos(int indiceRuta, Lista<Ruta*>*& rutas, Lista<Vuelo*>*& cadenaActual) {
    if (indiceRuta == rutas->longitud()) {
        return true;
    }

    Ruta* rutaRequerida = rutas->obtenerPos(indiceRuta);

    for (int i = 0; i < vuelos->longitud(); i++) {
        Vuelo* vueloActual = vuelos->obtenerPos(i);

        if (vueloActual->getOrigen() == rutaRequerida->getOrigen() &&
            vueloActual->getDestino() == rutaRequerida->getDestino()) {

            bool fechaValida = true;

            if (indiceRuta > 0) {
                Vuelo* vueloAnterior = cadenaActual->obtenerPos(indiceRuta - 1);
				int mesAnterior = ObtenerMes(vueloAnterior->getFecha());
				int diaAnterior = ObtenerDia(vueloAnterior->getFecha());
				int mesActual = ObtenerMes(vueloActual->getFecha());
				int diaActual = ObtenerDia(vueloActual->getFecha());
                if (mesActual != mesAnterior || (diaActual < diaAnterior||diaActual>diaAnterior+1)) {
                    fechaValida = false;
                }
            }

            if (fechaValida) {
                cadenaActual->agregaFinal(vueloActual);

                if (BuscarCadenaVuelos(indiceRuta + 1, rutas, cadenaActual)) {
                    return true; 
                }

                cadenaActual->eliminaFinal();
            }
        }
    }

    return false;
}

void ControladorVuelos::GenerarVuelosConEscala(string origen, string destino) {

    Lista<Ruta*>* rutasNecesarias = controladorRutas->BuscarRutaMasCorta(origen, destino);

    if (rutasNecesarias == nullptr || rutasNecesarias->longitud() == 0) {
        cout << "No hay conexion posible entre " << origen << " y " << destino << endl;
        return;
    }

    Lista<Vuelo*>* vuelosEncontrados = new Lista<Vuelo*>();

    bool exito = BuscarCadenaVuelos(0, rutasNecesarias, vuelosEncontrados);

    if (!exito) {
        cout << "Hay ruta, pero no hay vuelos disponibles en las fechas correctas para conectar." << endl;
        delete vuelosEncontrados;
        return;
    }

    if (vuelosEncontrados->longitud() == 1) {
        Vuelo* v = vuelosEncontrados->obtenerPos(0);

        cout << "Vuelo Directo Encontrado: " << v->getOrigen() << " -> " << v->getDestino() << " [" << v->getFecha() << "]" << endl;
    }
    else {

        Vuelo* primerVuelo = vuelosEncontrados->obtenerPos(0);
        Vuelo* ultimoVuelo = vuelosEncontrados->obtenerPos(vuelosEncontrados->longitud() - 1);

        string origenFinal = primerVuelo->getOrigen();
        string destinoFinal = ultimoVuelo->getDestino();

        string stringEscalas = "Escalas en: ";
        string stringFechas = primerVuelo->getFecha(); 

        for (int i = 0; i < vuelosEncontrados->longitud() - 1; i++) {
            Vuelo* vActual = vuelosEncontrados->obtenerPos(i);

            stringEscalas += vActual->getDestino();
            if (i < vuelosEncontrados->longitud() - 2) {
                stringEscalas += ", ";
            }

            if (i > 0) {
                stringFechas += " - " + vActual->getFecha();
            }
        }

        stringFechas += " / " + ultimoVuelo->getFecha();
        float precioFinal= CalcularPrecio(vuelosEncontrados,rutasNecesarias->longitud()-1); 
        float distanciaFinal = CalcularDistancia(rutasNecesarias,rutasNecesarias->longitud()-1); 

        cout << "\n--- NUEVO TICKET GENERADO ---" << endl;
        cout << "Origen: " << origenFinal << endl;
        cout << "Destino: " << destinoFinal << endl;
        cout << stringEscalas << endl;
        cout << "Fechas del viaje: " << stringFechas << endl;
		cout << "Distancia Total: " << distanciaFinal << " km" << endl;
		cout << "Precio Total: $" << precioFinal << endl;
    }
    delete rutasNecesarias;
    delete vuelosEncontrados; 
}