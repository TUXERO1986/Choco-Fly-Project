#include "ControladorVuelos.h"
using namespace ColorUI;
ControladorVuelos::ControladorVuelos() {
	controladorArchivosVuelos = new ControladorArchivos("Vuelos.txt");
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

	controladorArchivosVuelos->LeerArchivoVuelos(vuelos);
}
ControladorVuelos::~ControladorVuelos() {
    for (int i = 0; i < vuelos->longitud(); i++) {
        delete vuelos->obtenerPos(i);
    }
    delete vuelos;
}
float ControladorVuelos::CalcularDistancia(Lista<Ruta*>* rutasnecesarias, int i) {
    if (i < 0)return 0.00;
	float distanciaBase = rutasnecesarias->obtenerPos(i)->getDistancia();
	return distanciaBase + CalcularDistancia(rutasnecesarias, i - 1);
}
void ControladorVuelos::MostrarVuelos() {
	for (int i = 0; i < vuelos->longitud(); i++) {
		Vuelo* aux = vuelos->obtenerPos(i);
		ColorUI::printGradient("[ID DEL VUELO: " + to_string(i) + "]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
        cout  << "[ID DEL VUELO: " << i << "]" << endl;
		aux->MostrarVuelo();
		ColorUI::printGradient("-----------------------------",Tux, false);
		cout << "-----------------------------" << endl;
	}
}
void ControladorVuelos::AgregarNuevoVuelo(string origen, string destino, string escalas,string fecha, float distancia,ControladorAsientos* controladorAsientos) {
	Vuelo* nuevoVuelo = new Vuelo(origen, destino, escalas, fecha,distancia,controladorAsientos);
	vuelos->agregaFinal(nuevoVuelo);
	controladorArchivosVuelos->GuardarDatoArchivoVuelos(nuevoVuelo);
}
void ControladorVuelos::GenerarVuelos(int contador, Lista<Ruta*>* rutas) {

    for (int i = 0; i < contador; i += 2) {

        int indiceRuta = rand() % rutas->longitud();
        Ruta* aux = rutas->obtenerPos(indiceRuta);

        string origen = aux->getOrigen();
        string destino = aux->getDestino();
        float distancia = aux->getDistancia();
        string escalas = "Directo";

        string fechaIda = to_string(1 + (rand() % 30)) + "-" + to_string(1 + (rand() % 12)) + "-2026";
        ControladorAsientos* asientosIda = new ControladorAsientos();

        AgregarNuevoVuelo(origen, destino, escalas, fechaIda, distancia, asientosIda);

        if (i + 1 < contador) {
            string fechaRetorno = to_string(1 + (rand() % 30)) + "-" + to_string(1 + (rand() % 12)) + "-2026";

            ControladorAsientos* asientosRetorno = new ControladorAsientos();

            AgregarNuevoVuelo(destino, origen, escalas, fechaRetorno, distancia, asientosRetorno);
        }
    }

}
void ControladorVuelos::BuscarCadenaVuelos(int indiceRuta, Lista<Ruta*>* rutas,
    Lista<Vuelo*>* cadenaActual, Lista<Lista<Vuelo*>*>* todasLasCadenas) {

    if (indiceRuta == rutas->longitud()) {

        Lista<Vuelo*>* nuevaCombinacion = new Lista<Vuelo*>();
        for (int i = 0; i < cadenaActual->longitud(); i++) {
            nuevaCombinacion->agregaFinal(cadenaActual->obtenerPos(i));
        }

        todasLasCadenas->agregaFinal(nuevaCombinacion);

        return;
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

                if (mesActual != mesAnterior || (diaActual < diaAnterior || diaActual > diaAnterior + 1)) {
                    fechaValida = false;
                }
            }

            if (fechaValida) {
                cadenaActual->agregaFinal(vueloActual);

                BuscarCadenaVuelos(indiceRuta + 1, rutas, cadenaActual, todasLasCadenas);

                cadenaActual->eliminaFinal();
            }
        }
    }
}
void ControladorVuelos::FiltrarVuelosPorOrigenDestino(string origen, string destino) {
    for (int i = 0; i < vuelos->longitud(); i++) {
        Vuelo* aux = vuelos->obtenerPos(i);
        if (aux->getOrigen() == origen && aux->getDestino() == destino) {
            ColorUI::printGradient("[ID DEL VUELO: " + to_string(i) + "]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            aux->MostrarVuelo();
            cout << endl;
        }
    }
}
bool ControladorVuelos::VerificarVueloDirecto(string origen, string destino) {
    for (int i = 0; i < vuelos->longitud(); i++) {
        Vuelo* aux = vuelos->obtenerPos(i);
        if (aux->getOrigen() == origen && aux->getDestino() == destino) {
            return true;
        }
    }
    return false;
}
bool ControladorVuelos::GenerarVuelosConEscala(string origen, string destino, Lista<Ruta*>* rutas) {

    if (rutas == nullptr || rutas->longitud() == 0) {
        cout << "No hay conexion posible entre " << origen << " y " << destino << endl;
        return false;
    }

    Lista<Vuelo*>* cadenaTemporal = new Lista<Vuelo*>();

    Lista<Lista<Vuelo*>*>* todasLasCadenas = new Lista<Lista<Vuelo*>*>();

    BuscarCadenaVuelos(0, rutas, cadenaTemporal, todasLasCadenas);

    if (todasLasCadenas->longitud() == 0) {
        cout << endl<<"Hay ruta espacial, pero no hay vuelos disponibles en las fechas correctas para conectar." << endl;
        return false;
    }
    else {
        cout << "Se encontraron " << todasLasCadenas->longitud() << " opciones de vuelo:" << endl;

        // 3. Recorremos TODAS las combinaciones encontradas
        for (int c = 0; c < todasLasCadenas->longitud(); c++) {

            Lista<Vuelo*>* vuelosEncontrados = todasLasCadenas->obtenerPos(c);

            if (vuelosEncontrados->longitud() == 1) {
                //Vuelo* v = vuelosEncontrados->obtenerPos(0);
				//cout << "Numero: " << vuelos->getPos(v) << endl;
				//v->MostrarVuelo();
     //            AgregarNuevoVuelo(v->getOrigen(), v->getDestino(), "Directo", v->getFecha(),v->getDistancia());
            }
            else {
                Vuelo* primerVuelo = vuelosEncontrados->obtenerPos(0);
                Vuelo* ultimoVuelo = vuelosEncontrados->obtenerPos(vuelosEncontrados->longitud() - 1);

                string origenFinal = primerVuelo->getOrigen();
                string destinoFinal = ultimoVuelo->getDestino();

                string stringEscalas ="";
                string stringFechas = primerVuelo->getFecha();

                for (int i = 0; i < vuelosEncontrados->longitud() - 1; i++) {
                    Vuelo* vActual = vuelosEncontrados->obtenerPos(i);

                    stringEscalas += vActual->getDestino();
                    if (i < vuelosEncontrados->longitud() - 2) {
                        stringEscalas += ", ";
                    }
                    if (i > 0) {
                        stringFechas +=" / " + vActual->getFecha();
                    }
                }

                stringFechas += " / " + ultimoVuelo->getFecha();
                float distanciaFinal = CalcularDistancia(rutas, rutas->longitud() - 1);
                ControladorAsientos* controladorAsientos = new ControladorAsientos();
                AgregarNuevoVuelo(origenFinal, destinoFinal, stringEscalas, stringFechas, distanciaFinal,controladorAsientos);
            }

            delete vuelosEncontrados;
        }

    }

    delete cadenaTemporal;
    delete todasLasCadenas;
    return true;
}
Vuelo* ControladorVuelos::ObtenerVueloPorPosicion(int pos) {
    if (pos >= 0 && pos < vuelos->longitud()) {
        return vuelos->obtenerPos(pos);
    }
    return nullptr;
}
Lista<Vuelo*>* ControladorVuelos::getVuelos() { return vuelos; }