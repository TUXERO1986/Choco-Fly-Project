#include "ControladorPaquetes.h"
#include "Color.h"
using namespace ColorUI;
ControladorPaquetes::ControladorPaquetes() {
	paquetes = new Lista<Paquete*>();
	controladorArchivos = new ControladorArchivos("Paquetes.txt");
	controladorArchivos->LeerArchivoPaquetes(paquetes);
}
ControladorPaquetes::~ControladorPaquetes() {
	for (int i = 0; i < paquetes->longitud(); i++) {
		delete paquetes->obtenerPos(i);
	}
	delete paquetes;
}
void ControladorPaquetes::MostrarPaquetesCiudades(string ciudadOrigen, string ciudadDestino) {
	for (int i = 0; i < paquetes->longitud(); i++) {
		Paquete* aux = paquetes->obtenerPos(i);
		if (aux->getVueloIncluido()->getOrigen() == ciudadOrigen && aux->getVueloIncluido()->getDestino() == ciudadDestino) {
			cout << "Pauquete #" << i << ":" << endl;
			aux->MostrarPaquete();
			cout << endl;
		}
	}
}
void ControladorPaquetes::GenerarPaquetes(int contador, Lista<Hotel*>* listhoteles, Lista<Vuelo*>* listvuelos) {
	for (int i = 0; i < contador; i++) {
		int indiceHotel = rand() % listhoteles->longitud();
		int indiceVuelo = rand() % listvuelos->longitud();
		Hotel* hotelSeleccionado = listhoteles->obtenerPos(indiceHotel);
		Vuelo* vueloSeleccionado = listvuelos->obtenerPos(indiceVuelo);
		if (hotelSeleccionado->getCiudad() != vueloSeleccionado->getDestino())continue;
		AgregarNuevoPaquete(listvuelos->obtenerPos(indiceVuelo), listhoteles->obtenerPos(indiceHotel));
		controladorArchivos->GuardarDatoArchivoPaquetes(new Paquete(listvuelos->obtenerPos(indiceVuelo), listhoteles->obtenerPos(indiceHotel)));
	}
}
void ControladorPaquetes::AgregarNuevoPaquete(Vuelo* vueloIda, Hotel* hotel) {
	Paquete* nuevoPaquete = new Paquete(vueloIda, hotel);
	paquetes->agregaFinal(nuevoPaquete);
	controladorArchivos->GuardarDatoArchivoPaquetes(nuevoPaquete);
}
void ControladorPaquetes::MostrarPaquetes() {
	int total = paquetes->longitud();
	if (total == 0) {
		ColorUI::Alertas::MostrarInfo("No hay paquetes disponibles en el sistema.");
		return;
	}

	int itemsPorPagina = 3;
	int paginasTotales = (total + itemsPorPagina - 1) / itemsPorPagina;
	int paginaActual = 1;

	char opcion = ' ';
	do {
		system("cls");
		ColorUI::printGradient("\t=== CATALOGO DE PAQUETES (Pag " + to_string(paginaActual) + "/" + to_string(paginasTotales) + ") ===", Paletas::TemaPrincipal, false);
		cout << "\n";

		int inicio = (paginaActual - 1) * itemsPorPagina;
		int fin = (inicio + itemsPorPagina < total) ? inicio + itemsPorPagina : total;

		for (int i = inicio; i < fin; i++) {
			Paquete* aux = paquetes->obtenerPos(i);
			ColorUI::printGradient("  [ ID DEL PAQUETE: " + to_string(i) + " ]", { "#FFD700", "#FF8C00", "#FF4500" }, false, true);
			aux->MostrarPaquete();
			cout << "\n";
		}

		ColorUI::printGradient("\n\t[A] Anterior  |  [S] Siguiente  |  [Q] Salir", Paletas::azul, false);
		cout << "\n\tElige una opcion: ";
		cin >> opcion;
		
		if ((opcion == 's' || opcion == 'S') && paginaActual < paginasTotales) paginaActual++;
		else if ((opcion == 'a' || opcion == 'A') && paginaActual > 1) paginaActual--;

	} while (opcion != 'q' && opcion != 'Q');
}
Lista<Paquete*>* ControladorPaquetes::getPaquetes() { return paquetes; }
void ControladorPaquetes::setPaquetes(Lista<Paquete*>* paquetes) { this->paquetes = paquetes; }
