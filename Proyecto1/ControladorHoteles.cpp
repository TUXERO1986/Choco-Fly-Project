#include "ControladorHoteles.h"
ControladorHoteles::ControladorHoteles() {
	controladorArchivos = new ControladorArchivos("Hoteles.txt");
	hoteles = new Lista<Hotel*>();
	controladorArchivos->LeerArchivoHoteles(hoteles);
}
ControladorHoteles::~ControladorHoteles() {
	for (int i = 0; i < hoteles->longitud(); i++) {
		delete hoteles->obtenerPos(i);
	}
	delete hoteles;
}
void ControladorHoteles::GenerarHoteles(int contador, Lista<CiudadID*>* listaCiudades) {
	for (int i = 0; i < contador; i++) {
		int indiceCiudad = rand() % listaCiudades->longitud();
		string ciudadSeleccionada = listaCiudades->obtenerPos(indiceCiudad)->getNombre();
		string nombreHotel = "Hotel " + to_string(i + 1);
		float puntuacion = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f)); 
		float precioNoche = 50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 150.0f)); 
		AgregarNuevoHotel(nombreHotel, ciudadSeleccionada, puntuacion, precioNoche);
	}
}
void ControladorHoteles::AgregarNuevoHotel(string nombre, string ciudad, float puntuacion, float precioNoche) {
	Hotel* nuevoHotel = new Hotel(nombre, ciudad, puntuacion, precioNoche);
	hoteles->agregaFinal(nuevoHotel);
	controladorArchivos->GuardarDatoArchivoHoteles(nuevoHotel);
}
void ControladorHoteles::MostrarHoteles() {
	for (int i = 0; i < hoteles->longitud(); i++) {
		Hotel* aux = hoteles->obtenerPos(i);
		aux->MostrarHotel();
	}
}
Lista<Hotel*>* ControladorHoteles::getHoteles() { return hoteles; }