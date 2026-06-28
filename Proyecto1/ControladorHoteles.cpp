#include "ControladorHoteles.h"
ControladorHoteles::ControladorHoteles() {
	controladorArchivos = new ControladorArchivos("Hoteles.txt");
	hoteles = new Lista<Hotel*>();
    auto obtenerPrecio = [](Hotel* h) -> float {
        return h->getPrecioNoche();
    };

    hotelesMenorPrecio = new ArbolAVL<Hotel*>(obtenerPrecio);

	controladorArchivos->LeerArchivoHoteles(hoteles);
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
	for (int i = 0; i < hoteles->longitud(); i++) {
		Hotel* aux = hoteles->obtenerPos(i);
		cout << "[ID DEL HOTEL: " << i << "]" << endl;
		aux->MostrarHotel();
		cout << "---------------------------------" << endl;
	}
}
ArbolAVL<Hotel*>* ControladorHoteles::getHotelesMenorPrecio(){
    return this->hotelesMenorPrecio;
}
Lista<Hotel*>* ControladorHoteles::getHoteles() { return hoteles; }