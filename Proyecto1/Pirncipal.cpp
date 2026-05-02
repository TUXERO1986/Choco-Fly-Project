#include "Lista.h"
#include "Color.h"
#include "ControladorVuelos.h"
#include "conio.h"
using namespace std;
using namespace ColorUI;
void Menu() {
	cout << "======Menu======\n";
	cout << "1. Buscar ruta mas corta\n";
	cout << "2. Agregar nueva ruta\n";
	cout << "3. Salir\n";
}
int main() {
	srand(time(0));
	ControladorVuelos* controladorVuelos = new ControladorVuelos();
		//controladorVuelos->GenerarVuelos(150);
		controladorVuelos->MostrarVuelos();
		//controladorVuelos->GenerarVuelosConEscala("Piura","Santiago");

		delete controladorVuelos;
	return 0;
}