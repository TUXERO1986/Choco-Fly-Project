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
    indiceVuelosPorOrigen = new ArbolAVLMultiClave<Vuelo*, string>(
        [](Vuelo* v) { return v->getOrigen(); }
    );
    controladorArchivosVuelos->LeerArchivoVuelos(vuelos,indiceVuelosPorOrigen,vuelosMenorPrecio);
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
    

    Lista<Vuelo*>* vuelosValidos = indiceVuelosPorOrigen->BuscarTodos(rutaRequerida->getOrigen());
    
    if (vuelosValidos == nullptr) return; 

    for (int i = 0; i < vuelosValidos->longitud(); i++) {
        Vuelo* vueloActual = vuelosValidos->obtenerPos(i);

        if (vueloActual->getDestino() == rutaRequerida->getDestino()) {
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
    Lista<Vuelo*>* vuelosDesdeOrigen = indiceVuelosPorOrigen->BuscarTodos(origen);
    
    if (vuelosDesdeOrigen == nullptr) return false;

    for (int i = 0; i < vuelosDesdeOrigen->longitud(); i++) {
        Vuelo* aux = vuelosDesdeOrigen->obtenerPos(i);
        if (aux->getDestino() == destino) {
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

    Lista<Vuelo*>* cadenaActual = new Lista<Vuelo*>();
    Lista<Lista<Vuelo*>*>* todasLasCadenas = new Lista<Lista<Vuelo*>*>();

    
    BuscarCadenaVuelos(0, rutas, cadenaActual, todasLasCadenas);

    
    if (todasLasCadenas->longitud() == 0) {
        cout << "\n[!] Lo sentimos, no hay vuelos programados que coincidan para realizar esta conexion." << endl;
        delete cadenaActual;
        delete todasLasCadenas;
        return false;
    }

    int agregados = 0;

   
    for (int i = 0; i < todasLasCadenas->longitud(); i++) {
        Lista<Vuelo*>* cadena = todasLasCadenas->obtenerPos(i);
        
        string stringEscalas = "";
        float distanciaFinal = 0.0f;
        
       
        string fechaSalida = cadena->obtenerPos(0)->getFecha();

       
        for (int j = 0; j < cadena->longitud(); j++) {
            Vuelo* v = cadena->obtenerPos(j);
            distanciaFinal += v->getDistancia();
            
            if (j < cadena->longitud() - 1) {
                stringEscalas += v->getDestino();
                if (j < cadena->longitud() - 2) {
                    stringEscalas += "-";
                }
            }
        }

        
        bool existe = false;
        Lista<Vuelo*>* vuelosDesdeOrigen = indiceVuelosPorOrigen->BuscarTodos(origen);
        
        if (vuelosDesdeOrigen != nullptr) {
            for (int k = 0; k < vuelosDesdeOrigen->longitud(); k++) {
                Vuelo* existV = vuelosDesdeOrigen->obtenerPos(k);
                if (existV->getDestino() == destino && 
                    existV->getFecha() == fechaSalida && 
                    existV->getEscalas() == stringEscalas) {
                    existe = true;
                    break;
                }
            }
        }

        if (!existe) {
            AgregarNuevoVuelo(origen, destino, stringEscalas, fechaSalida, distanciaFinal);
            agregados++;
        }
    }

    delete cadenaActual;
    for (int i = 0; i < todasLasCadenas->longitud(); i++) {
        delete todasLasCadenas->obtenerPos(i);
    }
    delete todasLasCadenas;

    if (agregados > 0) {
        cout << "\n[EXITO] Se han empaquetado " << agregados << " opciones de vuelo con escala usando los trayectos reales registrados." << endl;
    }
    
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