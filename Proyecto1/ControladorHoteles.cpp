#include "ControladorHoteles.h"
#include "ConsolaUtils.h"
#include "Color.h"
using namespace ColorUI;
ControladorHoteles::ControladorHoteles() {
	controladorArchivos = new ControladorArchivos("Hoteles.txt");
	hoteles = new Lista<Hotel*>();
    auto obtenerPrecio = [](Hotel* h) -> float {
        return h->getPrecioNoche();
    };

    hotelesMenorPrecio = new ArbolAVL<Hotel*>(obtenerPrecio);

	controladorArchivos->LeerArchivoHoteles(hoteles);
    for(int i=0; i<hoteles->longitud();i++)hotelesMenorPrecio->Insertar(hoteles->obtenerPos(i));
}
ControladorHoteles::~ControladorHoteles() {
	for (int i = 0; i < hoteles->longitud(); i++) {
		delete hoteles->obtenerPos(i);
	}
	delete hoteles;
}
void ControladorHoteles::GenerarHoteles(int contador, Lista<CiudadID*>* listaCiudades) {
    string nombresBase[] = {
            "Grand Plaza", "Ocean View Resort", "The Royal Palace",
            "Sunset Boutique", "Crystal Bay Suites", "Emerald Resort",
            "Golden Horizon Inn", "Oasis Wellness", "Urban Paradise",
            "Silver Mountain Lodge", "Blue Lagoon Resort", "Majestic Heights",
            "Starlight Inn", "Crown Jewel Hotel", "Harmony Suites"
    };
    int totalNombres = 15;

    for (int i = 0; i < contador; i++) {
        int indiceCiudad = rand() % listaCiudades->longitud();
        string ciudadSeleccionada = listaCiudades->obtenerPos(indiceCiudad)->getNombre();


        int indiceNombre = rand() % totalNombres;


        string nombreHotel = nombresBase[indiceNombre] + " " + ciudadSeleccionada;



        float puntuacion = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f));
        float precioNoche = 50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 150.0f));

        AgregarNuevoHotel(nombreHotel, ciudadSeleccionada, puntuacion, precioNoche);
    }
}
void ControladorHoteles::AgregarNuevoHotel(string nombre, string ciudad, float puntuacion, float precioNoche) {
	Hotel* nuevoHotel = new Hotel(nombre, ciudad, puntuacion, precioNoche, new ControladorHabitaciones(),hoteles->longitud());
	hoteles->agregaFinal(nuevoHotel);
    hotelesMenorPrecio->Insertar(nuevoHotel);
	controladorArchivos->GuardarDatoArchivoHoteles(nuevoHotel);
}
void ControladorHoteles::MostrarHoteles() {
	int total = hoteles->longitud();
	if (total == 0) {
		ColorUI::Alertas::MostrarInfo("No hay hoteles disponibles en el sistema.");
		return;
	}

	int itemsPorPagina = 3;
	int paginasTotales = (total + itemsPorPagina - 1) / itemsPorPagina;
	int paginaActual = 1;

	char opcion = ' ';
	do {
		LimpiarConsola();
		ColorUI::printGradient("\t=== CATALOGO DE HOTELES (Pag " + to_string(paginaActual) + "/" + to_string(paginasTotales) + ") ===", Paletas::TemaPrincipal, false);
		cout << "\n";

		int inicio = (paginaActual - 1) * itemsPorPagina;
		int fin = (inicio + itemsPorPagina < total) ? inicio + itemsPorPagina : total;

		for (int i = inicio; i < fin; i++) {
			Hotel* aux = hoteles->obtenerPos(i);
			ColorUI::printGradient("  [ ID DEL HOTEL: " + to_string(i) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
			aux->MostrarHotel();
			cout << "\n";
		}

		ColorUI::printGradient("\n\t[A] Anterior  |  [S] Siguiente  |  [Q] Salir", Paletas::azul, false);
		cout << "\n\tElige una opcion: ";
		opcion = _getch();
		
		if ((opcion == 's' || opcion == 'S') && paginaActual < paginasTotales) paginaActual++;
		else if ((opcion == 'a' || opcion == 'A') && paginaActual > 1) paginaActual--;

	} while (opcion != 'q' && opcion != 'Q');
}
ArbolAVL<Hotel*>* ControladorHoteles::getHotelesMenorPrecio(){
    return this->hotelesMenorPrecio;
}
Lista<Hotel*>* ControladorHoteles::getHoteles() { return hoteles; }