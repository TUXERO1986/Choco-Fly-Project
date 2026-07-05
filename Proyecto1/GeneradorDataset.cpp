#include "GeneradorDataset.h"

GeneradorDataset::GeneradorDataset() {
    srand(time(0));

    nombresHoteles[0] = "Grand Plaza Hotel";
    nombresHoteles[1] = "Resort Las Americas";
    nombresHoteles[2] = "EcoLodge Imperial";
    nombresHoteles[3] = "Hotel Sol Dorado";
    nombresHoteles[4] = "Hostal El Viajero";
    nombresHoteles[5] = "Mirador Suites";
    nombresHoteles[6] = "Andina Royal Resort";
    nombresHoteles[7] = "Vista Hermosa Hotel";
    nombresHoteles[8] = "Central Boutique";
    nombresHoteles[9] = "Valle Verde Inn";
}

GeneradorDataset::~GeneradorDataset() {}

string GeneradorDataset::GenerarFechaAleatoria() {
    int dia = 1 + rand() % 28;
    int mes = 1 + rand() % 12;
    int anio = 2026; 
    
    string sDia = (dia < 10) ? "0" + to_string(dia) : to_string(dia);
    string sMes = (mes < 10) ? "0" + to_string(mes) : to_string(mes);
    
    return sDia + "-" + sMes + "-" + to_string(anio);
}

string GeneradorDataset::GenerarEstadoAsientosOHabitaciones(int cantidad) {
    string estado = "";
    for (int i = 0; i < cantidad; i++) {
        estado += (rand() % 2 == 0) ? "1" : "0"; 
    }
    return estado;
}

void GeneradorDataset::GenerarVuelosAleatorios(int cantidad, Lista<Ruta*>* rutas, ControladorVuelos* ctrlVuelos) {
    if (rutas->longitud() == 0) return;

    for (int i = 0; i < cantidad; i += 2) {
        int indiceRuta = rand() % rutas->longitud();
        Ruta* aux = rutas->obtenerPos(indiceRuta);

        string origen = aux->getOrigen();
        string destino = aux->getDestino();
        float distancia = aux->getDistancia();
        string escalas = "Directo";
        string fecha = GenerarFechaAleatoria();

        ctrlVuelos->AgregarNuevoVuelo(origen, destino, escalas, fecha, distancia);

        if (i + 1 < cantidad) {
            string fechaR = GenerarFechaAleatoria();
            ctrlVuelos->AgregarNuevoVuelo(destino, origen, escalas, fechaR, distancia);
        }
    }
}

void GeneradorDataset::GenerarHotelesAleatorios(int cantidad, Lista<Ruta*>* rutas, ControladorHoteles* ctrlHoteles) {
    if (rutas->longitud() == 0) return;

    for (int i = 0; i < cantidad; i++) {
        string nombre = nombresHoteles[rand() % CANT_HOTELES_NOMBRES];
        Ruta* rutaAlAzar = rutas->obtenerPos(rand() % rutas->longitud());
        string ciudad = (rand() % 2 == 0) ? rutaAlAzar->getOrigen() : rutaAlAzar->getDestino();
        
        float puntuacion = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f));
        float precio = 50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 150.0f));

        ctrlHoteles->AgregarNuevoHotel(nombre, ciudad, puntuacion, precio);
    }
}

void GeneradorDataset::GenerarPaquetesAleatorios(int cantidad, Lista<Ruta*>* rutas, 
                                                ControladorPaquetes* ctrlPaquetes, 
                                                Lista<Vuelo*>* listaVuelos, 
                                                Lista<Hotel*>* listaHoteles) {
    if (listaVuelos->longitud() == 0 || listaHoteles->longitud() == 0) return;

    for (int i = 0; i < cantidad; i++) {
        Vuelo* v = listaVuelos->obtenerPos(rand() % listaVuelos->longitud());
        Hotel* h = listaHoteles->obtenerPos(rand() % listaHoteles->longitud());

        ctrlPaquetes->AgregarNuevoPaquete(v, h);
    }
}

void GeneradorDataset::GenerarTodo(int cantVuelos, int cantHoteles, int cantPaquetes, 
                                   Lista<Ruta*>* rutas, 
                                   ControladorVuelos* cv, 
                                   ControladorHoteles* ch, 
                                   ControladorPaquetes* cp) {
    
    GenerarVuelosAleatorios(cantVuelos, rutas, cv);
    GenerarHotelesAleatorios(cantHoteles, rutas, ch);
    GenerarPaquetesAleatorios(cantPaquetes, rutas, cp, cv->getVuelos(), ch->getHoteles());
}