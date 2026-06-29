#include "GeneradorDataset.h"

GeneradorDataset::GeneradorDataset() {
    srand(time(0));

    // Nombres de hoteles corporativos y realistas, sin usar apellidos de personas
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

// INTEGRAMOS TU LÓGICA DE IDA Y VUELTA BASADA EN RUTAS REALES
void GeneradorDataset::GenerarVuelosAleatorios(int cantidad, Lista<Ruta*>* rutas) {
    if (rutas->longitud() == 0) {
        cout << "Error: No hay rutas disponibles para generar vuelos." << endl;
        return;
    }

    ofstream archivo("Vuelos.txt", ios::app);
    if (!archivo.is_open()) return;

    for (int i = 0; i < cantidad; i += 2) {
        // Cogemos una ruta real al azar
        int indiceRuta = rand() % rutas->longitud();
        Ruta* aux = rutas->obtenerPos(indiceRuta);

        string origen = aux->getOrigen();
        string destino = aux->getDestino();
        float distancia = aux->getDistancia();
        string escalas = "Directo";

        // Vuelo de Ida
        string fechaIda = GenerarFechaAleatoria();
        string asientosIda = GenerarEstadoAsientosOHabitaciones(30);
        archivo << origen << "," << destino << "," << escalas << "," << fechaIda << "," << distancia << "," << asientosIda << "\n";

        // Vuelo de Retorno (si el contador lo permite)
        if (i + 1 < cantidad) {
            string fechaRetorno = GenerarFechaAleatoria();
            string asientosRetorno = GenerarEstadoAsientosOHabitaciones(30);
            archivo << destino << "," << origen << "," << escalas << "," << fechaRetorno << "," << distancia << "," << asientosRetorno << "\n";
        }
    }
    archivo.close();
}

void GeneradorDataset::GenerarHotelesAleatorios(int cantidad, Lista<Ruta*>* rutas) {
    if (rutas->longitud() == 0) return;

    ofstream archivo("Hoteles.txt", ios::app);
    if (!archivo.is_open()) return;

    for (int i = 0; i < cantidad; i++) {
        string nombreHotel = nombresHoteles[rand() % CANT_HOTELES_NOMBRES];
        
        // El hotel debe existir en alguna ciudad destino u origen de las rutas reales
        Ruta* rutaAlAzar = rutas->obtenerPos(rand() % rutas->longitud());
        string ciudad = (rand() % 2 == 0) ? rutaAlAzar->getOrigen() : rutaAlAzar->getDestino();
        
        float puntuacion = 3.0f + static_cast<float>(rand() % 21) / 10.0f; 
        float precio = 40.0f + (rand() % 410); 
        string habitaciones = GenerarEstadoAsientosOHabitaciones(20); 

        archivo << nombreHotel << "," << ciudad << "," << puntuacion << "," << precio << "," << habitaciones << "\n";
    }
    archivo.close();
}

void GeneradorDataset::GenerarPaquetesAleatorios(int cantidad, Lista<Ruta*>* rutas) {
    if (rutas->longitud() == 0) return;

    ofstream archivo("Paquetes.txt", ios::app);
    if (!archivo.is_open()) return;

    for (int i = 0; i < cantidad; i++) {
        // 1. Extraemos una ruta real para el paquete
        Ruta* rutaAux = rutas->obtenerPos(rand() % rutas->longitud());

        string vOri = rutaAux->getOrigen();
        string vDes = rutaAux->getDestino();
        string vEsc = "Directo"; 
        string vFec = GenerarFechaAleatoria();
        float vDist = rutaAux->getDistancia();

        // 2. Generamos el Hotel (Obligatorio en la ciudad de destino)
        string hNom = nombresHoteles[rand() % CANT_HOTELES_NOMBRES];
        string hCiu = vDes; 
        
        float hPunt = 3.0f + static_cast<float>(rand() % 21) / 10.0f;
        float hPrec = (40.0f + (rand() % 410)) * 0.85f; // Precio de paquete con 15% dscto

        // 3. Guardado
        archivo << vOri << "," << vDes << "," << vEsc << "," << vFec << "," << vDist << ","
                << hNom << "," << hCiu << "," << hPunt << "," << hPrec << "\n";
    }
    archivo.close();
}

void GeneradorDataset::GenerarTodo(int cantVuelos, int cantHoteles, int cantPaquetes, Lista<Ruta*>* rutas) {
    GenerarVuelosAleatorios(cantVuelos, rutas);
    GenerarHotelesAleatorios(cantHoteles, rutas);
    GenerarPaquetesAleatorios(cantPaquetes, rutas);
}