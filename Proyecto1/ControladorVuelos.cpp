#include "ControladorVuelos.h"
#include "ConsolaUtils.h"
using namespace ColorUI;

ControladorVuelos::ControladorVuelos() {
    controladorArchivosVuelos = new ControladorArchivos("Vuelos.txt");
    vuelos = new Lista<Vuelo*>();
    
    auto obtenerPrecio = [](Vuelo* v) -> float {
        return v->getPrecioBase() + (v->getId() / 1000000.0f);
    };
    vuelosMenorPrecio = new ArbolAVL<Vuelo*>(obtenerPrecio);
    
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
    for(int i=0; i < vuelos->longitud(); i++) {
        vuelosMenorPrecio->Insertar(vuelos->obtenerPos(i));
    }
}

ControladorVuelos::~ControladorVuelos() {
    for (int i = 0; i < vuelos->longitud(); i++) {
        delete vuelos->obtenerPos(i);
    }
    delete vuelos;
    delete vuelosMenorPrecio;
    delete controladorArchivosVuelos;
}

void ControladorVuelos::MostrarVuelos() {
    int total = vuelos->longitud();
    if (total == 0) {
        ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles en el sistema.");
        return;
    }

    int itemsPorPagina = 3;
    int paginasTotales = (total + itemsPorPagina - 1) / itemsPorPagina;
    int paginaActual = 1;

    char opcion = ' ';
    do {
        LimpiarConsola();
        ColorUI::printGradient("\t=== CATALOGO DE VUELOS (Pag " + to_string(paginaActual) + "/" + to_string(paginasTotales) + ") ===", Paletas::TemaPrincipal, false);
        cout << "\n";

        int inicio = (paginaActual - 1) * itemsPorPagina;
        int fin = (inicio + itemsPorPagina < total) ? inicio + itemsPorPagina : total;

        for (int i = inicio; i < fin; i++) {
            Vuelo* aux = vuelos->obtenerPos(i);
            ColorUI::printGradient("  [ ID DEL VUELO: " + to_string(i) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            aux->MostrarDatos();
            cout << "\n";
        }

        ColorUI::printGradient("\n\t[A] Anterior  |  [S] Siguiente  |  [ENTER / Q] Continuar / Salir", Paletas::azul, false);
        cout << "\n\t> ";
        opcion = _getch();
        
        if ((opcion == 's' || opcion == 'S') && paginaActual < paginasTotales) paginaActual++;
        else if ((opcion == 'a' || opcion == 'A') && paginaActual > 1) paginaActual--;
        else if (opcion != 's' && opcion != 'S' && opcion != 'a' && opcion != 'A') {
            if (opcion >= '0' && opcion <= '9') {
                cin.putback(opcion);
            }
            break;
        }
    } while (opcion != 'q' && opcion != 'Q');
}

void ControladorVuelos::AgregarNuevoVuelo(string origen, string destino, string escalas,string fecha, float distancia) {
    Vuelo* nuevoVuelo = new Vuelo(origen, destino, escalas, fecha,distancia,vuelos->longitud());
    vuelos->agregaFinal(nuevoVuelo);
    vuelosMenorPrecio->Insertar(nuevoVuelo);
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

        AgregarNuevoVuelo(origen, destino, escalas, fechaIda, distancia);

        if (i + 1 < contador) {
            string fechaRetorno = to_string(1 + (rand() % 30)) + "-" + to_string(1 + (rand() % 12)) + "-2026";
            AgregarNuevoVuelo(destino, origen, escalas, fechaRetorno, distancia);
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
    MostrarResultadosPaginados<Vuelo>(
        vuelos, 
        "VUELOS " + origen + " - " + destino, 
        [origen, destino](Vuelo* v) { return v->getOrigen() == origen && v->getDestino() == destino; },
        [](Vuelo* v, int indice) {
            ColorUI::printGradient("  [ ID DEL VUELO: " + to_string(indice) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
            v->MostrarDatos();
        }
    );
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

    string stringEscalas = "";
    float distanciaFinal = 0.0f;
    string ciudadActual = origen;

    for (int i = 0; i < rutas->longitud(); i++) {
        Ruta* tramoActual = rutas->obtenerPos(i);
        distanciaFinal += tramoActual->getDistancia();

        string siguienteCiudad = (tramoActual->getOrigen() == ciudadActual) ? tramoActual->getDestino() : tramoActual->getOrigen();

        if (i < rutas->longitud() - 1) {
            stringEscalas += siguienteCiudad;
            if (i < rutas->longitud() - 2) {
                stringEscalas += "-";
            }
        }
        ciudadActual = siguienteCiudad;
    }

    string stringFechas = to_string(1 + (rand() % 28)) + "-" + to_string(1 + (rand() % 12)) + "-2026";

    cout << "\n[GRAFO] Ruta optima generada de " << origen << " a " << destino << endl;
    cout << "Escalas: " << (stringEscalas.empty() ? "Ninguna" : stringEscalas) << endl;
    cout << "Distancia total: " << distanciaFinal << " km" << endl;

    AgregarNuevoVuelo(origen, destino, stringEscalas, stringFechas, distanciaFinal);

    return true;
}

Vuelo* ControladorVuelos::ObtenerVueloPorPosicion(int pos) {
    if (pos >= 0 && pos < vuelos->longitud()) {
        return vuelos->obtenerPos(pos);
    }
    return nullptr;
}

ArbolAVL<Vuelo*>* ControladorVuelos::getVuelosMenorPrecio(){
    return vuelosMenorPrecio;
}

Lista<Vuelo*>* ControladorVuelos::getVuelos() { return vuelos; }